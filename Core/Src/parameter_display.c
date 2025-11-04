/*
 * parameter_display.c
 *
 * Created on: Oct 14, 2025
 * Author: prutha
 */

#include "parameter_display.h"
#include "main_scr.h"
#include "string.h"

LV_IMAGE_DECLARE(home_icon);
LV_IMAGE_DECLARE(Table_Image);
extern lv_obj_t *main_screen;
lv_obj_t *table_screen;

static void static_param_home_cb(lv_event_t * e) {
    // Delete current table screen
    if (table_screen) {
        lv_obj_del(table_screen);
        table_screen = NULL;
    }

    // Load main screen
    lv_scr_load(main_screen);
}

static void create_static_param_screen(lv_obj_t * screen, char *test_label, char *frame_rate, char *stack_use, char *heap_size, char *render_time, char *cpu_load)
{
    // Set background image
    lv_obj_t *bg = lv_img_create(screen);
    lv_img_set_src(bg, &Table_Image);
    lv_obj_set_size(bg, 800, 480);
    lv_obj_align(bg, LV_ALIGN_TOP_LEFT, 0, 0);

    // Create text labels
    lv_obj_t *label_test = lv_label_create(screen);
    lv_label_set_text(label_test, "Test");
    lv_obj_set_pos(label_test, 165, 156);
    lv_obj_set_style_text_align(label_test, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(label_test, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(label_test, &lv_font_calibri_bold_18, 0);

    lv_obj_t *label_2d_test = lv_label_create(screen);
    lv_label_set_text(label_2d_test, test_label);
    lv_obj_set_pos(label_2d_test, 415, 156);
    lv_obj_set_style_text_align(label_2d_test, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(label_2d_test, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(label_2d_test, &lv_font_calibri_bold_18, 0);

    lv_obj_t *label_frame_rate = lv_label_create(screen);
    lv_label_set_text(label_frame_rate, "Frame Rate (FPS)");
    lv_obj_set_pos(label_frame_rate, 165, 192);
    lv_obj_set_style_text_align(label_frame_rate, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_frame_rate, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_frame_rate, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_28 = lv_label_create(screen);
    lv_label_set_text(label_28, frame_rate);
    lv_obj_set_pos(label_28, 415, 192);
    lv_obj_set_style_text_align(label_28, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_28, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_28, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_stack_usage = lv_label_create(screen);
    lv_label_set_text(label_stack_usage, "Stack Usage");
    lv_obj_set_pos(label_stack_usage, 165, 228);
    lv_obj_set_style_text_align(label_stack_usage, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_stack_usage, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_stack_usage, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_12kb = lv_label_create(screen);
    lv_label_set_text(label_12kb, stack_use);
    lv_obj_set_pos(label_12kb, 415, 228);
    lv_obj_set_style_text_align(label_12kb, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_12kb, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_12kb, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_heap_usage = lv_label_create(screen);
    lv_label_set_text(label_heap_usage, "Heap Usage");
    lv_obj_set_pos(label_heap_usage, 165, 264);
    lv_obj_set_style_text_align(label_heap_usage, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_heap_usage, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_heap_usage, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_7kb = lv_label_create(screen);
    lv_label_set_text(label_7kb, heap_size);
    lv_obj_set_pos(label_7kb, 415, 264);
    lv_obj_set_style_text_align(label_7kb, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_7kb, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_7kb, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_render_time = lv_label_create(screen);
    lv_label_set_text(label_render_time, "Render Time (Frame Latency)");
    lv_obj_set_pos(label_render_time, 165, 298);
    lv_obj_set_style_text_align(label_render_time, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_render_time, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_render_time, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_05ms = lv_label_create(screen);
    lv_label_set_text(label_05ms, render_time);
    lv_obj_set_pos(label_05ms, 415, 298);
    lv_obj_set_style_text_align(label_05ms, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_05ms, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_05ms, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_cpu_load = lv_label_create(screen);
    lv_label_set_text(label_cpu_load, "CPU Load %");
    lv_obj_set_pos(label_cpu_load, 165, 334);
    lv_obj_set_style_text_align(label_cpu_load, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_cpu_load, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_cpu_load, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_16 = lv_label_create(screen);
    lv_label_set_text(label_16, cpu_load);
    lv_obj_set_pos(label_16, 415, 334);
    lv_obj_set_style_text_align(label_16, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_16, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_16, lv_color_hex(0xFFFFFF), 0);

    // Create home button
    lv_obj_t *home_btn = lv_btn_create(screen);
    lv_obj_set_size(home_btn, 66, 66); // Width: 60px, Height: 64px
    lv_obj_set_pos(home_btn, 369, 378);
    lv_obj_set_style_radius(home_btn, LV_RADIUS_CIRCLE, 0);

    // Add image to home button
    lv_obj_t *home_img = lv_img_create(home_btn);
    lv_img_set_src(home_img, &home_icon); // Set the image source
    lv_obj_center(home_img); // Center the image within the button

    // Add event callback for home button
    lv_obj_add_event_cb(home_btn, static_param_home_cb, LV_EVENT_CLICKED, NULL);
}

void static_param_screen_init(char *test_label, char *frame_rate, char *stack_use, char *heap_size, char *render_time, char *cpu_load) {
    table_screen = lv_obj_create(NULL);
    create_static_param_screen(table_screen, test_label, frame_rate, stack_use, heap_size, render_time, cpu_load);
    main_scr_reset_menu();
    lv_scr_load(table_screen);
}
