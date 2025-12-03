/*
 * my_perf_monitor.c
 *
 *  Created on: Nov 20, 2025
 *      Author: prutha
 */

#include <perf_monitor.h>
#include <stdio.h>
#include <stdint.h>

lv_obj_t *perf_box;
lv_obj_t *perf_label;

extern volatile uint32_t render_time;
extern uint8_t cpu;
extern uint8_t fps;

void perf_monitor_create(void)
{
    lv_obj_t *top = lv_layer_top();

    perf_box = lv_obj_create(top);
    lv_obj_set_size(perf_box, 120, 30);

    lv_obj_set_align(perf_box, LV_ALIGN_BOTTOM_RIGHT);

    lv_obj_set_style_bg_color(perf_box, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(perf_box, LV_OPA_50, 0);
    lv_obj_set_style_border_width(perf_box, 0, 0);
    lv_obj_set_style_pad_all(perf_box, 0, 0);
    lv_obj_set_style_radius(perf_box, 0, 0);

    perf_label = lv_label_create(perf_box);

    lv_obj_set_size(perf_label, 120, 30);
    lv_obj_set_style_text_color(perf_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(perf_label, &lv_font_calibri_regular_15, 0);
    lv_label_set_text(perf_label, " 00 FPS, 00%CPU\n 00 ms");

    lv_obj_set_style_text_align(perf_label, LV_TEXT_ALIGN_LEFT, 0);
    lv_obj_align(perf_label, LV_ALIGN_CENTER, 0, 0);
}

void perf_monitor_update(lv_timer_t *t)
{
    lv_label_set_text_fmt(perf_label, " %02u FPS, %02u%%CPU\n %02" LV_PRIu32 " ms", fps, cpu, render_time);
}

void perf_monitor_start(void)
{
    // Update every 1000 ms
    lv_timer_create(perf_monitor_update, 1000, NULL);
}
