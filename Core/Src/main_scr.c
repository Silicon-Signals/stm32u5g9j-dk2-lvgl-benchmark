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
#include "cluster_demo.h"
/*********************
 *      DEFINES
 *********************/
LV_IMAGE_DECLARE(toggle_left);
LV_IMAGE_DECLARE(toggle_right);
#define MENU_BTN_SIZE   60   // Diameter of small menu buttons
#define MAIN_BTN_SIZE   190  // Diameter of central button
/**********************
 *      TYPEDEFS
 **********************/

struct _lv_hit_test_info_t {
    const lv_point_t * point;   /**< A point relative to screen to check if it can click the object or not*/
    bool res;                   /**< true: `point` can click the object; false: it cannot*/
};


demo_mode_t current_mode = MODE_MANUAL;

typedef enum {
    AUTO_VIDEO = 0,
    AUTO_2D,
    AUTO_STATIC,
    AUTO_SVG,
    AUTO_TEXT,
    AUTO_CLUSTER,
} auto_demo_state_t;

static auto_demo_state_t auto_state = 0;
static lv_timer_t * auto_timer;
static lv_obj_t * lbl_mode;

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/
static bool menu_open = false;
int center_x = 400;
int center_y = 240;
int radius = 170;
int angle_btn_close = 90;
int angle_btn_video = 141;
int angle_btn_svg = 294;
int angle_btn_2d = 192;
int angle_btn_static = 243;
int angle_btn_text_scroll = 345;
int angle_btn_cluster = 39;

