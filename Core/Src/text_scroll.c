/*
 * text_scroll.c
 *
 *  Created on: Oct 16, 2025
 *      Author: prutha
 */
#include <stdio.h>
#include "text_scroll.h"
#include "parameter_display.h"
#include "benchmark_results.h"

static lv_obj_t *scroll_obj = NULL;
static lv_obj_t *text_container = NULL;

#define SCROLL_TIME_UP   4500  // 4.5s scroll up
#define SCROLL_TIME_DOWN 4500  // 4.5s scroll down
#define PAUSE_TIME       500   // 500ms pause

static lv_anim_t scroll_anim;
static lv_timer_t *text_timer = NULL;
static lv_timer_t *pause_timer = NULL;

static bool scroll_upward = true;

// Return to home screen after 10s
static void auto_return_cb(lv_timer_t * timer)
{
    lv_timer_del(pause_timer);
    pause_timer = NULL;

    char fps_str[16], external_str[16], ram_str[16], render_str[16], cpu_str[16], internal_str[16];

    snprintf(fps_str,  sizeof(fps_str),  "%lu", avg_fps);
    snprintf(external_str, sizeof(external_str), "%lu MB", external_usage / 1024);
    snprintf(internal_str, sizeof(internal_str), "%lu KB", internal_usage);
    snprintf(ram_str,  sizeof(ram_str),  "%lu MB", totalRamUsed / 1024);
    snprintf(render_str,sizeof(render_str),"%lu ms", avg_render_time);
    snprintf(cpu_str,   sizeof(cpu_str),   "%lu %%", avg_cpu_usage);

    static_param_screen_init("Text Scroll Test", fps_str, ram_str, internal_str, external_str, render_str, cpu_str);

    if (scroll_obj) {
        lv_obj_del(scroll_obj);
        scroll_obj = NULL;
    }

    lv_timer_del(timer);
    text_timer = NULL;
}

// Animation execution callback (sets Y position of text_container)
static void scroll_exec_cb(void * obj, int32_t v)
{
    lv_obj_set_y(obj, -v);
}

// Pause timer callback: starts the next scroll in opposite direction
static void pause_timer_cb(lv_timer_t * timer)
{
    if (!text_container) {
        lv_timer_del(timer);
        return;
    }

    lv_obj_update_layout(text_container);
    lv_coord_t content_height = lv_obj_get_height(text_container);
    lv_coord_t visible_height = 480;
    lv_coord_t scroll_range = content_height - visible_height;

    if (scroll_range <= 0) {
        lv_timer_del(timer);
        return; // Nothing to scroll
    }

    scroll_upward = !scroll_upward;  // Toggle direction

    if (scroll_upward) {
        // Next: Scroll UP (visually top → bottom)
        // Start from TOP position (beginning of text visible)
        lv_obj_set_y(text_container, 0);
        lv_anim_set_values(&scroll_anim, 0, scroll_range);        // Move content up
        lv_anim_set_time(&scroll_anim, SCROLL_TIME_UP);
    } else {
        // Next: Scroll DOWN (visually bottom → top)
        // Start from BOTTOM position (end of text visible)
        lv_obj_set_y(text_container, -scroll_range);
        lv_anim_set_values(&scroll_anim, scroll_range, 0);        // Move content down (back to top)
        lv_anim_set_time(&scroll_anim, SCROLL_TIME_DOWN);
    }

    lv_anim_start(&scroll_anim);

    lv_timer_del(timer);
    pause_timer = NULL;
}

// Animation ready callback: trigger pause at end
static void scroll_ready_cb(lv_anim_t * a)
{
    // Start pause before reversing direction
    pause_timer = lv_timer_create(pause_timer_cb, PAUSE_TIME, NULL);
}

// Start the scrolling sequence
static void start_scroll_animation(void)
{
    if (!scroll_obj || !text_container) return;

    lv_obj_update_layout(text_container);
    lv_coord_t content_height = lv_obj_get_height(text_container);
    lv_coord_t visible_height = 480;
    lv_coord_t scroll_range = content_height - visible_height;

    if (scroll_range <= 0) return;

    lv_anim_init(&scroll_anim);
    lv_anim_set_var(&scroll_anim, text_container);
    lv_anim_set_exec_cb(&scroll_anim, scroll_exec_cb);
    lv_anim_set_path_cb(&scroll_anim, lv_anim_path_linear);
    lv_anim_set_ready_cb(&scroll_anim, scroll_ready_cb);

    scroll_upward = true;
    lv_obj_set_y(text_container, 0);
    lv_anim_set_values(&scroll_anim, 0, scroll_range);
    lv_anim_set_time(&scroll_anim, SCROLL_TIME_UP);

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
    lv_obj_set_style_pad_all(scroll_obj, 1, 0);
    lv_obj_set_style_border_width(scroll_obj, 0, 0);
    lv_obj_set_style_radius(scroll_obj, 0, 0);

    // Transparent text container
    text_container = lv_obj_create(scroll_obj);
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
    lv_obj_t *text = lv_label_create(text_container);
    lv_label_set_text(text,
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

    lv_obj_set_style_text_font(text, &lv_font_calibri_regular_25, 0);
    lv_obj_set_style_text_color(text, lv_color_hex(0x000000), 0);
    lv_obj_set_width(text, 800);
    lv_label_set_long_mode(text, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(text, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_align_to(text, title, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    text_timer = lv_timer_create(auto_return_cb, 10000, NULL);  // 10s

    // Start smooth scroll animation
    start_scroll_animation();
}

void text_scroll_button_event_cb(lv_event_t * e)
{
	demo_running = 1;

	text_scroll();
}
