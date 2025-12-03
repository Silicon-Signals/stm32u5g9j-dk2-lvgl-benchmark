/*
 * my_perf_monitor.h
 *
 *  Created on: Nov 20, 2025
 *      Author: prutha
 */

#ifndef INC_PERF_MONITOR_H_
#define INC_PERF_MONITOR_H_

#include "lvgl/lvgl.h"

void perf_monitor_create(void);
void perf_monitor_update(lv_timer_t *t);
void perf_monitor_start(void);

#endif /* INC_PERF_MONITOR_H_ */
