/**
 * @file app_template.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-07-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_set_brightness.h"
#include "../common_define.h"


using namespace MOONCAKE::USER_APP;


void Set_Brightness::onSetup()
{
    // setAppName("Set_Brightness");
    setAllowBgRunning(false);

    /* Copy default value */
    SET_BRIGHTNESS::Data_t default_data;
    _data = default_data;

    _data.hal = (HAL::HAL*)getUserData();
}


/* Life cycle */
void Set_Brightness::onCreate()
{
    _log("onCreate");

    /* Get current brightness */
    _data.brightness = _data.hal->display.getBrightness();
    _log("get brightness: %d\n", _data.brightness);

    /* Update page for the first time */
    _gui.renderPage(_data.brightness);

    /* Anim init */
    _data.brightness_anim.setAnim(LVGL::ease_out, _data.brightness, _data.brightness, 0);
}


void Set_Brightness::onRunning()
{
    /* If scrolled */
    if (_data.hal->encoder.wasMoved(true))
    {
        /* Get scroll delta */
        _data.delta_time = millis() - _data.scroll_speed_time_count;

        /* Get increment */
        /* y = -(1/8)x + 10 */
        _data.brightness_increment = 10 - _data.delta_time / 8;
        /* Y = 1 */
        if (_data.brightness_increment < 1)
        {
            _data.brightness_increment = 1;
        }
        // _log("delta: %d increment: %d", _data.delta_time, _data.brightness_increment);
        

        // printf("%d\n", _data.hal->encoder.getPosition());
        if (_data.hal->encoder.getDirection() < 1)
        {
            _data.brightness += _data.brightness_increment;
            if (_data.brightness > 0xFF)
            {
                _data.brightness = 0xFF;
            }
        }
        else
        {
            _data.brightness -= _data.brightness_increment;
            if (_data.brightness < 0)
            {
                _data.brightness = 0;
            }
        }

        /* Set brightness */
        _log("set to: %d", _data.brightness);
        _gui.renderPage(_data.brightness);
        // _data.hal->display.setBrightness(_data.brightness);


        /* Reset anim */
        _data.brightness_anim.setAnim(LVGL::ease_out, _data.brightness_anim.getValue(millis()), _data.brightness, 600);
        _data.brightness_anim.resetTime(millis());
        

        /* Reset time count */
        _data.scroll_speed_time_count = millis();
    }


    /* Update brightness */
    if (!_data.brightness_anim.isFinished(millis()))
    {
        _data.hal->display.setBrightness(_data.brightness_anim.getValue(millis()));
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


void Set_Brightness::onDestroy()
{
    _log("onDestroy");
}
