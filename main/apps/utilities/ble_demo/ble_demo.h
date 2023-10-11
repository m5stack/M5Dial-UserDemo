/**
 * @file ble_demo.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


typedef struct  
{
    char* device_name;
    uint8_t* sending_data;
    uint8_t* is_connected;
    uint8_t* is_subscribed;
} BLEDemoInfo_t;


void ble_demo_start();
void ble_demo_stop();
BLEDemoInfo_t* ble_demo_get_infos();


#ifdef __cplusplus
}
#endif
