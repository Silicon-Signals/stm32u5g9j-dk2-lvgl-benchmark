/*
 * static_screen.c
 *
 *  Created on: Sep 29, 2025
 *      Author: prutha
 */

#include "static_screen.h"
#include "parameter_display.h"

// Shapes and timers
static lv_obj_t *circle_obj;
static lv_obj_t *square_obj;
static lv_obj_t *rect_obj;
static lv_obj_t *alpha_circle_obj;
static lv_obj_t *alpha_square_obj;
static lv_timer_t *color_timer;
static lv_timer_t *screen_timer;
static int color_index = 0;
static lv_obj_t *new_screen;

// Extern main_screen object
extern lv_obj_t *main_screen;

// Predefined colors
static lv_color_t colors_sq[3] = { LV_COLOR_MAKE(255,0,0), LV_COLOR_MAKE(0,255,0), LV_COLOR_MAKE(0,0,255) };
static lv_color_t colors_ci[3] = { LV_COLOR_MAKE(0,255,0), LV_COLOR_MAKE(0,0,255), LV_COLOR_MAKE(255,0,0) };
static lv_color_t colors_re[3] = { LV_COLOR_MAKE(0,0,255), LV_COLOR_MAKE(255,0,0), LV_COLOR_MAKE(0,255,0) };

// Color Timer
// Separate indices for each shape
static int square_color_index = 0;
static int circle_color_index = 0;
static int rectangle_color_index = 0;

// Timer callback every 200ms
static void color_timer_cb(lv_timer_t * timer) {
    // Update square color
    lv_obj_set_style_bg_color(square_obj, colors_sq[square_color_index], 0);
    lv_obj_set_style_bg_color(alpha_square_obj, colors_sq[square_color_index], 0);
    square_color_index = (square_color_index + 1) % 3;

    // Update circle color
    lv_obj_set_style_bg_color(circle_obj, colors_ci[circle_color_index], 0);
    lv_obj_set_style_bg_color(alpha_circle_obj, colors_ci[circle_color_index], 0);
    circle_color_index = (circle_color_index + 1) % 3;

    // Update rectangle color
    lv_obj_set_style_bg_color(rect_obj, colors_re[rectangle_color_index], 0);
    rectangle_color_index = (rectangle_color_index + 1) % 3;
}

// Return to home screen after 10s
static void auto_return_cb(lv_timer_t * timer) {
    if(color_timer) lv_timer_del(color_timer);
    static_param_screen_init("Static Test", "28", "12 KB", "78 KB", "0.5 ms", "16 %");

    if(new_screen) {
        lv_obj_del(new_screen);
        new_screen = NULL;
    }

    lv_timer_del(timer);
    screen_timer = NULL;

    color_index = 0;
}

// Static Button Event
void static_button_event_cb(lv_event_t * e) {
    // Create new screen
    new_screen = lv_obj_create(NULL);

    // Square
    square_obj = lv_obj_create(new_screen);
    lv_obj_set_size(square_obj, 150, 150); // width = L, height = h.
    lv_obj_set_style_radius(square_obj, 0, 0);
    lv_obj_set_pos(square_obj, 141, 52);

    // Circle
    circle_obj = lv_obj_create(new_screen);
    lv_obj_set_size(circle_obj, 150, 150); // radius = 75, width = 75 * 2, height = 75 * 2.
    lv_obj_set_style_radius(circle_obj, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_pos(circle_obj, 141, 277);

    // Rectangle
    rect_obj = lv_obj_create(new_screen);
    lv_obj_set_size(rect_obj, 200, 100); // width = L, height = h.
    lv_obj_set_style_radius(rect_obj, 0, 0);
    lv_obj_set_pos(rect_obj, 466, 77);
    lv_obj_set_style_radius(rect_obj, 20, 0);

    // Alpha Square
    alpha_square_obj = lv_obj_create(new_screen);
    lv_obj_set_size(alpha_square_obj, 150, 150); // width = L, height = h.
    lv_obj_set_pos(alpha_square_obj, 482, 292);
    lv_obj_set_style_radius(alpha_square_obj, 0, 0);
    lv_obj_set_style_bg_opa(alpha_square_obj, 127, 0);
    lv_obj_set_style_border_width(alpha_square_obj, 0, 0);

    // Alpha Circle
    alpha_circle_obj = lv_obj_create(new_screen);
    lv_obj_set_size(alpha_circle_obj, 150, 150); // radius = 75, width = 75 * 2, height = 75 * 2.
    lv_obj_set_style_radius(alpha_circle_obj, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_pos(alpha_circle_obj, 557, 217);
    lv_obj_set_style_bg_opa(alpha_circle_obj, 127, 0);
    lv_obj_set_style_border_width(alpha_circle_obj, 0, 0);

    // Load Screen
    lv_scr_load(new_screen);

    // Timers
    color_timer = lv_timer_create(color_timer_cb, 200, NULL);     // 200ms
    screen_timer = lv_timer_create(auto_return_cb, 10000, NULL);  // 10s
}
