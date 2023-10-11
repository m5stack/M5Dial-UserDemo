/**
 * @file app_lcd_test.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-07-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../app.h"
#include "../../hal/hal.h"
#include "gui/gui_lcd_test.h"


namespace MOONCAKE
{
    namespace USER_APP
    {
        namespace LCD_TEST
        {
            struct Data_t
            {
                HAL::HAL* hal = nullptr;
            };
        }

        class LCD_Test : public APP_BASE
        {
            private:
                const char* _tag = "lcd";

                LCD_TEST::Data_t _data;
                GUI_LCD_TEST _gui;
                

            public:
                
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

