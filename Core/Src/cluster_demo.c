/*
 * cluster_demo.c
 *
 *  Created on: Nov 17, 2025
 *      Author: prutha
 */

#include "cluster_demo.h"
#include "parameter_display.h"
#include "benchmark_results.h"
#include <stdio.h>
#include "stm32u5xx.h"

// Frames
const lv_image_dsc_t *left_frames[40] = {
    &left_frame_000, &left_frame_001, &left_frame_002, &left_frame_003,
    &left_frame_004, &left_frame_005, &left_frame_006, &left_frame_007,
    &left_frame_008, &left_frame_009, &left_frame_010, &left_frame_011,
    &left_frame_012, &left_frame_013, &left_frame_014, &left_frame_015,
    &left_frame_016, &left_frame_017, &left_frame_018, &left_frame_019,
    &left_frame_020, &left_frame_021, &left_frame_022, &left_frame_023,
    &left_frame_024, &left_frame_025, &left_frame_026, &left_frame_027,
    &left_frame_028, &left_frame_029, &left_frame_030, &left_frame_031,
    &left_frame_032, &left_frame_033, &left_frame_034, &left_frame_035,
    &left_frame_036, &left_frame_037, &left_frame_038, &left_frame_039,
};
const lv_image_dsc_t *right_frames[40] = {
    &right_frame_000, &right_frame_001, &right_frame_002, &right_frame_003,
    &right_frame_004, &right_frame_005, &right_frame_006, &right_frame_007,
    &right_frame_008, &right_frame_009, &right_frame_010, &right_frame_011,
    &right_frame_012, &right_frame_013, &right_frame_014, &right_frame_015,
    &right_frame_016, &right_frame_017, &right_frame_018, &right_frame_019,
    &right_frame_020, &right_frame_021, &right_frame_022, &right_frame_023,
    &right_frame_024, &right_frame_025, &right_frame_026, &right_frame_027,
    &right_frame_028, &right_frame_029, &right_frame_030, &right_frame_031,
    &right_frame_032, &right_frame_033, &right_frame_034, &right_frame_035,
    &right_frame_036, &right_frame_037, &right_frame_038, &right_frame_039,
};

// Objects
static lv_obj_t *scr;
static lv_obj_t *bg_img;
static lv_obj_t *left_img;
static lv_obj_t *right_img;

static lv_obj_t *left_ind;
static lv_obj_t *right_ind;
static lv_obj_t *dipper_img;
static lv_obj_t *engine_img;
static lv_obj_t *service_img;
static lv_obj_t *battery_icon;
static lv_obj_t *battery_arc;
static lv_obj_t *fuel_icon;
static lv_obj_t *notif_box;
static lv_obj_t *notif_box_fuel;

static lv_obj_t *label_kmh_text;
static lv_obj_t *label_kmh_value;
static lv_obj_t *label_rpm_text;
static lv_obj_t *label_rpm_value;
static lv_obj_t *label_gear_text;
static lv_obj_t *label_gear_value;
static lv_obj_t *label_total_text;
static lv_obj_t *label_total_value;

static lv_timer_t *anim_timer;
static uint32_t demo_start_ms = 0;
static uint32_t indicatorTimer = 0;

static lv_obj_t *fuel_img;
static int fuel_index = 0;
static int fuelTimer = 0;

typedef enum {
    Forward1,
    Reverse1,
    Forward2,
    Reverse2,
    Forward3
} Phase;

static Phase phase = Forward1;
static int leftAnimFrame = 0;


static void cleanup_and_exit(void)
{
    if (anim_timer) {
        lv_timer_del(anim_timer);
        anim_timer = NULL;
    }

    char fps_str[16], stack_str[16], heap_str[16], render_str[16], cpu_str[16];
    snprintf(fps_str,  sizeof(fps_str),  "%lu", avg_fps);
    snprintf(stack_str, sizeof(stack_str), "%lu KB", avg_stack_usage / 1024);
    snprintf(heap_str,  sizeof(heap_str),  "%lu KB", avg_heap_usage / 1024);
    snprintf(render_str,sizeof(render_str),"%lu ms", avg_render_time);
    snprintf(cpu_str,   sizeof(cpu_str),   "%lu %%", avg_cpu_usage);

    static_param_screen_init("Cluster Test", fps_str, stack_str, heap_str, render_str, cpu_str);

    if (scr) {
        lv_obj_del(scr);
        scr = NULL;
    }

    // Reset all state
    demo_start_ms = 0;
    indicatorTimer = 0;
    fuel_index = 0;
    fuelTimer = 0;
    leftAnimFrame = 0;
    phase = Forward1;
}

