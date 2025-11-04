#ifndef AVI_PARSER_H
#define AVI_PARSER_H

#include <stdint.h>
#include "jpeg_utils_conf.h"

typedef struct {
    const uint8_t *data;      // Pointer to AVI data in flash
    uint32_t size;            // Total size of AVI data
    uint32_t pos;             // Current position in data
    uint32_t frame_pos[1000]; // Frame offsets (max 1000 frames)
    uint32_t frame_count;     // Number of frames
    uint32_t width, height;   // Video dimensions
    uint32_t fps;             // Frames per second
} avi_t;

int avi_init(avi_t *avi, const uint8_t *data, uint32_t size);
int avi_get_frame(avi_t *avi, uint32_t frame_idx, const uint8_t **buf, uint32_t *size);
void JPEG_DecodeToRGB565(JPEG_HandleTypeDef *hjpeg, const uint8_t *jpeg_data, uint32_t jpeg_size, uint8_t *dest, uint32_t width, uint32_t height);

#endif /* AVI_PARSER_H */
