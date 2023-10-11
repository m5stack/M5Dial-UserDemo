/**
 * @file va_meter_firmware.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-07-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "hal/hal.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "apps/app.h"
#include "apps/launcher/launcher.h"
#include "apps/app_factory_test/app_factory_test.h"


#define delay(ms) vTaskDelay(pdMS_TO_TICKS(ms))


extern "C" void app_main(void)
{
    HAL::HAL hal;


    /* Hardware init */
    hal.init();
    // HAL::encoder_test(hal);
    // HAL::tp_test(hal);
    // HAL::rtc_test(hal);


    
    /* Check factory test mode */
    #ifdef ENABLE_FACTORY_TEST
    bool factory_test_mode = false;

    if (!hal.encoder.btn.read())
    {   
        uint16_t time_count = 0;
        while (!hal.encoder.btn.read())
        {
            delay(10);
            time_count++;
            if ((time_count * 10) > 1000)
            {
                factory_test_mode = true;
                break;
            }
        }
    }

    // factory_test_mode = true;
    if (factory_test_mode)
    {
        hal.buzz.tone(4000, 30);
        delay(50);
        hal.buzz.tone(4000, 30);

        MOONCAKE::USER_APP::FactoryTest factory_test;
        factory_test.setUserData((void*)&hal);
        factory_test.onSetup();
        factory_test.onCreate();
        while (1)
        {
            factory_test.onRunning();
        }
    }
    #endif


    /* Start launcher */
    MOONCAKE::USER_APP::Launcher app_launcher;
    app_launcher.setUserData((void*)&hal);
    app_launcher.onSetup();
    app_launcher.onCreate();
    while (1)
    {
        app_launcher.onRunning();
    }
}