static inline void set_icon(lv_obj_t *obj, const lv_image_dsc_t *normal, const lv_image_dsc_t *colored, bool on)
{
    lv_image_set_src(obj, on ? colored : normal);
}

static void cluster_anim_cb(lv_timer_t *t)
{
    uint32_t now = HAL_GetTick();
    uint32_t elapsed_ms = now - demo_start_ms;

    static uint32_t last_frame_update = 0;
    if (now - last_frame_update >= 100) {
        last_frame_update = now;

        switch (phase) {
            case Forward1:  if (++leftAnimFrame >= 39) phase = Reverse1;  break;
            case Reverse1:  if (--leftAnimFrame <= 13) phase = Forward2; break;
            case Forward2:  if (++leftAnimFrame >= 30) phase = Reverse2; break;
            case Reverse2:  if (--leftAnimFrame <= 3)  phase = Forward3; break;
            case Forward3:  if (++leftAnimFrame >= 21) phase = Forward1; break;
        }
        lv_image_set_src(left_img, left_frames[leftAnimFrame]);
    }

    // INDICATOR TIMELINE
    bool left_on  = true;
    bool right_on = false;
    uint32_t cycle = elapsed_ms % 6000;
    if (cycle >= 2000 && cycle < 4000) left_on = false;
    if (cycle >= 2000 && cycle < 4000) right_on = true;
    if (cycle >= 4000 && cycle < 6000) { left_on = true; right_on = true; }

    // Dipper Blink at 8s and 15s
    bool dipper_on = false;
    if ((elapsed_ms >= 8000 && elapsed_ms < 10000) || (elapsed_ms >= 15000 && elapsed_ms < 17000)) {
        dipper_on = ((elapsed_ms / 500) % 2) == 0;
    }

    // Battery Arc
    if (elapsed_ms < 5000) {
    	lv_image_set_src(battery_arc, &battery_full);
    } else if (elapsed_ms < 9000) {
    	lv_image_set_src(battery_arc, &battery_50);
    } else {
    	lv_image_set_src(battery_arc, &battery_low);
    }

    // Notifications
    if (elapsed_ms >= 9000) {
    	lv_obj_clear_flag(notif_box, LV_OBJ_FLAG_HIDDEN);
    }
    if (elapsed_ms >= 10000)
    	lv_obj_add_flag(notif_box, LV_OBJ_FLAG_HIDDEN);

    bool service_on = (elapsed_ms >= 10000);
    bool engine_on  = (elapsed_ms >= 15000);
    bool fuel_on    = (elapsed_ms >= 10000);
    bool battery_on = (elapsed_ms >= 9000);

    set_icon(left_ind,     &left_indicator,     &left_indicator_colored,  left_on);
    set_icon(right_ind,    &right_indicator,    &right_indicator_colored, right_on);
    set_icon(dipper_img,   &dipper,             &dipper_colored,          dipper_on);
    set_icon(engine_img,   &engine,             &engine_colored,          engine_on);
    set_icon(service_img,  &service,            &service_colored,         service_on);
    set_icon(battery_icon, &battery_colored,    &battery_40,              battery_on);
    set_icon(fuel_icon,    &fuel,               &Fuel_icon,               fuel_on);

    // Speed & Gear
    int gearValue = 0;
    int kmhValue = 0;
    if (leftAnimFrame <= 4) {
    	gearValue = 1;
    	kmhValue = 3  + leftAnimFrame * 8;
    } else if (leftAnimFrame <= 10) {
    	gearValue = 2;
    	kmhValue = 10 + (leftAnimFrame-4)*15;
    } else if (leftAnimFrame <= 20) {
    	gearValue = 3;
    	kmhValue = 30 + (leftAnimFrame-10)*20/10;
    } else if (leftAnimFrame <= 30) {
    	gearValue = 4;
    	kmhValue = 50 + (leftAnimFrame-20)*30/10;
    } else {
    	gearValue = 5;
    	kmhValue = 80 + (leftAnimFrame-30)*40/9;
    }

    // RPM Needle
    int rpmPercent = (kmhValue * 100) / 120;
    if (rpmPercent > 100) rpmPercent = 100;
    lv_image_set_src(right_img, right_frames[(rpmPercent * 39) / 100]);

    if (elapsed_ms >= 13000 && elapsed_ms < 16000) {
        lv_image_set_src(fuel_img, &Fuel_80);
    }
    else if (elapsed_ms >= 16000 && elapsed_ms < 19000) {
        lv_image_set_src(fuel_img, &Fuel_50);
    }
    else if (elapsed_ms >= 19000) {
        lv_image_set_src(fuel_img, &Low_fuel);
        lv_obj_clear_flag(notif_box_fuel, LV_OBJ_FLAG_HIDDEN);
    }

    lv_label_set_text_fmt(label_total_value, " %ld KM", (elapsed_ms * 200) / 20000);
    lv_label_set_text_fmt(label_kmh_value, "%d", kmhValue);
    lv_label_set_text_fmt(label_rpm_value, "%d", rpmPercent);
    lv_label_set_text_fmt(label_gear_value, "%d", gearValue);

    if (elapsed_ms >= 20000) {
        cleanup_and_exit();
        return;
    }
}

