/**
 * @file lcd_test.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../app_factory_test.h"
#include "../../app_lcd_test/app_lcd_test.h"
#include "../ft_common_define.h"


using namespace MOONCAKE::USER_APP;


void FactoryTest::_lcd_test()
{
    _log("lcd test");


    _canvas->fillScreen(TFT_BLACK);
    _canvas_update();

    _canvas->setFont(GUI_FONT_CN_BIG);
    _canvas->setTextSize(1);


    _canvas->setTextColor(TFT_YELLOW);
    _canvas->setCursor(20, 20);
    _canvas->printf("[M5Dial测试]\n  %s\n  %s\n\n  松开按键\n  进入测试模式", FW_VERISON, __DATE__);

    _canvas_update();


    while (!_data.hal->encoder.btn.read())
    {
        delay(100);
    }



    MOONCAKE::USER_APP::LCD_Test lcd_test;
    LGFX_Sprite empty;

    lcd_test.getGui()->setThemeColor(TFT_BLACK);
    lcd_test.getGui()->init(_data.hal->canvas, &empty);



    _canvas->fillScreen(TFT_BLACK);
    _canvas->setTextSize(1);
    _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
    _canvas->setCursor(0, 40);
    _canvas->printf("  [LCD] [触摸]\n  [编码器] 测试\n\n  旋转切换颜色\n  按钮下一项");
    _canvas_update();



    lcd_test.setUserData((void*)_data.hal);
    lcd_test.onSetup();
    lcd_test.onCreate();
    while (1)
    {
        // printf("????\n");
        // delay(1000);


        lcd_test.onRunning();

        // if (!_data.hal->encoder.btn.read())
        // {
        //     while (!_data.hal->encoder.btn.read())
        //     {
        //         delay(10);
        //     }
        //     break;
        // }

        if (lcd_test.isGoingDestroy())
        {
            lcd_test.onDestroy();
            break;
        }


        
    }
    

    _log("quit lcd test");
}
