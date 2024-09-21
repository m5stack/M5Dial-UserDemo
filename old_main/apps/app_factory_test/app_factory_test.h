/**
 * @file app_factory_test.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../app.h"
#include "../../hal/hal.h"
#include <vector>


#define FW_VERISON "V1.0"


namespace MOONCAKE
{
    namespace USER_APP
    {
        namespace FACTORY_TEST
        {
            struct Data_t
            {
                HAL::HAL* hal = nullptr;
            };
        }

        class FactoryTest : public APP_BASE
        {
            private:
                const char* _tag = "FactoryTest";
                

                /* Test */
                void _lcd_test();

                void _rtc_test();
                void _rtc_wakeup_test();

                void _rfid_test();
                
                void _io_test();
                void _io_test_rgb_init();
                void _io_test_adc_init();
                uint8_t _io_test_i2c_scan(std::vector<uint8_t>& addrList);

                void _wifi_test_start_task();
                void _wifi_test();

                void _ble_test();


            public:
                FACTORY_TEST::Data_t _data;


                /**
                 * @brief Lifecycle callbacks for derived to override
                 * 
                 */
                /* Setup App configs, called when App "install()" */
                void onSetup();

                /* Life cycle */
                void onCreate();
                void onRunning();
                void onDestroy();
        };

    }
}

