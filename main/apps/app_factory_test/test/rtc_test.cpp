/**
 * @file rtc_test.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../app_factory_test.h"
#include "../../app_rtc_test/app_rtc_test.h"
#include "../ft_common_define.h"


using namespace MOONCAKE::USER_APP;


void FactoryTest::_rtc_test()
{
    _log("rtc test");



    MOONCAKE::USER_APP::RTC_Test rtc_test;
    LGFX_Sprite empty;

    rtc_test.getGui()->setThemeColor(TFT_BLACK);
    rtc_test.getGui()->init(_data.hal->canvas, &empty);



    



    rtc_test.setUserData((void*)_data.hal);
    rtc_test.onSetup();
    rtc_test.onCreate();
    while (1)
    {
        rtc_test.onRunning();



        // _canvas->fillScreen(TFT_BLACK);
        _canvas->setTextSize(1);
        _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
        _canvas->setCursor(0, 40);
        _canvas->printf("  [RTC测试]\n  确保读值正常变化");
        _canvas_update();



        // if (!_data.hal->encoder.btn.read())
        // {
        //     while (!_data.hal->encoder.btn.read())
        //     {
        //         delay(10);
        //     }
        //     break;
        // }


        if (rtc_test.isGoingDestroy())
        {
            rtc_test.onDestroy();
            break;
        }
    }




    _log("quit rtc test");
}


void FactoryTest::_rtc_wakeup_test()
{
    _log("rtc wakeup test");



    




    _canvas->fillScreen(TFT_BLACK);
    _canvas->setTextSize(1);
    _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
    _canvas->setCursor(0, 40);
    _canvas->printf("  [RTC 唤醒测试]\n   请移除电源\n\n  按下按键[关机]\n  数秒后将自动启动");
    _canvas_update();

    while (1)
    {
        if (!_data.hal->encoder.btn.read())
        {
            while (!_data.hal->encoder.btn.read())
            {
                delay(10);
            }
            break;
        }
        delay(50);
    }


    _data.hal->rtc.clearIRQ();
    _data.hal->rtc.setAlarmIRQ(4);
    
    _canvas->fillScreen(TFT_BLACK);
    _canvas_update();

    delay(500);


    _data.hal->powerOff();


    while (1)
    {

        delay(1000);

    }




    _log("quit rtc wakeup test");
}
