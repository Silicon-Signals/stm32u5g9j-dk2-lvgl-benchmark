/*
 * video_demo.c
 *
 *  Created on: Nov 3, 2025
 *      Author: prutha
 */
#include "video_demo.h"
#include "main.h"
#include "benchmark_results.h"

extern int video;


void video_button_event_cb(lv_event_t * e)
{
	demo_running = 1;
	video = 0;
}
