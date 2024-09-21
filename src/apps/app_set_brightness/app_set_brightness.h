/**
 * @file app_set_brightness.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../app.h"
#include "../../hal/hal.h"
#include "gui/gui_set_brightness.h"
#include "../utilities/smooth_menu/src/lv_anim/lv_anim.h"


namespace MOONCAKE
{
    namespace USER_APP
    {
        namespace SET_BRIGHTNESS
        {
            struct Data_t
            {
                HAL::HAL* hal = nullptr;
                
                int16_t brightness = 128;
                int delta_time = 0;
                int brightness_increment;
                uint32_t scroll_speed_time_count = 0;

                LVGL::Anim_Path brightness_anim;
            };
        }

        class Set_Brightness : public APP_BASE
        {
            private:
                const char* _tag = "brightness";

            public:
                SET_BRIGHTNESS::Data_t _data;
                GUI_SetBrightness _gui;


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

