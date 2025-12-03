/*
 * 2d_screen.c
 *
 *  Created on: Sep 30, 2025
 *      Author: prutha
 */

#include "2d_screen.h"
#include "parameter_display.h"
#include "benchmark_results.h"
#include <stdio.h>

LV_IMAGE_DECLARE(silicon_logo);

lv_obj_t *screen_2d;
lv_timer_t *close_timer;

static lv_obj_t *top_logos[3];
static lv_obj_t *bottom_logos[3];
static lv_anim_t anim_rotate;

static lv_timer_t *bottom_move_timer;
static int move_phase = 0;
static int step_count = 0;
static bool going_out = true;

static void hide_2d_screen_cb(lv_timer_t *timer)
{
	if(bottom_move_timer) lv_timer_del(bottom_move_timer);
    char fps_str[16], stack_str[16], heap_str[16], render_str[16], cpu_str[16];

    snprintf(fps_str, sizeof(fps_str), "%lu", avg_fps);
    snprintf(stack_str, sizeof(stack_str), "%lu KB", avg_stack_usage / 1024);
    snprintf(heap_str, sizeof(heap_str), "%lu KB", avg_heap_usage / 1024);
    snprintf(render_str, sizeof(render_str), "%lu ms", avg_render_time);
    snprintf(cpu_str, sizeof(cpu_str), "%lu %%", avg_cpu_usage);

    static_param_screen_init("2D Test", fps_str, stack_str, heap_str, render_str, cpu_str);


    if(screen_2d) {
        lv_obj_del(screen_2d);
        screen_2d = NULL;
    }

    move_phase = 0;
    step_count = 0;

    lv_timer_del(timer);
    close_timer = NULL;
}

static void rotate_exec_cb(void *obj, int32_t v)
{
    lv_img_set_angle((lv_obj_t *)obj, v);
}

// Move all bottom logos
static void move_bottom_logos(int dx, int dy)
{
    for (int i = 0; i < 3; i++) {
        lv_coord_t x = lv_obj_get_x(bottom_logos[i]);
        lv_coord_t y = lv_obj_get_y(bottom_logos[i]);
        lv_obj_set_pos(bottom_logos[i], x + dx, y + dy);
    }
}

// Timer callback to move bottom 3 logos
static void bottom_move_cb(lv_timer_t *timer)
{
    const int STEP_PX = 1;
    const int STEPS_PER_DIRECTION = 50;

    int dx = 0, dy = 0;

    if (going_out) {
        // Moving away from center
        switch (move_phase) {
            case 0: dy =  STEP_PX; break;
            case 1: dx =  STEP_PX; break;
            case 2: dx = -STEP_PX; break;
            case 3: dy = -STEP_PX; break;
        }
    } else {
        // Returning To center
        switch (move_phase) {
            case 0: dy = -STEP_PX; break;
            case 1: dx = -STEP_PX; break;
            case 2: dx =  STEP_PX; break;
            case 3: dy =  STEP_PX; break;
        }
    }

    move_bottom_logos(dx, dy);

    step_count++;

    if (step_count >= STEPS_PER_DIRECTION) {
        step_count = 0;
        if (!going_out) {
            move_phase = (move_phase + 1) % 4;
        }
        going_out = !going_out;
    }
}

// 2D Screen
void button_2d_event_cb(lv_event_t *e)
{
	demo_running = 1;

    screen_2d = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_2d, lv_color_hex(0x12294B), 0);
    lv_scr_load(screen_2d);

    // Placement parameters
    const int logo_w = 125;
    const int logo_h = 125;
    const int top_y = 57;
    const int bottom_y = 298;

    const int left_x = 65;
    const int center_x = 338;
    const int right_x = 601;

    // Create top 3 rotating logos
    top_logos[0] = lv_img_create(screen_2d);
    lv_img_set_src(top_logos[0], &silicon_logo);
    lv_obj_set_pos(top_logos[0], left_x, top_y);
    lv_img_set_pivot(top_logos[0], logo_w / 2, logo_h / 2);

    top_logos[1] = lv_img_create(screen_2d);
    lv_img_set_src(top_logos[1], &silicon_logo);
    lv_obj_set_pos(top_logos[1], center_x, top_y);
    lv_img_set_pivot(top_logos[1], logo_w / 2, logo_h / 2);

    top_logos[2] = lv_img_create(screen_2d);
    lv_img_set_src(top_logos[2], &silicon_logo);
    lv_obj_set_pos(top_logos[2], right_x, top_y);
    lv_img_set_pivot(top_logos[2], logo_w / 2, logo_h / 2);

    // Create bottom 3 logos (moving ones)
    bottom_logos[0] = lv_img_create(screen_2d);
    lv_img_set_src(bottom_logos[0], &silicon_logo);
    lv_obj_set_pos(bottom_logos[0], left_x, bottom_y);

    bottom_logos[1] = lv_img_create(screen_2d);
    lv_img_set_src(bottom_logos[1], &silicon_logo);
    lv_obj_set_pos(bottom_logos[1], center_x, bottom_y);

    bottom_logos[2] = lv_img_create(screen_2d);
    lv_img_set_src(bottom_logos[2], &silicon_logo);
    lv_obj_set_pos(bottom_logos[2], right_x, bottom_y);

    // Animate top 3 logos (rotate clockwise)
    for (int i = 0; i < 3; i++) {
        lv_anim_init(&anim_rotate);
        lv_anim_set_var(&anim_rotate, top_logos[i]);
        lv_anim_set_exec_cb(&anim_rotate, rotate_exec_cb);
        lv_anim_set_values(&anim_rotate, 0, 3600);
        lv_anim_set_time(&anim_rotate, 5000);
        lv_anim_set_repeat_count(&anim_rotate, LV_ANIM_REPEAT_INFINITE);
        lv_anim_start(&anim_rotate);
    }

    // Create timer for bottom 3 logos movement
    bottom_move_timer = lv_timer_create(bottom_move_cb, 20, NULL);
    lv_timer_set_repeat_count(bottom_move_timer, LV_ANIM_REPEAT_INFINITE);
    close_timer = lv_timer_create(hide_2d_screen_cb, 10000, NULL);
}
