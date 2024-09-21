/**
 * @file wifi_factory_test.h
 * @author Forairaaaaa
 * @brief 
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





// #define CONFIG_ESP_WIFI_SSID            "M5-FA-Test-01"
// #define CONFIG_ESP_WIFI_PASSWORD        "M5FactoryTest??"


// #define CONFIG_ESP_WIFI_SSID            "M5-R&D"
// #define CONFIG_ESP_WIFI_PASSWORD        "echo\"password\">/dev/null"






typedef struct  
{
    char* ssid;
    char* password;
    char* ip;
    uint8_t* is_test_done;
    uint8_t* is_connected;
    uint8_t* scan_num;
} WiFiFactoryTestInfo_t;


void wifi_factory_test_start_task();

void wifi_factory_test();

WiFiFactoryTestInfo_t* wifi_factory_test_get_info();


#ifdef __cplusplus
}
#endif
