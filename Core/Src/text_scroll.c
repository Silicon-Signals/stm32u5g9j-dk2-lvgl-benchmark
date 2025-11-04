/*
 * text_scroll.c
 *
 *  Created on: Oct 16, 2025
 *      Author: prutha
 */
#include "text_scroll.h"
#include "parameter_display.h"

static lv_obj_t *scroll_obj = NULL;

#define SCROLL_TIME 10000  // total time for one full scroll cycle

static lv_anim_t scroll_anim;
static lv_timer_t *text_timer;

// Return to home screen after 10s
static void auto_return_cb(lv_timer_t * timer) {
    static_param_screen_init("Text Scroll Test", "28", "12 KB", "78 KB", "0.5 ms", "16 %");

    if(scroll_obj) {
        lv_obj_del(scroll_obj);
        scroll_obj = NULL;
    }

    lv_timer_del(timer);
    text_timer = NULL;
}

// Animation execution callback
static void scroll_exec_cb(void * obj, int32_t v)
{
    lv_obj_scroll_to_y(obj, v, LV_ANIM_ON);
}

// Animation ready callback — jump back to top and restart instantly
static void scroll_ready_cb(lv_anim_t * a)
{
    lv_obj_t * obj = a->var;

    // Instantly reset scroll to top without animation
    lv_obj_scroll_to_y(obj, 0, LV_ANIM_ON);

    // Restart animation immediately (no pause)
    lv_anim_start(&scroll_anim);
}

// Start continuous smooth scroll animation
static void start_scroll_animation(void)
{
    if (!scroll_obj) return;

    lv_obj_update_layout(scroll_obj);

    int32_t scrollable = lv_obj_get_scroll_bottom(scroll_obj);

    lv_anim_init(&scroll_anim);
    lv_anim_set_var(&scroll_anim, scroll_obj);
    lv_anim_set_exec_cb(&scroll_anim, scroll_exec_cb);
    lv_anim_set_values(&scroll_anim, 0, scrollable);
    lv_anim_set_time(&scroll_anim, SCROLL_TIME);
    lv_anim_set_path_cb(&scroll_anim, lv_anim_path_linear);
    lv_anim_set_ready_cb(&scroll_anim, scroll_ready_cb);
    lv_anim_start(&scroll_anim);
}

// Create text scroll screen
void text_scroll(void)
{
    // Create main scrollable container
    scroll_obj = lv_obj_create(lv_screen_active());
    lv_obj_set_size(scroll_obj, 800, 480);
    lv_obj_center(scroll_obj);
    lv_obj_set_style_bg_color(scroll_obj, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_opa(scroll_obj, LV_OPA_COVER, 0);
    lv_obj_set_scroll_dir(scroll_obj, LV_DIR_VER);
    lv_obj_set_scrollbar_mode(scroll_obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_all(scroll_obj, 0, 0);
    lv_obj_set_style_border_width(scroll_obj, 0, 0);

    // Transparent text container
    lv_obj_t *text_container = lv_obj_create(scroll_obj);
    lv_obj_set_size(text_container, 800, LV_SIZE_CONTENT);
    lv_obj_align(text_container, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_set_style_bg_opa(text_container, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(text_container, 0, 0);
    lv_obj_set_style_pad_all(text_container, 10, 0);

    // --- Title ---
    lv_obj_t *title = lv_label_create(text_container);
    lv_label_set_text(title, "STM32U5G9J-DK2");
    lv_obj_set_style_text_font(title, &lv_font_calibri_bold_44, 0);
    lv_obj_set_style_text_color(title, lv_color_hex(0x000000), 0);
    lv_obj_set_style_text_align(title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 0);

    // --- Body text ---
    lv_obj_t *body = lv_label_create(text_container);
    lv_label_set_text(body,
        "\n"
        "          The STM32U5G9J-DK2 Discovery kit is a complete demonstration and "
        "development platform for the STM32U5G9ZJT6Q microcontroller, featuring "
        "an Arm® Cortex®-M33 core with Arm® TrustZone®.\n\n"

        "          Leveraging the innovative ultra-low power-oriented features, 3 Mbytes "
        "of embedded SRAM, 4 Mbytes of embedded flash memory, and rich graphics "
        "features, the STM32U5G9J-DK2 Discovery kit enables users to prototype "
        "applications with state-of-the-art energy efficiency, as well as providing "
        "stunning and optimized graphics rendering with the support of a 2.5D Neo-"
        "Chrom accelerator, Chrom-ART Accelerator, and Chrom-GRC™ MMU.\n\n"

        "          The STM32U5G9J-DK2 Discovery kit integrates a full range of hardware "
        "features that help the user evaluate all the peripherals, such as a 5\" RGB 800x "
        "480 pixels TFT colored LCD module with a 24-bit RGB interface and capacitive "
        "touch panel, USB Type-C® HS, Octo-SPI flash memory device, ARDUINO®, and "
        "STLINK-V3EC (USART console).\n\n"

        "          The STM32U5G9J-DK2 Discovery kit integrates an STLINK-V3EC embedded "
        "in-circuit debugger and programmer for the STM32 microcontroller with a "
        "USB Virtual COM port bridge and comes with the STM32CubeU5 MCU Package, "
        "which provides an STM32 comprehensive software HAL library as well as "
        "various software examples.\n\n"

        "          Ultra-low-power STM32U5G9ZJT6Q microcontroller based on the Arm® "
        "Cortex®-M33 core with Arm® TrustZone®, featuring 4 Mbytes of flash "
        "memory, 3 Mbytes of SRAM, and SMPS, in an LQFP144 package.\n\n"

        "          Support for the NeoChrom VG GPU New processing unit optimizes rendering "
        "of vector graphics and animations such as flips, spins, scaling and more, "
        "vastly increasing the number of frames per second - fully integrated in "
        "X-CUBE-TOUCHGFX.\n\n"

        "          The STM32U5G9J-DK Discovery 2 kit relies on an HSE oscillator (16 MHz "
        "crystal) and an LSE oscillator (32.768 kHz crystal) as clock references. Using "
        "the HSE (instead of HSI) is mandatory to manage the DSI interface for the LCD "
        "module and the USB high-speed interface.\n\n"

        "          The STM32U5G9J Discovery 2 kit has up to 4 USARTs, 2 UARTs, and 1 "
        "LPUART. The Zephyr console output is assigned to USART1 which connected to "
        "the onboard ST-LINK/V3.0 Virtual COM port interface. Default communication "
        "settings are 115200 8N1.\n\n"

        "          The demonstration software, included in the STM32Cube MCU Package "
        "corresponding to the on-board microcontroller, is preloaded in the STM32 "
        "flash memory for easy demonstration of the device peripherals in standalone "
        "mode. The latest versions of the demonstration source code and associated "
        "documentation can be downloaded from www.st.com.\n\n"
    );

    lv_obj_set_style_text_font(body, &lv_font_calibri_regular_25, 0);
    lv_obj_set_style_text_color(body, lv_color_hex(0x000000), 0);
    lv_obj_set_width(body, 800);
    lv_label_set_long_mode(body, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(body, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_align_to(body, title, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    text_timer = lv_timer_create(auto_return_cb, 10000, NULL);  // 10s

    // Start smooth scroll animation
    start_scroll_animation();
}

void text_scroll_button_event_cb(lv_event_t * e)
{
	text_scroll();
}
