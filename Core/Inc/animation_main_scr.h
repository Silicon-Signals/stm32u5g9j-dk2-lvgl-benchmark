/*
 * animation_main_scr.h
 *
 *  Created on: Sep 29, 2025
 *      Author: prutha
 */

#ifndef INC_ANIMATION_MAIN_SCR_H_
#define INC_ANIMATION_MAIN_SCR_H_

#include "lvgl/lvgl.h"

// Center of circle (extern so you can set in main file)
extern int center_x;
extern int center_y;

// Function prototypes
void start_button_animation(lv_obj_t *btn, int final_x, int final_y);



#endif /* INC_ANIMATION_MAIN_SCR_H_ */
