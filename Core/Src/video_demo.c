/*
 * video_demo.c
 *
 *  Created on: Nov 3, 2025
 *      Author: prutha
 */

#include <stdio.h>
#include "benchmark_results.h"
#include "video_demo.h"
#include "main.h"
#include "video_frames.h"
#include "parameter_display.h"

#define X(n) &Big_Buck_Bunny_mjpeg_##n,

const lv_image_dsc_t *video_frames[] = {
    X(000) X(001) X(002) X(003) X(004) X(005) X(006) X(007) X(008) X(009)
    X(010) X(011) X(012) X(013) X(014) X(015) X(016) X(017) X(018) X(019)
    X(020) X(021) X(022) X(023) X(024) X(025) X(026) X(027) X(028) X(029)
    X(030) X(031) X(032) X(033) X(034) X(035) X(036) X(037) X(038) X(039)
    X(040) X(041) X(042) X(043) X(044) X(045) X(046) X(047) X(048) X(049)
    X(050) X(051) X(052) X(053) X(054) X(055) X(056) X(057) X(058) X(059)
    X(060) X(061) X(062) X(063) X(064) X(065) X(066) X(067) X(068) X(069)
    X(070) X(071) X(072) X(073) X(074) X(075) X(076) X(077) X(078) X(079)
    X(080) X(081) X(082) X(083) X(084) X(085) X(086) X(087) X(088) X(089)
    X(090) X(091) X(092) X(093) X(094) X(095) X(096) X(097) X(098) X(099)
    #undef X
};
const uint32_t video_frame_count = sizeof(video_frames) / sizeof(video_frames[0]);

lv_obj_t *video_screen = NULL;
lv_obj_t *video_img = NULL;

static lv_timer_t *video_timer = NULL;
static lv_timer_t *video_close_timer = NULL;

static uint32_t current_frame = 0;

static void hide_video_screen_cb(lv_timer_t *timer)
{
    if (video_timer) lv_timer_del(video_timer);

    char fps_str[16], stack_str[16], heap_str[16], render_str[16], cpu_str[16];

    snprintf(fps_str, sizeof(fps_str), "%lu", avg_fps);
    snprintf(stack_str, sizeof(stack_str), "%lu KB", avg_stack_usage / 1024);
    snprintf(heap_str, sizeof(heap_str), "%lu KB", avg_heap_usage / 1024);
    snprintf(render_str, sizeof(render_str), "%lu ms", avg_render_time);
    snprintf(cpu_str, sizeof(cpu_str), "%lu %%", avg_cpu_usage);

    static_param_screen_init("Video Test", fps_str, stack_str, heap_str, render_str, cpu_str);

    if (video_screen) {
        lv_obj_del(video_screen);
        video_screen = NULL;
        video_img = NULL;
    }

    current_frame = 0;

    lv_timer_del(video_close_timer);
    video_close_timer = NULL;
    timer = NULL;
}

static void video_play_cb(lv_timer_t * timer)
{
    if (!video_img) return;

    lv_image_set_src(video_img, video_frames[current_frame]);

    current_frame++;
    if (current_frame >= video_frame_count) {
        current_frame = 0;
    }
}

void video_button_event_cb(lv_event_t * e)
{
    demo_running = 1;

    // Create screen
    video_screen = lv_obj_create(NULL);
    lv_scr_load(video_screen);

    // Create image object (800×480)
    video_img = lv_image_create(video_screen);
    lv_obj_set_size(video_img, 800, 480);
    lv_obj_center(video_img);

    // Start 10 FPS playback (100 ms)
    video_timer = lv_timer_create(video_play_cb, 100, NULL);

    video_close_timer = lv_timer_create(hide_video_screen_cb, 10000, NULL);
}
