/*
 * 2d_screen.c
 *
 *  Created on: Sep 30, 2025
 *      Author: prutha
 */

#include "2d_screen.h"
#include "parameter_display.h"

LV_IMAGE_DECLARE(silicon_logo);

lv_obj_t *screen_2d;
lv_timer_t *close_timer;

static lv_obj_t *top_logos[3];
static lv_obj_t *bottom_logos[3];
static lv_anim_t anim_rotate;

static lv_timer_t *bottom_move_timer;
static int move_phase = 0;

static void hide_2d_screen_cb(lv_timer_t *timer)
{
	if(bottom_move_timer) lv_timer_del(bottom_move_timer);
    static_param_screen_init("2D test", "28", "12 KB", "78 KB", "0.5 ms", "15 %");

    if(screen_2d) {
        lv_obj_del(screen_2d);
        screen_2d = NULL;
    }

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
    const int step = 5;
    const int max_distance = 10;
    const int pause_duration = 15;

    static int move_count = 0;
    static bool returning = false;
    static int pause_count = 0;
    static bool pausing = false;

    if (pausing) {
    	pause_count++;
    	if (pause_count >= pause_duration) {
    		pausing = false;
    		pause_count = 0;
    		move_phase = (move_phase + 1) % 4;
    	}
    	return;
    }

    if (!returning) {
        // Moving away from original position
        switch (move_phase) {
            case 0: // Down
                move_bottom_logos(0, step);
                break;
            case 1: // Right
                move_bottom_logos(step, 0);
                break;
            case 2: // Left
                move_bottom_logos(-step, 0);
                break;
            case 3: // Up
                move_bottom_logos(0, -step);
                break;
        }
        move_count++;

        // When max distance reached, start returning
        if (move_count >= max_distance) {
            returning = true;
            move_count = 0;
        }
    } else {
        // Moving back to original position
        switch (move_phase) {
            case 0: // Return from Down
                move_bottom_logos(0, -step);
                break;
            case 1: // Return from Right
                move_bottom_logos(-step, 0);
                break;
            case 2: // Return from Left
                move_bottom_logos(step, 0);
                break;
            case 3: // Return from Up
                move_bottom_logos(0, step);
                break;
        }
        move_count++;

        // When returned to original position, move to next phase
        if (move_count >= max_distance) {
                    returning = false;
                    move_count = 0;
                    pausing = true;
                    pause_count = 0;
        }
    }
}

// 2D Screen
void button_2d_event_cb(lv_event_t *e)
{
    // Create new screen
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
