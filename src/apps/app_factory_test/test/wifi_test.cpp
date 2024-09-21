/**
 * @file wifi_test.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../app_factory_test.h"
#include "../../utilities/wifi_common_test/wifi_factory_test.h"
#include "../ft_common_define.h"


using namespace MOONCAKE::USER_APP;


void FactoryTest::_wifi_test_start_task()
{
    // wifi_factory_test();
    wifi_factory_test_start_task();
}


void FactoryTest::_wifi_test()
{
    _log("wifi test");

    


    uint32_t time_count = 0;
    while (1)
    {
        // printf("%s %s %s %d %d %d\n",
        //     wifi_factory_test_get_info()->ssid,
        //     wifi_factory_test_get_info()->password,
        //     wifi_factory_test_get_info()->ip,
        //     *(wifi_factory_test_get_info()->is_test_done),
        //     *(wifi_factory_test_get_info()->scan_num),
        //     *(wifi_factory_test_get_info()->is_connected)
        // );



        if ((millis() - time_count) > 500)
        {
            _canvas->fillScreen(TFT_BLACK);
            _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
            _canvas->setCursor(0, 40);
            _canvas->printf("  [WiFi 测试]\n");



            if (*(wifi_factory_test_get_info()->is_test_done))
            {

                if (*(wifi_factory_test_get_info()->is_connected))
                {
                    _canvas->setTextColor(TFT_GREEN, TFT_BLACK);
                    _canvas->printf("  测试通过\n");


                    _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
                    _canvas->printf("  [scan num] ");
                    _canvas->setTextColor(TFT_GREEN, TFT_BLACK);
                    _canvas->printf("%d\n", *(wifi_factory_test_get_info()->scan_num));


                    _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
                    _canvas->printf("  [IP] ");
                    _canvas->setTextColor(TFT_GREEN, TFT_BLACK);
                    _canvas->printf("%s\n", wifi_factory_test_get_info()->ip);

                    
                    _canvas->setTextColor(TFT_GREEN, TFT_BLACK);
                    _canvas->setFont(GUI_FONT_CN_SMALL);
                    _canvas->printf("\n  %s\n  %s", wifi_factory_test_get_info()->ssid, wifi_factory_test_get_info()->password);
                    _canvas->setFont(GUI_FONT_CN_BIG);



                }
                else
                {
                    _canvas->setTextColor(TFT_RED, TFT_BLACK);
                    _canvas->printf("  测试失败 \n  连接失败\n");


                    _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
                    _canvas->printf("  [scan num] ");
                    _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
                    _canvas->printf("%d\n", *(wifi_factory_test_get_info()->scan_num));


                    _canvas->setTextColor(TFT_RED, TFT_BLACK);
                    _canvas->setFont(GUI_FONT_CN_SMALL);
                    _canvas->printf("\n    %s\n    %s", wifi_factory_test_get_info()->ssid, wifi_factory_test_get_info()->password);
                    _canvas->setFont(GUI_FONT_CN_BIG);
                }


            }   
            else
            {
                _canvas->setTextColor(TFT_BLUE, TFT_BLACK);
                _canvas->printf("  测试中... \n");

                _canvas->setFont(GUI_FONT_CN_SMALL);
                _canvas->printf("\n    %s\n    %s", wifi_factory_test_get_info()->ssid, wifi_factory_test_get_info()->password);
                _canvas->setFont(GUI_FONT_CN_BIG);
            }


            _canvas_update();

            time_count = millis();
        }




        if (!_data.hal->encoder.btn.read())
        {
            while (!_data.hal->encoder.btn.read())
            {
                delay(10);
            }
            break;
        }
    }


    _log("quit wifi test");
}

