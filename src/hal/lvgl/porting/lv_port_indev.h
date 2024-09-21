
/**
 * @file lv_port_indev_templ.h
 *
 */

/*Copy this file as "lv_port_indev.h" and set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_INDEV_TEMPL_H
#define LV_PORT_INDEV_TEMPL_H

// #ifdef __cplusplus
// extern "C" {
// #endif

/*********************
 *      INCLUDES
 *********************/
// #include "lvgl/lvgl.h"
#include <lvgl.h>
// #include "../../encoder/simple_encoder.h"
// #include <simple_encoder_pcnt.h>
#include "../../utils/ESP32Encoder/src/ESP32Encoder.h"
#include "../../utils/Button/Button.h"
#include "../../tp/hal_tp.hpp"

/*********************
 *      DEFINES
 *********************/
#define ENCODER_REVERSE

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
// void lv_port_indev_init(SIMPLE_ENCODER::ENCODER* encoder);
void lv_port_indev_init(ESP32Encoder* encoder, FT3267::TP_FT3267* tp);

/**********************
 *      MACROS
 **********************/

// #ifdef __cplusplus
// } /*extern "C"*/
// #endif

#endif /*LV_PORT_INDEV_TEMPL_H*/

#endif /*Disable/Enable content*/
