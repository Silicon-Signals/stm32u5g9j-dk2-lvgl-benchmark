/*
 * main_scr.c
 *
 *  Created on: Sep 29, 2025
 *      Author: prutha
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include "math.h"
#include "main_scr.h"
#include "animation_main_scr.h"
#include "static_screen.h"
#include "2d_screen.h"
#include "svg_screen.h"
#include "text_scroll.h"
#include "video_demo.h"
/*********************
 *      DEFINES
 *********************/
#define MENU_BTN_SIZE   60   // Diameter of small menu buttons
#define MAIN_BTN_SIZE   190  // Diameter of central button
/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/
static bool menu_open = false;
int center_x = 400;
int center_y = 240;
int radius = 160;
int angle_btn_close = 90;
int angle_btn_alpha = 150;
int angle_btn_svg = 330;
int angle_btn_2d = 210;
int angle_btn_static = 270;
int angle_btn_text_scroll = 30;


lv_obj_t *new_scr;
lv_obj_t *main_screen;
lv_obj_t *btn_static;
lv_obj_t *btn_2d;
lv_obj_t *btn_svg;
lv_obj_t *btn_alpha;
lv_obj_t *btn_text_scroll;
lv_obj_t *btn_close;
lv_obj_t *main_btn;
lv_obj_t * label_center;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void menu_button_event_cb(lv_event_t * e) {
    if(menu_open)
        return;
    lv_obj_add_flag(label_center, LV_OBJ_FLAG_HIDDEN);
    start_button_animation(btn_static,
        center_x + radius * cos(DEG_TO_RAD(angle_btn_static)) - MENU_BTN_SIZE/2,
        center_y + radius * sin(DEG_TO_RAD(angle_btn_static)) - MENU_BTN_SIZE/2);

    start_button_animation(btn_2d,
        center_x + radius * cos(DEG_TO_RAD(angle_btn_2d)) - MENU_BTN_SIZE/2,
        center_y + radius * sin(DEG_TO_RAD(angle_btn_2d)) - MENU_BTN_SIZE/2);

    start_button_animation(btn_svg,
        center_x + radius * cos(DEG_TO_RAD(angle_btn_svg)) - MENU_BTN_SIZE/2,
        center_y + radius * sin(DEG_TO_RAD(angle_btn_svg)) - MENU_BTN_SIZE/2);

    start_button_animation(btn_alpha,
        center_x + radius * cos(DEG_TO_RAD(angle_btn_alpha)) - MENU_BTN_SIZE/2,
        center_y + radius * sin(DEG_TO_RAD(angle_btn_alpha)) - MENU_BTN_SIZE/2);

    start_button_animation(btn_close,
        center_x + radius * cos(DEG_TO_RAD(angle_btn_close)) - MENU_BTN_SIZE/2,
        center_y + radius * sin(DEG_TO_RAD(angle_btn_close)) - MENU_BTN_SIZE/2);
    start_button_animation(btn_text_scroll,
            center_x + radius * cos(DEG_TO_RAD(angle_btn_text_scroll)) - MENU_BTN_SIZE/2,
            center_y + radius * sin(DEG_TO_RAD(angle_btn_text_scroll)) - MENU_BTN_SIZE/2);

    menu_open = true;  // set flag
}

void main_scr_reset_menu(void)
{
    /* Hide the 6 menu buttons */
    lv_obj_add_flag(btn_static,      LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_2d,          LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_svg,         LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_alpha,       LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_close,       LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_text_scroll, LV_OBJ_FLAG_HIDDEN);

    /* Show the centre label again (it may have been hidden when the menu opened) */
    lv_obj_clear_flag(label_center, LV_OBJ_FLAG_HIDDEN);

    /* Make sure the menu is considered closed */
    menu_open = false;
}

// Callback for when the close animation finishes
static void close_anim_ready_cb(lv_anim_t * a)
{
    lv_obj_t * btn = (lv_obj_t *)a->var;
    lv_obj_add_flag(btn, LV_OBJ_FLAG_HIDDEN);
}

