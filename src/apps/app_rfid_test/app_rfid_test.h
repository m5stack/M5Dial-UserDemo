/**
 * @file app_rfid_test.h
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
#include "gui/gui_rfid_test.h"
#include <rc522.h>


namespace MOONCAKE
{
    namespace USER_APP
    {
        namespace APP_RFID_TEST
        {
            struct Data_t
            {
                HAL::HAL* hal = nullptr;

                /* RFID */
                rc522_handle_t* rc522_handler;
            };
        }

        class RFID_Test : public APP_BASE
        {
            private:
                const char* _tag = "rfid";


                static void _rfid_event_handler(void* arg, esp_event_base_t base, int32_t event_id, void* event_data);
                void _rfid_init();
                void _callback_get_rfid_card(const uint64_t& sn);


            public:
                APP_RFID_TEST::Data_t _data;
                GUI_RFID_Test _gui;


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

