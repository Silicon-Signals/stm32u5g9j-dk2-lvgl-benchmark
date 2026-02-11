/*
 * parameter_display.c
 *
 * Created on: Oct 14, 2025
 * Author: prutha
 */

#include "parameter_display.h"
#include "benchmark_results.h"
#include "main_scr.h"
#include <string.h>
#include <stdio.h>

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

void static_param_screen_close(void) {
    if (table_screen) {
        lv_obj_del(table_screen);
        table_screen = NULL;
    }
}

static void create_static_param_screen(lv_obj_t * screen, char *test_label, char *ram_use, char *internal_flash_size, char *external_flash_size, char *render_time, char *cpu_load)
{
    // Set background image
    lv_obj_t *bg = lv_img_create(screen);
    lv_img_set_src(bg, &Table_Image);
    lv_obj_set_size(bg, 800, 480);
    lv_obj_align(bg, LV_ALIGN_TOP_LEFT, 0, 0);

    // Create text labels
    lv_obj_t *label_test = lv_label_create(screen);
    lv_label_set_text(label_test, "Test");
    lv_obj_set_pos(label_test, 165, 154);
    lv_obj_set_style_text_align(label_test, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(label_test, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(label_test, &lv_font_calibri_bold_18, 0);

    lv_obj_t *label_test_name = lv_label_create(screen);
    lv_label_set_text(label_test_name, test_label);
    lv_obj_set_pos(label_test_name, 415, 154);
    lv_obj_set_style_text_align(label_test_name, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(label_test_name, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(label_test_name, &lv_font_calibri_bold_18, 0);

    lv_obj_t *label_ram_usage = lv_label_create(screen);
    lv_label_set_text(label_ram_usage, "RAM Usage");
    lv_obj_set_pos(label_ram_usage, 165, 190);
    lv_obj_set_style_text_align(label_ram_usage, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_ram_usage, &lv_font_calibri_bold_18, 0);
    lv_obj_set_style_text_color(label_ram_usage, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_ram = lv_label_create(screen);
    lv_label_set_text(label_ram, ram_use);
    lv_obj_set_pos(label_ram, 415, 190);
    lv_obj_set_style_text_align(label_ram, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_ram, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_ram, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_internal_flash_usage = lv_label_create(screen);
    lv_label_set_text(label_internal_flash_usage, "Internal Flash Usage");
    lv_obj_set_pos(label_internal_flash_usage, 165, 226);
    lv_obj_set_style_text_align(label_internal_flash_usage, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_internal_flash_usage, &lv_font_calibri_bold_18, 0);
    lv_obj_set_style_text_color(label_internal_flash_usage, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_internal_flash = lv_label_create(screen);
    lv_label_set_text(label_internal_flash, internal_flash_size);
    lv_obj_set_pos(label_internal_flash, 415, 226);
    lv_obj_set_style_text_align(label_internal_flash, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_internal_flash, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_internal_flash, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_external_flash_usage = lv_label_create(screen);
    lv_label_set_text(label_external_flash_usage, "External Flash Usage");
    lv_obj_set_pos(label_external_flash_usage, 165, 262);
    lv_obj_set_style_text_align(label_external_flash_usage, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_external_flash_usage, &lv_font_calibri_bold_18, 0);
    lv_obj_set_style_text_color(label_external_flash_usage, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_external_flash = lv_label_create(screen);
    lv_label_set_text(label_external_flash, external_flash_size);
    lv_obj_set_pos(label_external_flash, 415, 262);
    lv_obj_set_style_text_align(label_external_flash, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_external_flash, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_external_flash, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_render_time = lv_label_create(screen);
    lv_label_set_text(label_render_time, "Render Time (Frame Latency)");
    lv_obj_set_pos(label_render_time, 165, 298);
    lv_obj_set_style_text_align(label_render_time, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_render_time, &lv_font_calibri_bold_18, 0);
    lv_obj_set_style_text_color(label_render_time, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_render = lv_label_create(screen);
    lv_label_set_text(label_render, render_time);
    lv_obj_set_pos(label_render, 415, 298);
    lv_obj_set_style_text_align(label_render, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_render, &lv_font_calibri_regular_18, 0);
    lv_obj_set_style_text_color(label_render, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_cpu_load = lv_label_create(screen);
    lv_label_set_text(label_cpu_load, "CPU Load %");
    lv_obj_set_pos(label_cpu_load, 165, 334);
    lv_obj_set_style_text_align(label_cpu_load, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_set_style_text_font(label_cpu_load, &lv_font_calibri_bold_18, 0);
    lv_obj_set_style_text_color(label_cpu_load, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t *label_cpu = lv_label_create(screen);
    lv_label_set_text(label_cpu, cpu_load);
    lv_obj_set_pos(label_cpu, 415, 334);
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
    if (current_mode == MODE_MANUAL) {
    	lv_obj_add_event_cb(home_btn, static_param_home_cb, LV_EVENT_CLICKED, NULL);
    } else {
        lv_obj_add_flag(home_btn, LV_OBJ_FLAG_HIDDEN);
    }
}

void static_param_screen_init(char *test_label) {
    if (table_screen) {
        lv_obj_del(table_screen);
        table_screen = NULL;
    }
    table_screen = lv_obj_create(NULL);

    char external_str[16], ram_str[16], render_str[16], cpu_str[16], internal_str[16];

    snprintf(external_str, sizeof(external_str), "%lu MB", external_usage / 1024);
    snprintf(internal_str, sizeof(internal_str), "%lu KB", internal_usage);
    snprintf(ram_str,  sizeof(ram_str),  "%lu KB", totalRamUsed);
    snprintf(render_str,sizeof(render_str),"%lu ms", avg_render_time);
    snprintf(cpu_str,   sizeof(cpu_str),   "%lu %%", avg_cpu_usage);

    create_static_param_screen(table_screen, test_label, ram_str, internal_str, external_str, render_str, cpu_str);
    main_scr_reset_menu();
    lv_scr_load(table_screen);
}
