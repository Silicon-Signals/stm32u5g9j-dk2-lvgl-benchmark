/*
 * animation_main_scr.c
 *
 *  Created on: Sep 29, 2025
 *      Author: prutha
 */


#include "animation_main_scr.h"

// Private animation callbacks
static void anim_x_cb(void * var, int32_t v) {
    lv_obj_set_x((lv_obj_t *)var, v);
}

static void anim_y_cb(void * var, int32_t v) {
    lv_obj_set_y((lv_obj_t *)var, v);
}

// Animate a button outward from center
void start_button_animation(lv_obj_t *btn, int final_x, int final_y) {
    int start_x = center_x - lv_obj_get_width(btn)/2;
    int start_y = center_y - lv_obj_get_height(btn)/2;

    // Show before anim
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_HIDDEN);

    lv_anim_t a;

    // X animation
    lv_anim_init(&a);
    lv_anim_set_var(&a, btn);
    lv_anim_set_exec_cb(&a, anim_x_cb);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_values(&a, start_x, final_x);
    lv_anim_start(&a);

    // Y animation
    lv_anim_init(&a);
    lv_anim_set_var(&a, btn);
    lv_anim_set_exec_cb(&a, anim_y_cb);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_values(&a, start_y, final_y);
    lv_anim_start(&a);
}

