/**
 * @file app_temp_demo.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../app.h"
#include "../../hal/hal.h"
#include "gui/gui_temp_demo.h"


namespace MOONCAKE
{
    namespace USER_APP
    {

        namespace VIDEO_SHIT
        {
            struct Data_t
            {
                HAL::HAL* hal = nullptr;
            };
        }

        class VideoShit : public APP_BASE
        {
            private:

            public:
                VideoShit() = default;
                ~VideoShit() = default;

                VIDEO_SHIT::Data_t _data;
                GUI_VideoShit _gui;


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

