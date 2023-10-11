/**
 * @file adc_read.h
 * @author Forairaaaaa
 * @brief https://github.com/espressif/esp-idf/blob/v5.1/examples/peripherals/adc/oneshot_read/main/oneshot_read_main.c
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
#include <esp_adc/adc_oneshot.h>


void adc_read_init();
int adc_read_get_value();


#ifdef __cplusplus
}
#endif
