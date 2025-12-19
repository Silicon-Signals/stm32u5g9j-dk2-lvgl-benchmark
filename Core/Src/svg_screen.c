/*
 * svg_screen.c
 *
 *  Created on: Oct 23, 2025
 *      Author: prutha
 */
#include <stdio.h>
#include "parameter_display.h"
#include "svg_screen.h"
#include "benchmark_results.h"
#include "svg_strings.h"

extern const lv_image_dsc_t car_body;
extern const lv_image_dsc_t ellipse;

extern const lv_image_dsc_t tire1;
extern const lv_image_dsc_t tire2;
extern const lv_image_dsc_t tire3;
extern const lv_image_dsc_t tire4;
extern const lv_image_dsc_t tire5;

extern const lv_image_dsc_t tire_pair1;
extern const lv_image_dsc_t tire_pair2;
extern const lv_image_dsc_t tire_pair3;
extern const lv_image_dsc_t tire_pair4;
extern const lv_image_dsc_t tire_pair5;

// Function prototypes
static void shift_callback(lv_timer_t *timer);

// Global variables
lv_obj_t *screen_svg;
static lv_obj_t *tires[5];
static lv_obj_t *car_tire_image;
lv_timer_t *svg_timer;
lv_timer_t *car_tier;
static int pos_idx[5] = {4, 3, 2, 1, 0};

static lv_point_t positions[5] = {
		{670, 60},
		{550, 150},
		{400, 185},
		{250, 150},
		{130, 60}
};

static const lv_img_dsc_t *tire_images[5] = {&tire_pair4, &tire_pair5, &tire_pair1, &tire_pair2, &tire_pair3};
static int tire_w, tire_h;

static void hide_svg_screen_cb(lv_timer_t *timer) {
     if(car_tier) lv_timer_del(car_tier);
     char fps_str[16], stack_str[16], heap_str[16], render_str[16], cpu_str[16];

     snprintf(fps_str, sizeof(fps_str), "%lu", avg_fps);
     snprintf(stack_str, sizeof(stack_str), "%lu KB", avg_stack_usage / 1024);
     snprintf(heap_str, sizeof(heap_str), "%lu KB", avg_heap_usage / 1024);
     snprintf(render_str, sizeof(render_str), "%lu ms", avg_render_time);
     snprintf(cpu_str, sizeof(cpu_str), "%lu %%", avg_cpu_usage);

     static_param_screen_init("SVG Test", fps_str, stack_str, heap_str, render_str, cpu_str);


     if(screen_svg) {
         lv_obj_del(screen_svg);
         screen_svg = NULL;
     }

     lv_timer_del(timer);
     svg_timer = NULL;
}

void create_svg_scr(void) {
    // Set screen background to white
    lv_obj_set_style_bg_color(screen_svg, lv_color_white(), 0);

    // Reset position indices
    for(int i = 0; i < 5; i++)
    	pos_idx[i] = 4 - i;

    // Get tire dimensions
    tire_w = 65;
    tire_h = 65;

    // Create ellipse image
    lv_obj_t *ellipse_data = lv_img_create(screen_svg);
    lv_img_set_src(ellipse_data, &ellipse);
    lv_obj_align(ellipse_data, LV_ALIGN_TOP_MID, 0, -50);

    // Create Car image at bottom center
    lv_obj_t *car_image = lv_img_create(screen_svg);
    lv_img_set_src(car_image, &car_body);
    lv_obj_set_pos(car_image, 183, 271);

    car_tire_image = lv_img_create(screen_svg);
    lv_img_set_src(car_tire_image, tire_images[2]);
    lv_obj_set_pos(car_tire_image, 219, 314);

    // Tire image descriptors
    static const lv_img_dsc_t *srcs[5] = {&tire4, &tire5, &tire1, &tire2, &tire3};

    // Create tire images and set initial positions
    for (int i = 0; i < 5; i++) {
        tires[i] = lv_img_create(screen_svg);
        lv_img_set_src(tires[i], srcs[i]);
        lv_coord_t px = positions[pos_idx[i]].x - tire_w / 2;
        lv_coord_t py = positions[pos_idx[i]].y - tire_h / 2;
        lv_obj_set_pos(tires[i], px, py);
    }

    // Create timer for animation every 0.5 seconds
    car_tier = lv_timer_create(shift_callback, 700, NULL);
}

static void anim_x_cb(void *var, int32_t v) {
    lv_obj_set_x((lv_obj_t *)var, (lv_coord_t)v);
}

static void anim_y_cb(void *var, int32_t v) {
    lv_obj_set_y((lv_obj_t *)var, (lv_coord_t)v);
}

static void shift_callback(lv_timer_t *timer) {
    for (int i = 0; i < 5; i++) {
        int old_idx = pos_idx[i];
        int new_idx = (old_idx + 1) % 5; // Increment for left to right movement
        pos_idx[i] = new_idx;

        lv_coord_t start_x = positions[old_idx].x - tire_w / 2;
        lv_coord_t end_x = positions[new_idx].x - tire_w / 2;
        lv_coord_t start_y = positions[old_idx].y - tire_h / 2;
        lv_coord_t end_y = positions[new_idx].y - tire_h / 2;

        // Animate x
        lv_anim_t a_x;
        lv_anim_init(&a_x);
        lv_anim_set_var(&a_x, tires[i]);
        lv_anim_set_values(&a_x, start_x, end_x);
        lv_anim_set_exec_cb(&a_x, anim_x_cb);
        lv_anim_set_path_cb(&a_x, lv_anim_path_ease_in_out);
        lv_anim_set_time(&a_x, 350);
        lv_anim_start(&a_x);

        // Animate y
        lv_anim_t a_y;
        lv_anim_init(&a_y);
        lv_anim_set_var(&a_y, tires[i]);
        lv_anim_set_values(&a_y, start_y, end_y);
        lv_anim_set_exec_cb(&a_y, anim_y_cb);
        lv_anim_set_path_cb(&a_y, lv_anim_path_ease_in_out);
        lv_anim_set_time(&a_y, 350);
        lv_anim_start(&a_y);
    }

    int center_idx = pos_idx[2];
    lv_img_set_src(car_tire_image, tire_images[center_idx]);
}

void button_svg_event_cb(lv_event_t * e)
{
	demo_running = 1;

    // Create new screen
    screen_svg = lv_obj_create(NULL);
    lv_scr_load(screen_svg);
    create_svg_scr();

    svg_timer = lv_timer_create(hide_svg_screen_cb, 10000, NULL);
}
