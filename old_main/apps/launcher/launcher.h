/**
 * @file launcher.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-07-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../app.h"
#include "../../hal/hal.h"
#include "../utilities/smooth_menu/src/simple_menu/simple_menu.h"
#include "launcher_render_callback.hpp"
#include "../utilities/gui_base/gui_base.h"

#include "../app_lcd_test/app_lcd_test.h"
#include "../app_temp_demo/app_temp_demo.h"
#include "../app_rtc_test/app_rtc_test.h"
#include "../app_rfid_test/app_rfid_test.h"
#include "../app_set_brightness/app_set_brightness.h"
#include "../app_wifi_scan/app_wifi_scan.h"
#include "../app_more_menu/app_more_menu.h"
#include "../app_ble_server/app_ble_server.h"



namespace MOONCAKE
{
    namespace USER_APP
    {
        namespace LAUNCHER
        {
            struct Data_t
            {
                HAL::HAL* hal = nullptr;
                SMOOTH_MENU::Simple_Menu* menu;
                LauncherRender_CB_t* menu_render_cb;
            };
        }

        class Launcher : public APP_BASE
        {
            private:
                const char* _tag = "launcher";

                LAUNCHER::Data_t _data;
                void _menu_init();
                void _icon_list_init();
                void _launcher_init();
                void _launcher_loop();
                void _app_open_callback(uint8_t selectedNum);
                void _simple_app_manager(MOONCAKE::APP_BASE* app);

            public:
                Launcher() = default;
                ~Launcher();

            
                /**
                 * @brief Lifecycle callbacks for derived to override
                 * 
                 */
                /* Setup App configs, called when App "install()" */
                void onSetup();

                /* Life cycle */
                void onCreate();
                // void onResume();
                void onRunning();
                // void onRunningBG();
                // void onPause();
                // void onDestroy();
        };

    }
}

