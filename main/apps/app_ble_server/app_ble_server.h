/**
 * @file app_ble_server.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../app.h"
#include "../../hal/hal.h"
#include "gui/gui_ble_server.h"


namespace MOONCAKE
{
    namespace USER_APP
    {
        namespace BLE_SERVER
        {
            struct Data_t
            {
                HAL::HAL* hal = nullptr;

                std::string ble_device_name;
                // BLEServer* pServer = nullptr;
                // BLEService* pService = nullptr;
                // BLECharacteristic* pCharacteristic = nullptr;

                uint32_t ble_page_update_interval = 1000;
                uint32_t ble_page_update_time_count = 0;
            };
        }

        class BLE_Server : public APP_BASE
        {
            private:
                const char* _tag = "BLE_Server";
                void _ble_init();

            public:
                BLE_SERVER::Data_t _data;
                GUI_BLE_Server _gui;


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

