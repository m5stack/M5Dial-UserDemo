/**
 * @file app_wifi_scan.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_wifi_scan.h"
#include "../common_define.h"
#include "../utilities/wifi_common_test/wifi_common_test.h"



using namespace MOONCAKE::USER_APP;


void WiFi_Scan::_scan_wifi()
{
    _log("start wifi scan...");

    uint8_t wifi_num = WIFI_COMMON_TEST::SCAN::scan(_data.wifi_scan_result);
    
    _log("get wifi num: %d", wifi_num);
    _log("result:");
    printf("%s", _data.wifi_scan_result.c_str());


    /* Update page */
    _gui.renderPage(_data.menu_y_offset, _data.wifi_scan_result);
}


void WiFi_Scan::onSetup()
{
    // setAppName("WiFi_Scan");
    setAllowBgRunning(false);

    /* Copy default value */
    WIFI_SCAN::Data_t default_data;
    _data = default_data;

    _data.hal = (HAL::HAL*)getUserData();
}


/* Life cycle */
void WiFi_Scan::onCreate()
{
    _log("onCreate");

    _scan_wifi();
    
    /* Anim init */
    _data.menu_y_offset_anim.setAnim(LVGL::overshoot, 100, 0, 600);
    _data.menu_y_offset_anim.resetTime(millis());
}


void WiFi_Scan::onRunning()
{
    /* If scrolled */
    if (_data.hal->encoder.wasMoved(true))
    {
        /* Get scroll delta */
        _data.delta_time = millis() - _data.scroll_speed_time_count;

        /* Get increment */
        /* y = -(1/8)x + 25 */
        _data.offset_increment = 25 - _data.delta_time / 8;
        /* Y = 1 */
        if (_data.offset_increment < 1)
        {
            _data.offset_increment = 1;
        }
        // _log("delta: %d increment: %d", _data.delta_time, _data.offset_increment);


        // printf("%d\n", _data.hal->encoder.getPosition());
        if (_data.hal->encoder.getDirection() < 1)
        {
            _data.menu_y_offset -= _data.offset_increment;
        }
        else
        {
            _data.menu_y_offset += _data.offset_increment;
        }


        /* Reset anim */
        _data.menu_y_offset_anim.setAnim(LVGL::overshoot, _data.menu_y_offset_anim.getValue(millis()), _data.menu_y_offset, 600);
        _data.menu_y_offset_anim.resetTime(millis());


        // /* Update page */
        // _gui.renderPage(_data.menu_y_offset, _data.wifi_scan_result);


        /* Reset time count */
        _data.scroll_speed_time_count = millis();
    }


    /* Update page */
    _gui.renderPage(_data.menu_y_offset_anim.getValue(millis()), _data.wifi_scan_result);


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


void WiFi_Scan::onDestroy()
{
    _log("onDestroy");
}

