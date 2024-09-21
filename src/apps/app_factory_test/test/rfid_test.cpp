/**
 * @file rfid_test.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../app_factory_test.h"
#include "../../app_rfid_test/app_rfid_test.h"
#include "../ft_common_define.h"


using namespace MOONCAKE::USER_APP;


void FactoryTest::_rfid_test()
{
    _log("rfid test");



    MOONCAKE::USER_APP::RFID_Test rfid_test;
    LGFX_Sprite empty;

    rfid_test.getGui()->setThemeColor(TFT_BLACK);
    rfid_test.getGui()->init(_data.hal->canvas, &empty);



    
    // _canvas->fillScreen(TFT_BLACK);
    _canvas->setTextSize(1);
    _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
    _canvas->setCursor(0, 40);
    _canvas->printf("  [RFID 测试]\n  确保能正常读卡");
    _canvas_update();


    rfid_test.setUserData((void*)_data.hal);
    rfid_test.onSetup();
    rfid_test.onCreate();
    while (1)
    {
        rfid_test.onRunning();

        // if (!_data.hal->encoder.btn.read())
        // {
        //     _log("quit");
        //     while (!_data.hal->encoder.btn.read())
        //     {
        //         delay(10);
        //     }
        //     break;
        // }

        if (rfid_test.isGoingDestroy())
        {
            rfid_test.onDestroy();
            break;
        }
    }




    _log("quit rfid test");
}