// Demo Start
void cluster_demo_start(void)
{
    scr = lv_obj_create(NULL);
    lv_scr_load(scr);

    // Background
    bg_img = lv_image_create(scr);
    lv_image_set_src(bg_img, &cluster_bg);
    lv_obj_set_pos(bg_img, 0, 0);

    // Main Frames
    left_img  = lv_image_create(scr);
    right_img = lv_image_create(scr);
    lv_obj_set_pos(left_img,  -10, 98);
    lv_obj_set_pos(right_img, 511, 98);

    // Icons
    left_ind = lv_image_create(scr);
    lv_obj_set_pos(left_ind, 181, 30);
    lv_image_set_src(left_ind, &left_indicator);

    right_ind = lv_image_create(scr);
    lv_obj_set_pos(right_ind, 569, 30);
    lv_image_set_src(right_ind, &right_indicator);

    dipper_img = lv_image_create(scr);
    lv_obj_set_pos(dipper_img, 273, 30);
    lv_image_set_src(dipper_img, &dipper);

    engine_img = lv_image_create(scr);
    lv_obj_set_pos(engine_img, 371, 30);
    lv_image_set_src(engine_img, &engine);

    service_img = lv_image_create(scr);
    lv_obj_set_pos(service_img, 478, 30);
    lv_image_set_src(service_img, &service);

    fuel_img = lv_img_create(scr);
    lv_image_set_src(fuel_img, &Full_fuel);
    lv_obj_set_pos(fuel_img, 30, 430);

    fuel_icon = lv_img_create(scr);
    lv_image_set_src(fuel_icon, &fuel);
    lv_obj_set_pos(fuel_icon, 184, 422);

    battery_arc = lv_img_create(scr);
    lv_image_set_src(battery_arc, &battery_full);
    lv_obj_set_pos(battery_arc, 614, 272);

    battery_icon = lv_img_create(scr);
    lv_image_set_src(battery_icon, &battery_colored);
    lv_obj_set_pos(battery_icon, 740, 349);

    // LOW BATTERY NOTIFICATION
    notif_box = lv_obj_create(scr);
    lv_obj_set_size(notif_box, 200, 50);
    lv_obj_set_style_bg_color(notif_box, lv_color_white(), 0);
    lv_obj_set_style_radius(notif_box, 0, 0);
    lv_obj_set_pos(notif_box, 300, 20);
    lv_obj_add_flag(notif_box, LV_OBJ_FLAG_HIDDEN);

    // Inner red box (5px margin)
    lv_obj_t *inner = lv_obj_create(notif_box);
    lv_obj_set_size(inner, 190, 40);
    lv_obj_set_style_bg_color(inner, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_radius(inner, 0, 0);
    lv_obj_align(inner, LV_ALIGN_CENTER, 0, 0);

    // Battery icon (left center inside red box)
    lv_obj_t *notif_icon = lv_img_create(inner);
    lv_img_set_src(notif_icon, &battery);
    lv_obj_align(notif_icon, LV_ALIGN_LEFT_MID, -20, 0);

    // Text
    lv_obj_t *notif_label = lv_label_create(inner);
    lv_label_set_text(notif_label, "Low Battery !!");
    lv_obj_set_style_text_color(notif_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(notif_label, &lv_font_calibri_bold_25, 0);
    lv_obj_align(notif_label, LV_ALIGN_LEFT_MID, 10, 0);

    notif_box_fuel = lv_obj_create(scr);
    lv_obj_set_size(notif_box_fuel, 200, 70);
    lv_obj_set_style_bg_color(notif_box_fuel, lv_color_white(), 0);
    lv_obj_set_style_radius(notif_box_fuel, 0, 0);
    lv_obj_set_pos(notif_box_fuel, 300, 20);
    lv_obj_add_flag(notif_box_fuel, LV_OBJ_FLAG_HIDDEN);

    // Inner red box (5px margin)
    lv_obj_t *inner_fuel = lv_obj_create(notif_box_fuel);
    lv_obj_set_size(inner_fuel, 190, 60);
    lv_obj_set_style_bg_color(inner_fuel, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_radius(inner_fuel, 0, 0);
    lv_obj_align(inner_fuel, LV_ALIGN_CENTER, 0, 0);

    // Battery icon (left center inside red box)
    lv_obj_t *notif_icon_fuel = lv_img_create(inner_fuel);
    lv_img_set_src(notif_icon_fuel, &fuel);
    lv_obj_align(notif_icon_fuel, LV_ALIGN_LEFT_MID, -20, 0);

    // Text
    lv_obj_t *notif_label_fuel = lv_label_create(inner_fuel);
    lv_label_set_text(notif_label_fuel, "Low Fuel\nPlease refuel");
    lv_obj_set_style_text_color(notif_label_fuel, lv_color_white(), 0);
    lv_obj_set_style_text_font(notif_label_fuel, &lv_font_calibri_bold_25, 0);
    lv_obj_align(notif_label_fuel, LV_ALIGN_LEFT_MID, 15, 0);

    // Text Labels
    label_kmh_text  = lv_label_create(scr);
    lv_label_set_text(label_kmh_text, "KM/H");
    lv_obj_set_pos(label_kmh_text, 181, 248);
    lv_obj_set_style_text_color(label_kmh_text, lv_color_white(), 0);
    lv_obj_set_style_text_font(label_kmh_text, &lv_font_digital_italic_30, 0);

    label_kmh_value = lv_label_create(scr);
    lv_label_set_text(label_kmh_value, "0");
    lv_obj_set_pos(label_kmh_value, 188, 194);
    lv_obj_set_style_text_color(label_kmh_value, lv_color_white(), 0);
    lv_obj_set_style_text_font(label_kmh_value, &lv_font_digital_italic_55, 0);

    label_rpm_text  = lv_label_create(scr);
    lv_label_set_text(label_rpm_text, "%RPM");
    lv_obj_set_pos(label_rpm_text, 564, 248);
    lv_obj_set_style_text_color(label_rpm_text, lv_color_white(), 0);
    lv_obj_set_style_text_font(label_rpm_text, &lv_font_digital_italic_30, 0);

    label_rpm_value = lv_label_create(scr);
    lv_label_set_text(label_rpm_value, "0");
    lv_obj_set_pos(label_rpm_value, 575, 194);
    lv_obj_set_style_text_color(label_rpm_value, lv_color_white(), 0);
    lv_obj_set_style_text_font(label_rpm_value, &lv_font_digital_italic_55, 0);

    label_gear_text  = lv_label_create(scr);
    lv_label_set_text(label_gear_text, "GEAR");
    lv_obj_set_pos(label_gear_text, 375, 172);
    lv_obj_set_style_text_color(label_gear_text, lv_color_white(), 0);
    lv_obj_set_style_text_font(label_gear_text, &lv_font_digital_italic_30, 0);

    label_gear_value = lv_label_create(scr);
    lv_label_set_text(label_gear_value, "0");
    lv_obj_set_pos(label_gear_value, 388, 116);
    lv_obj_set_style_text_color(label_gear_value, lv_color_white(), 0);
    lv_obj_set_style_text_font(label_gear_value, &lv_font_digital_italic_55, 0);

    label_total_text  = lv_label_create(scr);
    lv_label_set_text(label_total_text, "TOTAL :");
    lv_obj_set_pos(label_total_text, 326, 425);
    lv_obj_set_style_text_color(label_total_text, lv_color_white(), 0);
    lv_obj_set_style_text_font(label_total_text, &lv_font_digital_italic_30, 0);

    label_total_value = lv_label_create(scr);
    lv_label_set_text(label_total_value, " 0 KM");
    lv_obj_set_pos(label_total_value, 411, 425);
    lv_obj_set_style_text_color(label_total_value, lv_color_white(), 0);
    lv_obj_set_style_text_font(label_total_value, &lv_font_digital_italic_30, 0);

    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);

    demo_start_ms = HAL_GetTick();

    // Reset state
    fuel_index = 0;
    fuelTimer = 0;
    leftAnimFrame = 0;
    phase = Forward1;

    anim_timer = lv_timer_create(cluster_anim_cb, 25, NULL);
}

void cluster_button_event_cb(lv_event_t *e)
{
	cluster_running = 1;
	cluster_demo_start();
}