lv_obj_t *new_scr;
lv_obj_t *main_screen;
lv_obj_t *btn_static;
lv_obj_t *btn_2d;
lv_obj_t *btn_svg;
lv_obj_t *btn_video;
lv_obj_t *btn_text_scroll;
lv_obj_t *btn_close;
lv_obj_t *btn_cluster;
lv_obj_t *main_btn;
lv_obj_t *label_center;
lv_obj_t *mode_sw;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
static void start_button_event_cb(lv_event_t * e);
void menu_button_event_cb(lv_event_t * e) {
    if(menu_open)
        return;
    lv_obj_add_flag(label_center, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(mode_sw, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(lbl_mode, LV_OBJ_FLAG_HIDDEN);

    start_button_animation(btn_static,
        center_x + radius * cos(DEG_TO_RAD(angle_btn_static)) - MENU_BTN_SIZE/2,
        center_y + radius * sin(DEG_TO_RAD(angle_btn_static)) - MENU_BTN_SIZE/2);

    start_button_animation(btn_2d,
        center_x + radius * cos(DEG_TO_RAD(angle_btn_2d)) - MENU_BTN_SIZE/2,
        center_y + radius * sin(DEG_TO_RAD(angle_btn_2d)) - MENU_BTN_SIZE/2);

    start_button_animation(btn_svg,
        center_x + radius * cos(DEG_TO_RAD(angle_btn_svg)) - MENU_BTN_SIZE/2,
        center_y + radius * sin(DEG_TO_RAD(angle_btn_svg)) - MENU_BTN_SIZE/2);

    start_button_animation(btn_video,
        center_x + radius * cos(DEG_TO_RAD(angle_btn_video)) - MENU_BTN_SIZE/2,
        center_y + radius * sin(DEG_TO_RAD(angle_btn_video)) - MENU_BTN_SIZE/2);

    start_button_animation(btn_close,
        center_x + radius * cos(DEG_TO_RAD(angle_btn_close)) - MENU_BTN_SIZE/2,
        center_y + radius * sin(DEG_TO_RAD(angle_btn_close)) - MENU_BTN_SIZE/2);
    start_button_animation(btn_text_scroll,
            center_x + radius * cos(DEG_TO_RAD(angle_btn_text_scroll)) - MENU_BTN_SIZE/2,
            center_y + radius * sin(DEG_TO_RAD(angle_btn_text_scroll)) - MENU_BTN_SIZE/2);
    start_button_animation(btn_cluster,
                center_x + radius * cos(DEG_TO_RAD(angle_btn_cluster)) - MENU_BTN_SIZE/2,
                center_y + radius * sin(DEG_TO_RAD(angle_btn_cluster)) - MENU_BTN_SIZE/2);

    menu_open = true;  // set flag
}

void main_scr_reset_menu(void)
{
    lv_obj_remove_flag(btn_static,      LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(btn_2d,          LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(btn_svg,         LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(btn_video,       LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(btn_close,       LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(btn_text_scroll, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(btn_cluster,     LV_OBJ_FLAG_HIDDEN);

    menu_open = true;
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
    lv_anim_set_time(&a, 800);
    lv_anim_set_values(&a, lv_obj_get_x(btn), center_x - lv_obj_get_width(btn)/2);
    lv_anim_set_ready_cb(&a, close_anim_ready_cb);
    lv_anim_start(&a);

    lv_anim_t b;
    lv_anim_init(&b);
    lv_anim_set_var(&b, btn);
    lv_anim_set_exec_cb(&b, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_time(&b, 800);
    lv_anim_set_values(&b, lv_obj_get_y(btn), center_y - lv_obj_get_height(btn)/2);
    lv_anim_start(&b);
}

static void show_center_label_timer_cb(lv_timer_t * timer)
{
    lv_obj_clear_flag(label_center, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(mode_sw, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(lbl_mode, LV_OBJ_FLAG_HIDDEN);
    lv_timer_del(timer);  // self-delete
}

void close_button_event_cb(lv_event_t * e)
{
    if(!menu_open) return;

    // Animate all buttons back to center, then hide
    animate_button_back(btn_static, center_x, center_y);
    animate_button_back(btn_2d, center_x, center_y);
    animate_button_back(btn_svg, center_x, center_y);
    animate_button_back(btn_video, center_x, center_y);
    animate_button_back(btn_close, center_x, center_y);
    animate_button_back(btn_text_scroll, center_x, center_y);
    animate_button_back(btn_cluster, center_x, center_y);

    lv_timer_create(show_center_label_timer_cb, 800, NULL);

    menu_open = false;
}

static void circular_hit_test_cb(lv_event_t * e)
{
    lv_hit_test_info_t * info = lv_event_get_hit_test_info(e);
    lv_obj_t * obj = lv_event_get_target(e);

    // Get the click point relative to the object's top-left corner
    lv_point_t rel_point;
    rel_point.x = info->point->x - lv_obj_get_x(obj);
    rel_point.y = info->point->y - lv_obj_get_y(obj);

    // Object size
    lv_coord_t w = lv_obj_get_width(obj);
    lv_coord_t h = lv_obj_get_height(obj);

    // Center of the object
    lv_coord_t cx = w / 2;
    lv_coord_t cy = h / 2;

    // Approximate radius (use the smaller dimension / 2)
    lv_coord_t r = (w < h ? w : h) / 2;

    // Relative coordinates from center
    lv_coord_t dx = rel_point.x - cx;
    lv_coord_t dy = rel_point.y - cy;

    // If distance from center > radius, not hittable
    if (dx * dx + dy * dy > r * r) {
        info->res = false; // Outside circle
    } else {
        info->res = true;  // Inside circle
    }
}

static void mode_switch_event_cb(lv_event_t * e)
{
    lv_obj_t * img = lv_event_get_target(e);

    if(current_mode == MODE_MANUAL) {
        /* Switch to AUTO */
        lv_obj_add_flag(btn_static, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(btn_2d, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(btn_video, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(btn_svg, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(btn_close, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(btn_text_scroll, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(btn_cluster, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(label_center, LV_OBJ_FLAG_HIDDEN);

        current_mode = MODE_AUTO;
        lv_image_set_src(img, &toggle_right);
        lv_label_set_text(lbl_mode, "Auto");
    } else {
        /* Switch to MANUAL */
        menu_open = false;

        current_mode = MODE_MANUAL;
        lv_image_set_src(img, &toggle_left);
        lv_label_set_text(lbl_mode, "Manual");
    }
}

static void auto_demo_timer_cb(lv_timer_t * timer)
{
    switch(auto_state)
    {
        case AUTO_VIDEO:
        	video_button_event_cb(NULL);
            auto_state = AUTO_2D;
            lv_timer_set_period(timer, 13000);
            break;

        case AUTO_2D:
            button_2d_event_cb(NULL);
            auto_state = AUTO_STATIC;
            lv_timer_set_period(timer, 13000);
            break;

        case AUTO_STATIC:
            static_button_event_cb(NULL);
            auto_state = AUTO_SVG;
            lv_timer_set_period(timer, 13000);
            break;

        case AUTO_SVG:
            button_svg_event_cb(NULL);
            auto_state = AUTO_TEXT;
            lv_timer_set_period(timer, 13000);
            break;

        case AUTO_TEXT:
            text_scroll_button_event_cb(NULL);
            auto_state = AUTO_CLUSTER;
            lv_timer_set_period(timer, 13000);
            break;

        case AUTO_CLUSTER:
        	cluster_button_event_cb(NULL);
            auto_state = AUTO_VIDEO;
            lv_timer_set_period(timer, 23000);
            break;
        default:
            auto_state = AUTO_VIDEO;
            lv_timer_set_period(timer, 13000);
            break;
    }
}

static void start_auto_demo(void)
{
    if(auto_timer) {
        lv_timer_del(auto_timer);
        auto_timer = NULL;
    }

    auto_state = AUTO_VIDEO;
    auto_timer = lv_timer_create(auto_demo_timer_cb, 10, NULL);
}

static void start_button_event_cb(lv_event_t * e)
{
    auto_state = AUTO_VIDEO;

    if(current_mode == MODE_AUTO) {
        start_auto_demo();
    } else {
        menu_button_event_cb(e);
    }
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

    mode_sw = lv_image_create(bg_img);
    lv_image_set_src(mode_sw, &toggle_left);
    lv_obj_set_pos(mode_sw, 0, 438);   // left-bottom
    lv_obj_add_flag(mode_sw, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(mode_sw, mode_switch_event_cb, LV_EVENT_CLICKED, NULL);

    /* Dynamic mode label (LEFT of switch) */
    lbl_mode = lv_label_create(bg_img);
    lv_label_set_text(lbl_mode, "Manual");   // default when switch OFF
    lv_obj_set_style_text_font(lbl_mode, &lv_font_calibri_bold_18, 0);
    lv_obj_set_style_text_color(lbl_mode, lv_color_white(), 0);
    lv_obj_set_pos(lbl_mode, 82, 447);

    main_btn = lv_button_create(bg_img);
    lv_obj_remove_style_all(main_btn);
    lv_obj_set_x(main_btn, center_x - MAIN_BTN_SIZE/2);
    lv_obj_set_y(main_btn, center_y - 188/2);
    lv_obj_set_width(main_btn, MAIN_BTN_SIZE);
    lv_obj_set_height(main_btn, 188);
    lv_obj_set_style_radius(main_btn, 100, 0);
    lv_obj_add_flag(main_btn, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_add_event_cb(main_btn, circular_hit_test_cb, LV_EVENT_HIT_TEST, NULL);

    lv_obj_clear_flag(main_btn, LV_OBJ_FLAG_PRESS_LOCK);
    lv_obj_clear_flag(main_btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(main_btn, LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_clear_flag(main_btn, LV_OBJ_FLAG_FLOATING);
    lv_obj_add_flag(main_btn, LV_OBJ_FLAG_IGNORE_LAYOUT);

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
    lv_obj_remove_style_all(btn_static);
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
    lv_obj_remove_style_all(btn_2d);
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
    lv_label_set_text(label_2d, "2D");
    lv_obj_set_style_text_font(label_2d, &lv_font_calibri_bold_14, 0);
    lv_obj_set_style_text_color(label_2d, lv_color_white(), 0);
    lv_obj_set_width(label_2d, MENU_BTN_SIZE);
    lv_label_set_long_mode(label_2d, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(label_2d, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_align(label_2d, LV_ALIGN_CENTER);

    btn_svg = lv_button_create(bg_img);
    lv_obj_remove_style_all(btn_svg);
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
    lv_label_set_text(label_svg, "SVG");
    lv_obj_set_style_text_font(label_svg, &lv_font_calibri_bold_14, 0);
    lv_obj_set_style_text_color(label_svg, lv_color_white(), 0);
    lv_obj_set_width(label_svg, MENU_BTN_SIZE);
    lv_label_set_long_mode(label_svg, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(label_svg, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_align(label_svg, LV_ALIGN_CENTER);

    btn_video = lv_button_create(bg_img);
    lv_obj_remove_style_all(btn_video);
    lv_obj_set_x(btn_video, center_x + radius * cos(DEG_TO_RAD(angle_btn_video)) - MENU_BTN_SIZE/2);
    lv_obj_set_y(btn_video, center_y + radius * sin(DEG_TO_RAD(angle_btn_video)) - MENU_BTN_SIZE/2);
    lv_obj_set_width(btn_video, MENU_BTN_SIZE);
    lv_obj_set_height(btn_video, MENU_BTN_SIZE);
    lv_obj_set_style_radius(btn_video, MENU_BTN_SIZE/2, 0);
    lv_obj_set_flag(btn_video, LV_OBJ_FLAG_HIDDEN, false);

    lv_obj_t * img_video_btn = lv_image_create(btn_video);
    lv_image_set_src(img_video_btn, &ui_button);
    lv_obj_set_align(img_video_btn, LV_ALIGN_CENTER);

    // For btn_video label
    lv_obj_t * label_video = lv_label_create(btn_video);
    lv_label_set_text(label_video, "Video\nTest");
    lv_obj_set_style_text_font(label_video, &lv_font_calibri_bold_14, 0);
    lv_obj_set_style_text_color(label_video, lv_color_white(), 0);
    lv_obj_set_width(label_video, MENU_BTN_SIZE);
    lv_label_set_long_mode(label_video, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(label_video, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_align(label_video, LV_ALIGN_CENTER);

    btn_text_scroll = lv_button_create(bg_img);
    lv_obj_remove_style_all(btn_text_scroll);
    lv_obj_set_x(btn_text_scroll, center_x + radius * cos(DEG_TO_RAD(angle_btn_text_scroll)) - MENU_BTN_SIZE/2);
    lv_obj_set_y(btn_text_scroll, center_y + radius * sin(DEG_TO_RAD(angle_btn_text_scroll)) - MENU_BTN_SIZE/2);
    lv_obj_set_width(btn_text_scroll, MENU_BTN_SIZE);
    lv_obj_set_height(btn_text_scroll, MENU_BTN_SIZE);
    lv_obj_set_style_radius(btn_text_scroll, MENU_BTN_SIZE/2, 0);
    lv_obj_set_flag(btn_text_scroll, LV_OBJ_FLAG_HIDDEN, false);

    lv_obj_t * img_text_btn = lv_image_create(btn_text_scroll);
    lv_image_set_src(img_text_btn, &ui_button);
    lv_obj_set_align(img_text_btn, LV_ALIGN_CENTER);

    // For btn_text_scroll
    lv_obj_t * label_text_scroll = lv_label_create(btn_text_scroll);
    lv_label_set_text(label_text_scroll, "Text\nScroll");
    lv_obj_set_style_text_font(label_text_scroll, &lv_font_calibri_bold_14, 0);
    lv_obj_set_style_text_color(label_text_scroll, lv_color_white(), 0);
    lv_obj_set_width(label_text_scroll, MENU_BTN_SIZE);
    lv_label_set_long_mode(label_text_scroll, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(label_text_scroll, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_align(label_text_scroll, LV_ALIGN_CENTER);

    btn_cluster = lv_button_create(bg_img);
    lv_obj_remove_style_all(btn_cluster);
    lv_obj_set_x(btn_cluster, center_x + radius * cos(DEG_TO_RAD(angle_btn_cluster)) - MENU_BTN_SIZE/2);
    lv_obj_set_y(btn_cluster, center_y + radius * sin(DEG_TO_RAD(angle_btn_cluster)) - MENU_BTN_SIZE/2);
    lv_obj_set_width(btn_cluster, MENU_BTN_SIZE);
    lv_obj_set_height(btn_cluster, MENU_BTN_SIZE);
    lv_obj_set_style_radius(btn_cluster, MENU_BTN_SIZE/2, 0);
    lv_obj_set_flag(btn_cluster, LV_OBJ_FLAG_HIDDEN, false);

    lv_obj_t * img_cluster_btn = lv_image_create(btn_cluster);
    lv_image_set_src(img_cluster_btn, &ui_button);
    lv_obj_set_align(img_cluster_btn, LV_ALIGN_CENTER);

    // For btn_cluster label
    lv_obj_t * label_cluster = lv_label_create(btn_cluster);
    lv_label_set_text(label_cluster, "Cluster");
    lv_obj_set_style_text_font(label_cluster, &lv_font_calibri_bold_14, 0);
    lv_obj_set_style_text_color(label_cluster, lv_color_white(), 0);
    lv_obj_set_width(label_cluster, MENU_BTN_SIZE);
    lv_label_set_long_mode(label_cluster, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(label_cluster, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_align(label_cluster, LV_ALIGN_CENTER);

    btn_close = lv_button_create(bg_img);
    lv_obj_remove_style_all(btn_close);
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
    lv_obj_add_flag(btn_video, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_svg, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_close, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_text_scroll, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_cluster, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_event_cb(main_btn, start_button_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_close, close_button_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_static, static_button_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_2d, button_2d_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_svg, button_svg_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_text_scroll, text_scroll_button_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_video, video_button_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(btn_cluster, cluster_button_event_cb, LV_EVENT_CLICKED, NULL);

    LV_TRACE_OBJ_CREATE("finished");

    return main_screen;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
