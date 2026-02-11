/*
 * 2d_screen.c
 *
 *  Created on: Sep 30, 2025
 *      Author: prutha
 */

#include <stdio.h>
#include "2d_screen.h"
#include "parameter_display.h"
#include "benchmark_results.h"

LV_IMAGE_DECLARE(siliconsignals_logo);

lv_obj_t *screen_2d;
lv_timer_t *close_timer;

static lv_obj_t *Img_rotate[3];
static lv_obj_t *Img_move[3];
static lv_anim_t anim_rotate;

static lv_timer_t *Img_move_timer;
static int direction_index = 0;
static int current_step = 0;
static bool outward_motion = true;

static void hide_2d_screen_cb(lv_timer_t *timer)
{
	if(Img_move_timer) lv_timer_del(Img_move_timer);

    static_param_screen_init("2D Test");

    if(screen_2d) {
        lv_obj_del(screen_2d);
        screen_2d = NULL;
    }

    direction_index = 0;
    current_step = 0;
    outward_motion = true;

    lv_timer_del(timer);
    close_timer = NULL;
}

static void Img_rotate_cb(void *obj, int32_t v)
{
    lv_img_set_angle((lv_obj_t *)obj, v);
}

// Move all bottom logos
static void move_bottom_logos(int dx, int dy)
{
    for (int i = 0; i < 3; i++) {
        lv_coord_t x = lv_obj_get_x(Img_move[i]);
        lv_coord_t y = lv_obj_get_y(Img_move[i]);
        lv_obj_set_pos(Img_move[i], x + dx, y + dy);
    }
}

// Timer callback to move bottom 3 logos
static void Img_move_cb(lv_timer_t *timer)
{
    const int MOVE_STEP_PIXELS = 1;
    const int STEPS_PER_MOVE = 50;

    int delta_x = 0;
    int delta_y = 0;

    /* ------------------------------------------------------------
     * outward_motion: true  → moving away from origin
     *                  false → returning back to origin
     * direction_index: 0 = up, 1 = down, 2 = left, 3 = right
     * ------------------------------------------------------------
     */
    if (outward_motion) {
        switch (direction_index) {
            case 0: delta_y = -MOVE_STEP_PIXELS; break;   // Move Up
            case 1: delta_y =  MOVE_STEP_PIXELS; break;   // Move Down
            case 2: delta_x = -MOVE_STEP_PIXELS; break;   // Move Left
            case 3: delta_x =  MOVE_STEP_PIXELS; break;   // Move Right
        }
    }
    else {
        switch (direction_index) {
            case 0: delta_y =  MOVE_STEP_PIXELS; break;   // Return Down
            case 1: delta_y = -MOVE_STEP_PIXELS; break;   // Return Up
            case 2: delta_x =  MOVE_STEP_PIXELS; break;   // Return Right
            case 3: delta_x = -MOVE_STEP_PIXELS; break;   // Return Left
        }
    }

    // Apply movement
    move_bottom_logos(delta_x, delta_y);

    // Step counter
    current_step++;

    if (current_step >= STEPS_PER_MOVE) {
        current_step = 0;

        // When returning phase finishes → change direction
        if (!outward_motion) {
            direction_index = (direction_index + 1) % 4;
        }

        // Toggle outward <-> return
        outward_motion = !outward_motion;
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
    Img_rotate[0] = lv_img_create(screen_2d);
    lv_img_set_src(Img_rotate[0], &siliconsignals_logo);
    lv_obj_set_pos(Img_rotate[0], left_x, top_y);
    lv_img_set_pivot(Img_rotate[0], logo_w / 2, logo_h / 2);

    Img_rotate[1] = lv_img_create(screen_2d);
    lv_img_set_src(Img_rotate[1], &siliconsignals_logo);
    lv_obj_set_pos(Img_rotate[1], center_x, top_y);
    lv_img_set_pivot(Img_rotate[1], logo_w / 2, logo_h / 2);

    Img_rotate[2] = lv_img_create(screen_2d);
    lv_img_set_src(Img_rotate[2], &siliconsignals_logo);
    lv_obj_set_pos(Img_rotate[2], right_x, top_y);
    lv_img_set_pivot(Img_rotate[2], logo_w / 2, logo_h / 2);

    // Create bottom 3 logos (moving ones)
    Img_move[0] = lv_img_create(screen_2d);
    lv_img_set_src(Img_move[0], &siliconsignals_logo);
    lv_obj_set_pos(Img_move[0], left_x, bottom_y);

    Img_move[1] = lv_img_create(screen_2d);
    lv_img_set_src(Img_move[1], &siliconsignals_logo);
    lv_obj_set_pos(Img_move[1], center_x, bottom_y);

    Img_move[2] = lv_img_create(screen_2d);
    lv_img_set_src(Img_move[2], &siliconsignals_logo);
    lv_obj_set_pos(Img_move[2], right_x, bottom_y);

    // Animate top 3 logos (rotate clockwise)
    for (int i = 0; i < 3; i++) {
        lv_anim_init(&anim_rotate);
        lv_anim_set_var(&anim_rotate, Img_rotate[i]);
        lv_anim_set_exec_cb(&anim_rotate, Img_rotate_cb);
        lv_anim_set_values(&anim_rotate, 0, 3600);
        lv_anim_set_time(&anim_rotate, 5000);
        lv_anim_set_repeat_count(&anim_rotate, LV_ANIM_REPEAT_INFINITE);
        lv_anim_start(&anim_rotate);
    }

    // Create timer for bottom 3 logos movement
    Img_move_timer = lv_timer_create(Img_move_cb, 17, NULL);
    lv_timer_set_repeat_count(Img_move_timer, LV_ANIM_REPEAT_INFINITE);
    close_timer = lv_timer_create(hide_2d_screen_cb, 10000, NULL);
}
