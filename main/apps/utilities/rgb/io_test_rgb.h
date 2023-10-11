/**
 * @file io_test_rgb.h
 * @author Forairaaaaa
 * @brief https://github.com/espressif/idf-extra-components/blob/master/led_strip/examples/led_strip_rmt_ws2812/main/led_strip_rmt_ws2812_main.c
 * @version 0.1
 * @date 2023-08-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <led_strip.h>


led_strip_handle_t rgb_configure_led(void);


#ifdef __cplusplus
}
#endif
