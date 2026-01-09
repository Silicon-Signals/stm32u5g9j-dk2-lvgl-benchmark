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

static void create_static_param_screen(lv_obj_t * screen, char *test_label, char *frame_rate, char *ram_use, char *internal_flash_size, char *external_flash_size, char *render_time, char *cpu_load)
{
    // Set background image
    lv_obj_t *bg = lv_img_create(screen);
    lv_img_set_src(bg, &Table_Image);
    lv_obj_set_size(bg, 800, 480);
    lv_obj_align(bg, LV_ALIGN_TOP_LEFT, 0, 0);

    // Create text labels
    lv_obj_t *label_test = lv_label_create(screen);
    lv_label_set_text(label_test, "Test");
    lv_obj_set_pos(label_test, 165, 106);
    lv_obj_set_style_text_align(label_test, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(label_test, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(label_test, &lv_font_calibri_bold_18, 0);

    lv_obj_t *label_test_name = lv_label_create(screen);
    lv_label_set_text(label_test_name, test_label);
    lv_obj_set_pos(label_test_name, 415, 106);
    lv_obj_set_style_text_align(label_test_name, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(label_test_name, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(label_test_name, &lv_font_calibri_bold_18, 0);

    lv_obj_t *label_frame_rate = lv_label_create(screen);
    lv_label_set_text(label_frame_rate, "Frame Rate (FPS)");
    lv_obj_set_pos(label_frame_rate, 165, 142);
    lv_obj_set_style_text_align(label_frame_rate, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_frame_rate, &lv_font_calibri_bold_18, 0);
    lv_obj_set_style_text_color(label_frame_rate, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_frame = lv_label_create(screen);
    lv_label_set_text(label_frame, frame_rate);
    lv_obj_set_pos(label_frame, 415, 142);
    lv_obj_set_style_text_align(label_frame, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_frame, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_frame, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_ram_usage = lv_label_create(screen);
    lv_label_set_text(label_ram_usage, "RAM Usage");
    lv_obj_set_pos(label_ram_usage, 165, 178);
    lv_obj_set_style_text_align(label_ram_usage, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_ram_usage, &lv_font_calibri_bold_18, 0);
    lv_obj_set_style_text_color(label_ram_usage, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_ram = lv_label_create(screen);
    lv_label_set_text(label_ram, ram_use);
    lv_obj_set_pos(label_ram, 415, 178);
    lv_obj_set_style_text_align(label_ram, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_ram, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_ram, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_internal_flash_usage = lv_label_create(screen);
    lv_label_set_text(label_internal_flash_usage, "Internal Flash Usage");
    lv_obj_set_pos(label_internal_flash_usage, 165, 214);
    lv_obj_set_style_text_align(label_internal_flash_usage, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_internal_flash_usage, &lv_font_calibri_bold_18, 0);
    lv_obj_set_style_text_color(label_internal_flash_usage, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_internal_flash = lv_label_create(screen);
    lv_label_set_text(label_internal_flash, internal_flash_size);
    lv_obj_set_pos(label_internal_flash, 415, 214);
    lv_obj_set_style_text_align(label_internal_flash, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_internal_flash, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_internal_flash, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_external_flash_usage = lv_label_create(screen);
    lv_label_set_text(label_external_flash_usage, "External Flash Usage");
    lv_obj_set_pos(label_external_flash_usage, 165, 250);
    lv_obj_set_style_text_align(label_external_flash_usage, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_external_flash_usage, &lv_font_calibri_bold_18, 0);
    lv_obj_set_style_text_color(label_external_flash_usage, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_external_flash = lv_label_create(screen);
    lv_label_set_text(label_external_flash, external_flash_size);
    lv_obj_set_pos(label_external_flash, 415, 250);
    lv_obj_set_style_text_align(label_external_flash, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_external_flash, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_external_flash, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_render_time = lv_label_create(screen);
    lv_label_set_text(label_render_time, "Render Time (Frame Latency)");
    lv_obj_set_pos(label_render_time, 165, 286);
    lv_obj_set_style_text_align(label_render_time, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_render_time, &lv_font_calibri_bold_18, 0);
    lv_obj_set_style_text_color(label_render_time, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_render = lv_label_create(screen);
    lv_label_set_text(label_render, render_time);
    lv_obj_set_pos(label_render, 415, 286);
    lv_obj_set_style_text_align(label_render, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_render, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_render, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_cpu_load = lv_label_create(screen);
    lv_label_set_text(label_cpu_load, "CPU Load %");
    lv_obj_set_pos(label_cpu_load, 165, 322);
    lv_obj_set_style_text_align(label_cpu_load, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_cpu_load, &lv_font_calibri_bold_18, 0);
    lv_obj_set_style_text_color(label_cpu_load, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_cpu = lv_label_create(screen);
    lv_label_set_text(label_cpu, cpu_load);
    lv_obj_set_pos(label_cpu, 415, 322);
    lv_obj_set_style_text_align(label_cpu, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_cpu, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_cpu, lv_color_hex(0xFFFFFF), 0);

    // Create home button
    lv_obj_t *home_btn = lv_btn_create(screen);
    lv_obj_remove_style_all(home_btn);

    lv_obj_set_size(home_btn, 65, 65);
    lv_obj_set_pos(home_btn, 369, 378);
    lv_obj_set_style_radius(home_btn, LV_RADIUS_CIRCLE, 0);

    // Add the image
    lv_obj_t *home_img = lv_img_create(home_btn);
    lv_img_set_src(home_img, &home_icon);
    lv_obj_align(home_img, LV_ALIGN_CENTER, 0, 0);

    // Add event callback for home button
    lv_obj_add_event_cb(home_btn, static_param_home_cb, LV_EVENT_CLICKED, NULL);
}

void static_param_screen_init(char *test_label, char *frame_rate, char *ram_use, char *internal_flash_size, char *external_flash_size, char *render_time, char *cpu_load) {
    table_screen = lv_obj_create(NULL);
    create_static_param_screen(table_screen, test_label, frame_rate, ram_use, internal_flash_size, external_flash_size, render_time, cpu_load);
    main_scr_reset_menu();
    lv_scr_load(table_screen);
}
