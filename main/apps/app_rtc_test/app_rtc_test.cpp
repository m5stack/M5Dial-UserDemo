/**
 * @file app_rtc_test.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_rtc_test.h"
#include "../common_define.h"


using namespace MOONCAKE::USER_APP;


void RTC_Test::onSetup()
{
    // setAppName("RTC_Test");
    setAllowBgRunning(false);

    /* Copy default value */
    RTC_TEST::Data_t default_data;
    _data = default_data;

    _data.hal = (HAL::HAL*)getUserData();
}


/* Life cycle */
void RTC_Test::onCreate()
{
    _log("onCreate");
}


void RTC_Test::onRunning()
{
    /* If button pressed */
    if (!_data.hal->encoder.btn.read())
    {
        /* Hold until button release */
        while (!_data.hal->encoder.btn.read())
            delay(5);

        /* Bye */
        destroyApp();
    }

    /* Update page */
    if ((millis() - _data.time_count) > 1000)
    {
        _data.hal->rtc.getTime(_data.rtc_time);
        _log("%d:%d:%d", _data.rtc_time.tm_hour, _data.rtc_time.tm_min, _data.rtc_time.tm_sec);

        _gui.renderPage(_data.rtc_time.tm_hour, _data.rtc_time.tm_min, _data.rtc_time.tm_sec);
        
        _data.time_count = millis();
    }
}


void RTC_Test::onDestroy()
{
    _log("onDestroy");
}

