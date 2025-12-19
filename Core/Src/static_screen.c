/*
 * static_screen.c
 *
 *  Created on: Sep 29, 2025
 *      Author: prutha
 */
#include <stdio.h>
#include "static_screen.h"
#include "parameter_display.h"
#include "benchmark_results.h"

// Shapes and timers
static lv_obj_t *circle;
static lv_obj_t *square;
static lv_obj_t *rectangle;
static lv_obj_t *alpha_circle;
static lv_obj_t *alpha_square;
static lv_obj_t *new_screen;

static lv_timer_t *color_timer;
static lv_timer_t *screen_timer;

static int color_index = 0;
static lv_obj_t *new_screen;

// Extern main_screen object
extern lv_obj_t *main_screen;

// Predefined colors
static lv_color_t square_color[3] = { LV_COLOR_MAKE(255,0,0), LV_COLOR_MAKE(0,255,0), LV_COLOR_MAKE(0,0,255) };
static lv_color_t circle_color[3] = { LV_COLOR_MAKE(0,255,0), LV_COLOR_MAKE(0,0,255), LV_COLOR_MAKE(255,0,0) };
static lv_color_t rectangle_color[3] = { LV_COLOR_MAKE(0,0,255), LV_COLOR_MAKE(255,0,0), LV_COLOR_MAKE(0,255,0) };

// Color Timer
// Separate indices for each shape
static int square_color_index = 0;
static int circle_color_index = 0;
static int rectangle_color_index = 0;

// Timer callback every 200ms
static void color_timer_cb(lv_timer_t * timer) {
    // Update square color
    lv_obj_set_style_bg_color(square, square_color[square_color_index], 0);
    lv_obj_set_style_bg_color(alpha_square, square_color[square_color_index], 0);
    square_color_index = (square_color_index + 1) % 3;

    // Update circle color
    lv_obj_set_style_bg_color(circle, circle_color[circle_color_index], 0);
    lv_obj_set_style_bg_color(alpha_circle, circle_color[circle_color_index], 0);
    circle_color_index = (circle_color_index + 1) % 3;

    // Update rectangle color
    lv_obj_set_style_bg_color(rectangle, rectangle_color[rectangle_color_index], 0);
    rectangle_color_index = (rectangle_color_index + 1) % 3;
}

// Return to home screen after 10s
static void auto_return_cb(lv_timer_t * timer) {
    if(color_timer) lv_timer_del(color_timer);
    char fps_str[16], stack_str[16], heap_str[16], render_str[16], cpu_str[16];

    snprintf(fps_str, sizeof(fps_str), "%lu", avg_fps);
    snprintf(stack_str, sizeof(stack_str), "%lu KB", avg_stack_usage / 1024);
    snprintf(heap_str, sizeof(heap_str), "%lu KB", avg_heap_usage / 1024);
    snprintf(render_str, sizeof(render_str), "%lu ms", avg_render_time);
    snprintf(cpu_str, sizeof(cpu_str), "%lu %%", avg_cpu_usage);

    static_param_screen_init("Static Test", fps_str, stack_str, heap_str, render_str, cpu_str);

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
	demo_running = 1;

    // Create new screen
    new_screen = lv_obj_create(NULL);

    // Square
    square = lv_obj_create(new_screen);
    lv_obj_set_size(square, 150, 150); // width = L, height = h.
    lv_obj_set_style_radius(square, 0, 0);
    lv_obj_set_pos(square, 141, 52);

    // Circle
    circle = lv_obj_create(new_screen);
    lv_obj_set_size(circle, 150, 150); // radius = 75, width = 75 * 2, height = 75 * 2.
    lv_obj_set_style_radius(circle, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_pos(circle, 141, 277);

    // Rectangle
    rectangle = lv_obj_create(new_screen);
    lv_obj_set_size(rectangle, 200, 100); // width = L, height = h.
    lv_obj_set_style_radius(rectangle, 0, 0);
    lv_obj_set_pos(rectangle, 466, 77);
    lv_obj_set_style_radius(rectangle, 20, 0);

    // Alpha Square
    alpha_square = lv_obj_create(new_screen);
    lv_obj_set_size(alpha_square, 150, 150); // width = L, height = h.
    lv_obj_set_pos(alpha_square, 482, 292);
    lv_obj_set_style_radius(alpha_square, 0, 0);
    lv_obj_set_style_bg_opa(alpha_square, 127, 0);
    lv_obj_set_style_border_width(alpha_square, 0, 0);

    // Alpha Circle
    alpha_circle = lv_obj_create(new_screen);
    lv_obj_set_size(alpha_circle, 150, 150); // radius = 75, width = 75 * 2, height = 75 * 2.
    lv_obj_set_style_radius(alpha_circle, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_pos(alpha_circle, 557, 217);
    lv_obj_set_style_bg_opa(alpha_circle, 127, 0);
    lv_obj_set_style_border_width(alpha_circle, 0, 0);

    // Load Screen
    lv_scr_load(new_screen);

    // Timers
    color_timer = lv_timer_create(color_timer_cb, 200, NULL);     // 200ms
    screen_timer = lv_timer_create(auto_return_cb, 10000, NULL);  // 10s
}