static void animate_button_back(lv_obj_t * btn, int center_x, int center_y)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, btn);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_values(&a, lv_obj_get_x(btn), center_x - lv_obj_get_width(btn)/2);
    lv_anim_set_ready_cb(&a, close_anim_ready_cb);
    lv_anim_start(&a);

    lv_anim_t b;
    lv_anim_init(&b);
    lv_anim_set_var(&b, btn);
    lv_anim_set_exec_cb(&b, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_time(&b, 1000);
    lv_anim_set_values(&b, lv_obj_get_y(btn), center_y - lv_obj_get_height(btn)/2);
    lv_anim_start(&b);
}

void close_button_event_cb(lv_event_t * e)
{
    if(!menu_open) return;

    lv_obj_remove_flag(label_center, LV_OBJ_FLAG_HIDDEN);

    // Animate all buttons back to center, then hide
    animate_button_back(btn_static, center_x, center_y);
    animate_button_back(btn_2d, center_x, center_y);
    animate_button_back(btn_svg, center_x, center_y);
    animate_button_back(btn_alpha, center_x, center_y);
    animate_button_back(btn_close, center_x, center_y);
    animate_button_back(btn_text_scroll, center_x, center_y);

    menu_open = false; // reset flag
}

lv_obj_t * main_screen_start(void)
{
    LV_TRACE_OBJ_CREATE("begin");
    LV_IMAGE_DECLARE(ui_button_center);
    LV_IMAGE_DECLARE(ui_button);
    LV_IMAGE_DECLARE(ui_bg);
    LV_IMAGE_DECLARE(close_btn);

    static bool style_inited = false;

    if (!style_inited) {

        style_inited = true;
    }

    main_screen = lv_obj_create(NULL);
    lv_obj_t * bg_img = lv_image_create(main_screen);
    lv_obj_set_style_bg_image_tiled(bg_img, true, 0);
    lv_image_set_src(bg_img, &ui_bg);
    lv_obj_set_width(bg_img, 800);
    lv_obj_set_height(bg_img, 480);
    lv_obj_set_x(bg_img, 0);
    lv_obj_set_y(bg_img, 0);

    main_btn = lv_button_create(bg_img);
    lv_obj_set_x(main_btn, center_x - MAIN_BTN_SIZE/2);
    lv_obj_set_y(main_btn, center_y - 188/2);
    lv_obj_set_width(main_btn, MAIN_BTN_SIZE);
    lv_obj_set_height(main_btn, 188);
    lv_obj_set_style_radius(main_btn, 100, 0);

    lv_obj_clear_flag(main_btn, LV_OBJ_FLAG_PRESS_LOCK);
    lv_obj_clear_flag(main_btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(main_btn, LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_clear_flag(main_btn, LV_OBJ_FLAG_FLOATING);

    lv_obj_t * img_main_btn = lv_image_create(main_btn);
    lv_image_set_src(img_main_btn, &ui_button_center);
    lv_obj_set_align(img_main_btn, LV_ALIGN_CENTER);

    // For main_btn label
    label_center = lv_label_create(main_btn);
    lv_label_set_text(label_center, "START");
    lv_obj_set_style_text_font(label_center, &lv_font_calibri_bold_44, 0);
    lv_obj_set_style_text_color(label_center, lv_color_white(), 0);
    lv_obj_set_align(label_center, LV_ALIGN_CENTER);

    btn_static = lv_button_create(bg_img);
    lv_obj_set_x(btn_static, center_x + radius * cos(DEG_TO_RAD(angle_btn_static)) - MENU_BTN_SIZE/2);
    lv_obj_set_y(btn_static, center_y + radius * sin(DEG_TO_RAD(angle_btn_static)) - MENU_BTN_SIZE/2);
    lv_obj_set_width(btn_static, MENU_BTN_SIZE);
    lv_obj_set_height(btn_static, MENU_BTN_SIZE);
    lv_obj_set_style_radius(btn_static, MENU_BTN_SIZE/2, 0);
    lv_obj_set_flag(btn_static, LV_OBJ_FLAG_HIDDEN, false);

    lv_obj_t * img_static_btn = lv_image_create(btn_static);
    lv_image_set_src(img_static_btn, &ui_button);
    lv_obj_set_align(img_static_btn, LV_ALIGN_CENTER);

    // For btn_static label
    lv_obj_t * label_static = lv_label_create(btn_static);
    lv_label_set_text(label_static, "Static");
    lv_obj_set_style_text_font(label_static, &lv_font_calibri_bold_14, 0);
    lv_obj_set_style_text_color(label_static, lv_color_white(), 0);
    lv_obj_set_align(label_static, LV_ALIGN_CENTER);

    btn_2d = lv_button_create(bg_img);
    lv_obj_set_x(btn_2d, center_x + radius * cos(DEG_TO_RAD(angle_btn_2d)) - MENU_BTN_SIZE/2);
    lv_obj_set_y(btn_2d, center_y + radius * sin(DEG_TO_RAD(angle_btn_2d)) - MENU_BTN_SIZE/2);
    lv_obj_set_width(btn_2d, MENU_BTN_SIZE);
    lv_obj_set_height(btn_2d, MENU_BTN_SIZE);
    lv_obj_set_style_radius(btn_2d, MENU_BTN_SIZE/2, 0);
    lv_obj_set_flag(btn_2d, LV_OBJ_FLAG_HIDDEN, false);

    lv_obj_t * img_2d_btn = lv_image_create(btn_2d);
    lv_image_set_src(img_2d_btn, &ui_button);
    lv_obj_set_align(img_2d_btn, LV_ALIGN_CENTER);

    // For btn_2d label
    lv_obj_t * label_2d = lv_label_create(btn_2d);
    lv_label_set_text(label_2d, "2D\nTest");
    lv_obj_set_style_text_font(label_2d, &lv_font_calibri_bold_14, 0);
    lv_obj_set_style_text_color(label_2d, lv_color_white(), 0);
    lv_obj_set_width(label_2d, MENU_BTN_SIZE);
    lv_label_set_long_mode(label_2d, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(label_2d, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_align(label_2d, LV_ALIGN_CENTER);


    btn_svg = lv_button_create(bg_img);
    lv_obj_set_x(btn_svg, center_x + radius * cos(DEG_TO_RAD(angle_btn_svg)) - MENU_BTN_SIZE/2);
    lv_obj_set_y(btn_svg, center_y + radius * sin(DEG_TO_RAD(angle_btn_svg)) - MENU_BTN_SIZE/2);
    lv_obj_set_width(btn_svg, MENU_BTN_SIZE);
    lv_obj_set_height(btn_svg, MENU_BTN_SIZE);
    lv_obj_set_style_radius(btn_svg, MENU_BTN_SIZE/2, 0);
    lv_obj_set_flag(btn_svg, LV_OBJ_FLAG_HIDDEN, false);

    lv_obj_t * img_svg_btn = lv_image_create(btn_svg);
    lv_image_set_src(img_svg_btn, &ui_button);
    lv_obj_set_align(img_svg_btn, LV_ALIGN_CENTER);

    // For btn_svg label
    lv_obj_t * label_svg = lv_label_create(btn_svg);
    lv_label_set_text(label_svg, "SVG\nTest");
    lv_obj_set_style_text_font(label_svg, &lv_font_calibri_bold_14, 0);
    lv_obj_set_style_text_color(label_svg, lv_color_white(), 0);
    lv_obj_set_width(label_svg, MENU_BTN_SIZE);
    lv_label_set_long_mode(label_svg, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(label_svg, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_align(label_svg, LV_ALIGN_CENTER);

    btn_alpha = lv_button_create(bg_img);
    lv_obj_set_x(btn_alpha, center_x + radius * cos(DEG_TO_RAD(angle_btn_alpha)) - MENU_BTN_SIZE/2);
    lv_obj_set_y(btn_alpha, center_y + radius * sin(DEG_TO_RAD(angle_btn_alpha)) - MENU_BTN_SIZE/2);
    lv_obj_set_width(btn_alpha, MENU_BTN_SIZE);
    lv_obj_set_height(btn_alpha, MENU_BTN_SIZE);
    lv_obj_set_style_radius(btn_alpha, MENU_BTN_SIZE/2, 0);
    lv_obj_set_flag(btn_alpha, LV_OBJ_FLAG_HIDDEN, false);

    lv_obj_t * img_alpha_btn = lv_image_create(btn_alpha);
    lv_image_set_src(img_alpha_btn, &ui_button);
    lv_obj_set_align(img_alpha_btn, LV_ALIGN_CENTER);

    // For btn_alpha label
    lv_obj_t * label_alpha = lv_label_create(btn_alpha);
    lv_label_set_text(label_alpha, "Video\nTest");
    lv_obj_set_style_text_font(label_alpha, &lv_font_calibri_bold_14, 0);
    lv_obj_set_style_text_color(label_alpha, lv_color_white(), 0);
    lv_obj_set_width(label_alpha, MENU_BTN_SIZE);
    lv_label_set_long_mode(label_alpha, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(label_alpha, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_align(label_alpha, LV_ALIGN_CENTER);

    btn_text_scroll = lv_button_create(bg_img);
    lv_obj_set_x(btn_text_scroll, center_x + radius * cos(DEG_TO_RAD(angle_btn_text_scroll)) - MENU_BTN_SIZE/2);
    lv_obj_set_y(btn_text_scroll, center_y + radius * sin(DEG_TO_RAD(angle_btn_text_scroll)) - MENU_BTN_SIZE/2);
    lv_obj_set_width(btn_text_scroll, MENU_BTN_SIZE);
    lv_obj_set_height(btn_text_scroll, MENU_BTN_SIZE);
    lv_obj_set_style_radius(btn_text_scroll, MENU_BTN_SIZE/2, 0);
    lv_obj_set_flag(btn_text_scroll, LV_OBJ_FLAG_HIDDEN, false);

    lv_obj_t * img_text_btn = lv_image_create(btn_text_scroll);
    lv_image_set_src(img_text_btn, &ui_button);
    lv_obj_set_align(img_text_btn, LV_ALIGN_CENTER);

    // For btn_static label
    lv_obj_t * label_text_scroll = lv_label_create(btn_text_scroll);
    lv_label_set_text(label_text_scroll, "Text\nScroll");
    lv_obj_set_style_text_font(label_text_scroll, &lv_font_calibri_bold_14, 0);
    lv_obj_set_style_text_color(label_text_scroll, lv_color_white(), 0);
    lv_obj_set_width(label_text_scroll, MENU_BTN_SIZE);
    lv_label_set_long_mode(label_text_scroll, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(label_text_scroll, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_align(label_text_scroll, LV_ALIGN_CENTER);

    btn_close = lv_button_create(bg_img);
    lv_obj_set_x(btn_close, center_x + radius * cos(DEG_TO_RAD(angle_btn_close)) - MENU_BTN_SIZE/2);
    lv_obj_set_y(btn_close, center_y + radius * sin(DEG_TO_RAD(angle_btn_close)) - MENU_BTN_SIZE/2);
    lv_obj_set_width(btn_close, MENU_BTN_SIZE);
    lv_obj_set_height(btn_close, MENU_BTN_SIZE);
    lv_obj_set_style_radius(btn_close, MENU_BTN_SIZE/2, 0);
    lv_obj_set_flag(btn_close, LV_OBJ_FLAG_HIDDEN, false);

    // Background image for button
    lv_obj_t * img_close_bg = lv_image_create(btn_close);
    lv_image_set_src(img_close_bg, &ui_button);
    lv_obj_set_align(img_close_bg, LV_ALIGN_CENTER);

    lv_obj_t * img_close_icon = lv_image_create(img_close_bg);
    lv_image_set_src(img_close_icon, &close_btn);
    lv_obj_set_align(img_close_icon, LV_ALIGN_CENTER);

    lv_obj_add_flag(btn_static, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_2d, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_alpha, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_svg, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_close, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_text_scroll, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_event_cb(main_btn, menu_button_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_close, close_button_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_static, static_button_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_2d, button_2d_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_svg, button_svg_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_text_scroll, text_scroll_button_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_alpha, video_button_event_cb, LV_EVENT_CLICKED, NULL);

    LV_TRACE_OBJ_CREATE("finished");

    return main_screen;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
