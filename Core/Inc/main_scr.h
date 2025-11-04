/*
 * main_scr.h
 *
 *  Created on: Sep 29, 2025
 *      Author: prutha
 */

#ifndef INC_MAIN_SCR_H_
#define INC_MAIN_SCR_H_

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

/*********************
 *      DEFINES
 *********************/
#define DEG_TO_RAD(deg) ((deg) * 3.14159265 / 180.0)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * main_screen_start(void);
void main_scr_reset_menu(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif



#endif /* INC_MAIN_SCR_H_ */
