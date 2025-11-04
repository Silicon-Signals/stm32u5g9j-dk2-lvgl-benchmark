/*
 * svg_screen.c
 *
 *  Created on: Oct 23, 2025
 *      Author: prutha
 */

#include "parameter_display.h"
#include "svg_screen.h"

LV_IMAGE_DECLARE(Tire1);
LV_IMAGE_DECLARE(Tire2);
LV_IMAGE_DECLARE(Tire3);
LV_IMAGE_DECLARE(Tire4);
LV_IMAGE_DECLARE(Tire5);
LV_IMAGE_DECLARE(tire_pair1);
LV_IMAGE_DECLARE(tire_pair2);
LV_IMAGE_DECLARE(tire_pair3);
LV_IMAGE_DECLARE(tire_pair4);
LV_IMAGE_DECLARE(tire_pair5);
LV_IMAGE_DECLARE(Ellipse);
LV_IMAGE_DECLARE(Car_Body);

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
		{680, 60},
		{550, 165},
		{400, 193},
		{250, 165},
		{120, 60}
};
static const lv_img_dsc_t *tire_images[5] = {&tire_pair1, &tire_pair2, &tire_pair3, &tire_pair4, &tire_pair5};
static int tire_w, tire_h;

static void hide_svg_screen_cb(lv_timer_t *timer) {
     if(car_tier) lv_timer_del(car_tier);
     static_param_screen_init("SVG test", "28", "12 KB", "78 KB", "0.5 ms", "15 %");

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

    // Get tire dimensions
    tire_w = Tire1.header.w;
    tire_h = Tire1.header.h;

    // Create ellipse image
    lv_obj_t *ellipse = lv_img_create(screen_svg);
    lv_img_set_src(ellipse, &Ellipse);
    lv_obj_align(ellipse, LV_ALIGN_TOP_MID, 0, 0);

    // Create Car image at bottom center
    lv_obj_t *car_image = lv_img_create(screen_svg);
    lv_img_set_src(car_image, &Car_Body);
    lv_obj_align(car_image, LV_ALIGN_BOTTOM_MID, 0, -50);

    car_tire_image = lv_img_create(screen_svg);
    lv_img_set_src(car_tire_image, tire_images[2]); // Initially set to the center tire (Tire3)
    lv_obj_align(car_tire_image, LV_ALIGN_BOTTOM_MID, 5, -38);

    // Tire image descriptors
    const lv_img_dsc_t *srcs[5] = {&Tire1, &Tire2, &Tire3, &Tire4, &Tire5};

    // Create tire images and set initial positions
    for (int i = 0; i < 5; i++) {
        tires[i] = lv_img_create(screen_svg);
        lv_img_set_src(tires[i], srcs[i]);
        lv_coord_t px = positions[pos_idx[i]].x - tire_w / 2;
        lv_coord_t py = positions[pos_idx[i]].y - tire_h / 2;
        lv_obj_set_pos(tires[i], px, py);
    }

    // Create timer for animation every 0.5 seconds
    car_tier = lv_timer_create(shift_callback, 500, NULL);
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
        lv_anim_set_time(&a_x, 250);
        lv_anim_start(&a_x);

        // Animate y
        lv_anim_t a_y;
        lv_anim_init(&a_y);
        lv_anim_set_var(&a_y, tires[i]);
        lv_anim_set_values(&a_y, start_y, end_y);
        lv_anim_set_exec_cb(&a_y, anim_y_cb);
        lv_anim_set_path_cb(&a_y, lv_anim_path_ease_in_out);
        lv_anim_set_time(&a_y, 250);
        lv_anim_start(&a_y);
    }

    int center_idx = pos_idx[2]; // Index of the tire at the center position
    lv_img_set_src(car_tire_image, tire_images[center_idx]);
}

void button_svg_event_cb(lv_event_t * e)
{
    // Create new screen
    screen_svg = lv_obj_create(NULL);
    lv_scr_load(screen_svg);
    create_svg_scr();

    svg_timer = lv_timer_create(hide_svg_screen_cb, 10000, NULL);
}
