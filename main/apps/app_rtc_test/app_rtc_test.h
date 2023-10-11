/**
 * @file app_rtc_test.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../app.h"
#include "../../hal/hal.h"
#include "gui/gui_rtc_test.h"


namespace MOONCAKE
{
    namespace USER_APP
    {
        namespace RTC_TEST
        {
            struct Data_t
            {
                HAL::HAL* hal = nullptr;
                tm rtc_time;
                uint32_t time_count = 0;
            };
        }

        class RTC_Test : public APP_BASE
        {
            private:
                const char* _tag = "rtc";

            public:
                RTC_TEST::Data_t _data;
                GUI_RTC_Test _gui;


                /**
                 * @brief Get gui pointer for basic settings 
                 * 
                 * @return GUI_Base* 
                 */
                GUI_Base* getGui() override { return &_gui; }


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

