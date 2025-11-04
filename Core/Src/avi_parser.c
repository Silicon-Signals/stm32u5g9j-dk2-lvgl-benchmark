#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "lvgl/lvgl.h"
#include "avi_parser.h"
#include "main.h"
#include "jpeg_utils_conf.h"
#include "jpeg_utils.h"

extern DMA2D_HandleTypeDef hdma2d;
extern UART_HandleTypeDef huart1;
void debug_print(const char *msg) {
    HAL_UART_Transmit(&huart1, (uint8_t *)msg, strlen(msg), 100);
    HAL_UART_Transmit(&huart1, (uint8_t *)"\r", 1, 100);
}

void debug_hex(const uint8_t *data, uint32_t len, uint32_t offset) {
    char debug_msg[128];
    uint32_t i;
    for (i = 0; i < len && i < 16; i += 8) {
        sprintf(debug_msg, "Data at %lu: %02x %02x %02x %02x %02x %02x %02x %02x\n",
                offset + i, data[i], data[i+1], data[i+2], data[i+3],
                data[i+4], data[i+5], data[i+6], data[i+7]);
        debug_print(debug_msg);
    }
}

static inline uint16_t YUV2RGB565(int Y, int U, int V)
{
    int r = Y + 1.402f * (V - 128);
    int g = Y - 0.344f * (U - 128) - 0.714f * (V - 128);
    int b = Y + 1.772f * (U - 128);

    if (r < 0) r = 0; else if (r > 255) r = 255;
    if (g < 0) g = 0; else if (g > 255) g = 255;
    if (b < 0) b = 0; else if (b > 255) b = 255;

    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void JPEG_DecodeToRGB565(JPEG_HandleTypeDef *hjpeg, const uint8_t *jpeg_data, uint32_t jpeg_size, uint8_t *rgb565_dest, uint32_t width, uint32_t height)
{
    HAL_StatusTypeDef status;
    JPEG_ConfTypeDef jpegInfo;
    JPEG_YCbCrToRGB_Convert_Function convertFunc;
    uint32_t ImageNbMCUs = 0;

    // Step 1: Get JPEG image info
    HAL_JPEG_GetInfo(hjpeg, &jpegInfo);

    // Step 2: Get conversion function based on subsampling (e.g., YUV420)
    status = JPEG_GetDecodeColorConvertFunc(&jpegInfo, &convertFunc, &ImageNbMCUs);

    char debug_msg[128];
    sprintf(debug_msg, "Status : %lu\r\n", status);
    debug_print(debug_msg);

    if (jpegInfo.ColorSpace == 16) {
        debug_print("Warning: Unexpected ColorSpace 16, treating as YCbCr\r\n");
        jpegInfo.ColorSpace = JPEG_YCBCR_COLORSPACE; // Fallback
    }

    sprintf(debug_msg, "ColorSpace : %lu\r\n", jpegInfo.ColorSpace);
    debug_print(debug_msg);

    if (status != HAL_OK || convertFunc == NULL) {
        Error_Handler(); // or print debug message
        return;
    }

    // Step 3: Start JPEG decode (YUV output in internal buffer)
    static uint8_t jpeg_output_buffer[800 * 480 * 3 / 2]; // Enough for YUV420

    HAL_JPEG_Decode(hjpeg, (uint8_t *)jpeg_data, jpeg_size, jpeg_output_buffer, sizeof(jpeg_output_buffer), HAL_MAX_DELAY);

    // Wait until done
    while (HAL_JPEG_GetState(hjpeg) != HAL_JPEG_STATE_READY) {}

    // Manual conversion loop for YUV420
    uint8_t *Y = jpeg_output_buffer;
    uint8_t *U = Y + width * height;
    uint8_t *V = U + (width * height / 4);

    for (uint32_t j = 0; j < height; j++) {
        for (uint32_t i = 0; i < width; i++) {
            uint32_t Y_index = j * width + i;
            uint32_t U_index = (j / 2) * (width / 2) + (i / 2);
            uint32_t V_index = U_index;
            uint16_t pixel = YUV2RGB565(Y[Y_index], U[U_index], V[V_index]);
            ((uint16_t *)rgb565_dest)[Y_index] = pixel;
        }
    }

    // Step 4: Convert from YUV → RGB565
    uint32_t convertedBytes = 0;
    uint32_t dataCount = jpegInfo.ImageWidth * jpegInfo.ImageHeight * (jpegInfo.ColorSpace == JPEG_GRAYSCALE_COLORSPACE ? 1 : (jpegInfo.ChromaSubsampling == JPEG_420_SUBSAMPLING ? 1.5 : 2));
    convertFunc(jpeg_output_buffer, rgb565_dest, 0, dataCount, &convertedBytes);
}

int avi_init(avi_t *avi, const uint8_t *data, uint32_t size) {
    avi->data = data;
    avi->size = size;
    avi->pos = 0;
    avi->frame_count = 0;

    char debug_msg[128];
    sprintf(debug_msg, "AVI size: %lu bytes\n", size);
    debug_print(debug_msg);
    debug_hex(data, 16, 0);

    // Check RIFF + AVI
    if (avi->size < 12) return -1;
    if (memcmp(avi->data, "RIFF", 4) || memcmp(avi->data + 8, "AVI ", 4)) {
        debug_print("Invalid RIFF/AVI header\n");
        return -1;
    }
    avi->pos = 12;
    debug_print("RIFF/AVI header OK\n");

    uint8_t buf[64];
    while (avi->pos + 8 <= avi->size) {
        memcpy(buf, avi->data + avi->pos, 8);
        uint32_t chunk_size = *(uint32_t *)(buf + 4);
        char id[5] = {0};
        memcpy(id, buf, 4);

        sprintf(debug_msg, "Chunk at %lu: %s, size %lu\n", avi->pos, id, chunk_size);
        debug_print(debug_msg);

        if (chunk_size > avi->size - avi->pos - 8) {
            debug_print("Chunk size too big -> stop\n");
            break;
        }

        // --- LIST handler ---
        if (!strncmp(id, "LIST", 4)) {
            if (avi->pos + 12 > avi->size) break;

            memcpy(buf, avi->data + avi->pos + 8, 4);
            char list_type[5] = {0};
            memcpy(list_type, buf, 4);

            sprintf(debug_msg, "LIST type: %s (size %lu)\n", list_type, chunk_size);
            debug_print(debug_msg);

            uint32_t list_end = avi->pos + 8 + chunk_size;
            avi->pos += 12; // skip LIST+size+type

            if (!strncmp(list_type, "hdrl", 4)) {
                // Parse headers
                while (avi->pos + 8 < list_end) {
                    memcpy(buf, avi->data + avi->pos, 8);
                    uint32_t sub_size = *(uint32_t *)(buf + 4);
                    char sub_id[5] = {0};
                    memcpy(sub_id, buf, 4);

                    sprintf(debug_msg, "  hdrl sub-chunk: %s, size %lu\n", sub_id, sub_size);
                    debug_print(debug_msg);

                    if (!strncmp(sub_id, "avih", 4) && sub_size >= 56) {
                        memcpy(buf, avi->data + avi->pos + 8, 56);
                        uint32_t usec = *(uint32_t *)(buf + 0);
                        avi->width  = *(uint32_t *)(buf + 32);
                        avi->height = *(uint32_t *)(buf + 36);
                        avi->fps    = usec ? 1000000 / usec : 15;

                        sprintf(debug_msg, "  avih: %lux%lu, %lu FPS\n", avi->width, avi->height, avi->fps);
                        debug_print(debug_msg);
                    }

                    avi->pos += 8 + sub_size;
                    if (avi->pos % 2) avi->pos++;
                }
                avi->pos = list_end;
            }
            else if (!strncmp(list_type, "movi", 4)) {
                // Collect frames
                while (avi->pos + 8 < list_end && avi->frame_count < 1000) {
                    memcpy(buf, avi->data + avi->pos, 8);
                    uint32_t frame_size = *(uint32_t *)(buf + 4);
                    char frame_id[5] = {0};
                    memcpy(frame_id, buf, 4);

                    if (!strncmp(frame_id, "00dc", 4) || !strncmp(frame_id, "00db", 4)) {
                        avi->frame_pos[avi->frame_count++] = avi->pos + 8;
                        sprintf(debug_msg, "  Frame %lu: %s, size %lu\n",
                                avi->frame_count, frame_id, frame_size);
                        debug_print(debug_msg);
                    }
                    avi->pos += 8 + frame_size;
                    if (avi->pos % 2) avi->pos++;
                }
                avi->pos = list_end;
            }
            else {
                // Unknown LIST: just skip safely
                avi->pos = list_end;
            }
        }
        else {
            // Non-LIST chunk (like JUNK, idx1, INFO, etc.)
            avi->pos += 8 + chunk_size;
            if (avi->pos % 2) avi->pos++;
        }
    }

    if (!avi->frame_count) {
        debug_print("No frames found\n");
        return -1;
    }
    return 0;
}

int avi_get_frame(avi_t *avi, uint32_t frame_idx, const uint8_t **buf, uint32_t *size) {
    if (frame_idx >= avi->frame_count) {
        debug_print("Invalid frame index\n");
        return -1;
    }
    uint32_t frame_start = avi->frame_pos[frame_idx];
    if (frame_start + 8 > avi->size) {
        debug_print("Frame out of bounds\n");
        return -1;
    }

    uint8_t header[8];
    memcpy(header, avi->data + frame_start - 8, 8);
    *size = *(uint32_t *)(header + 4);
    *buf = avi->data + frame_start;
    if (*buf + *size > avi->data + avi->size) {
        debug_print("Frame size exceeds AVI\n");
        return -1;
    }

    char debug_msg[64];
    sprintf(debug_msg, "Fetching frame %lu, size %lu\r\n", frame_idx + 1, *size);
    debug_print(debug_msg);
    return 0;
}
