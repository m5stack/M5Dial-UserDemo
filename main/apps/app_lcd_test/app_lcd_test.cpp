/**
 * @file app_lcd_test.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-07-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_lcd_test.h"
#include "../common_define.h"


using namespace MOONCAKE::USER_APP;


void LCD_Test::onSetup()
{
    // setAppName("LCD_Test");
    setAllowBgRunning(false);

    /* Copy default value */
    LCD_TEST::Data_t default_data;
    _data = default_data;

    _data.hal = (HAL::HAL*)getUserData();
}


/* Life cycle */
void LCD_Test::onCreate()
{
    _log("onCreate");

    /* Wait until released */
    while (_data.hal->tp.isTouched())
    {
        delay(5);
    }
}


void LCD_Test::onRunning()
{
    /* If scrolled */
    if (_data.hal->encoder.wasMoved(true))
    {
        // printf("%d\n", _data.hal->encoder.getPosition());
        if (_data.hal->encoder.getDirection() < 1)
            _gui.goNextPage();
        else 
            _gui.goLastPage();
        
        /* Lower frequency */
        delay(100);
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

    /* If touched */
    if (_data.hal->tp.isTouched())
    {
        _data.hal->tp.update();
        _gui.renderTp(_data.hal->tp.getTouchPointBuffer().x, _data.hal->tp.getTouchPointBuffer().y);
    }

    // delay(5);
}


void LCD_Test::onDestroy()
{
    _log("onDestroy");
}

