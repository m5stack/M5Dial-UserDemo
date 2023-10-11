/**
 * @file ble_test.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../app_factory_test.h"
#include "../../app_ble_server/app_ble_server.h"
#include "../ft_common_define.h"


using namespace MOONCAKE::USER_APP;


void FactoryTest::_ble_test()
{
    _log("ble test");




    MOONCAKE::USER_APP::BLE_Server ble_test;
    LGFX_Sprite empty;

    ble_test.getGui()->setThemeColor(TFT_BLACK);
    ble_test.getGui()->init(_data.hal->canvas, &empty);



    



    ble_test.setUserData((void*)_data.hal);
    ble_test.onSetup();
    ble_test.onCreate();
    while (1)
    {
        ble_test.onRunning();



        // _canvas->fillScreen(TFT_BLACK);
        _canvas->setTextSize(1);
        _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
        _canvas->setCursor(0, 40);
        _canvas->printf("  [BLE 测试]\n  手机连接");
        _canvas_update();



        // if (!_data.hal->encoder.btn.read())
        // {
        //     while (!_data.hal->encoder.btn.read())
        //     {
        //         delay(10);
        //     }
        //     break;
        // }


        if (ble_test.isGoingDestroy())
        {
            ble_test.onDestroy();
            break;
        }
    }






    _log("quit ble test");
}
