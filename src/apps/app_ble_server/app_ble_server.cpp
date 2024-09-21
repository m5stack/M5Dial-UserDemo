/**
 * @file app_ble_server.cpp
 * @author Forairaaaaa
 * @brief https://github.com/espressif/arduino-esp32/blob/esp-idf-v5.2/libraries/BLE/examples/BLE_server/BLE_server.ino
 * @version 0.1
 * @date 2023-08-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_ble_server.h"
#include "../common_define.h"
#include <esp_mac.h>
#include "../utilities/ble_demo/ble_demo.h"


using namespace MOONCAKE::USER_APP;



void BLE_Server::_ble_init()
{
    _log("Starting BLE work!");

    /* Start ble demo */
    ble_demo_start();
    _log_mem();
}


void BLE_Server::onSetup()
{
    setAppName("BLE_Server");
    setAllowBgRunning(false);

    /* Copy default value */
    BLE_SERVER::Data_t default_data;
    _data = default_data;

    _data.hal = (HAL::HAL*)getUserData();
}


/* Life cycle */
void BLE_Server::onCreate()
{
    _log("onCreate");
    _ble_init();
}


void BLE_Server::onRunning()
{
    if ((millis() - _data.ble_page_update_time_count) > _data.ble_page_update_interval)
    {

        // printf("%s %d %d %d\n",
        //     ble_demo_get_infos()->device_name,
        //     *(ble_demo_get_infos()->sending_data),
        //     *(ble_demo_get_infos()->is_connected),
        //     *(ble_demo_get_infos()->is_subscribed)
        // );


        char info[48];

        if (*(ble_demo_get_infos()->is_subscribed))
        {
            snprintf(info, 48, "send %d", *(ble_demo_get_infos()->sending_data));
        }
        else 
        {
            snprintf(info, 48, "no subscribe");
        }



        /* Update page */
        _gui.renderPage(
            (GUI_BLE_Server::BLEStatus_t)*(ble_demo_get_infos()->is_connected),
            ble_demo_get_infos()->device_name,
            info
        );


        /* Reset */
        _data.ble_page_update_time_count = millis();
    }


    /* If button pressed */
    if (!_data.hal->encoder.btn.read())
    {
        /* Hold until button release */
        while (!_data.hal->encoder.btn.read())
            delay(5);

        /* Bye */
        destroyApp();
    }
}


void BLE_Server::onDestroy()
{
    _log("onDestroy");

    /* Close ble demo */
    ble_demo_stop();
}
