/**
 * @file app_wifi_scan.h
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
#include "gui/gui_wifi_scan.h"
#include "../utilities/smooth_menu/src/lv_anim/lv_anim.h"


namespace MOONCAKE
{
    namespace USER_APP
    {
        namespace WIFI_SCAN
        {
            struct Data_t
            {
                HAL::HAL* hal = nullptr;

                int delta_time = 0;
                int offset_increment = 0;
                uint32_t scroll_speed_time_count = 0;

                int menu_y_offset = 0;
                std::string wifi_scan_result;

                LVGL::Anim_Path menu_y_offset_anim;
            };
        }

        class WiFi_Scan : public APP_BASE
        {
            private:
                const char* _tag = "wifi";
                void _scan_wifi();

            public:
                WIFI_SCAN::Data_t _data;
                GUI_WiFi_Scan _gui;


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

