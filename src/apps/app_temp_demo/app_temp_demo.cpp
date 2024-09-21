/**
 * @file app_temp_demo.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_temp_demo.h"


#define delay(ms) vTaskDelay(pdMS_TO_TICKS(ms))
#define millis() (esp_timer_get_time() / 1000)


namespace MOONCAKE
{
    namespace USER_APP
    {
        void VideoShit::onSetup()
        {
            setAppName("Video Shit");
            setAllowBgRunning(false);

            /* Init with default value */
            VIDEO_SHIT::Data_t default_data;
            _data = default_data;

            _data.hal = (HAL::HAL*)getUserData();
        }


        /* Life cycle */
        void VideoShit::onCreate()
        {
            printf("[%s] onCreate\n", getAppName().c_str());
        }


        void VideoShit::onRunning()
        {
            /* If scrolled */
            if (_data.hal->encoder.wasMoved(true))
            {
                // printf("%d\n", _data.hal->encoder.getPosition());
                if (_data.hal->encoder.getDirection() < 1)
                    _gui.tempUp();
                else 
                    _gui.tempDown();
                
                /* Lower frequency */
                delay(100);
            }

            /* If button pressed */
            if (!_data.hal->encoder.btn.read())
            {
                /* Hold until button release */
                while (!_data.hal->encoder.btn.read())
                    delay(5);

                /* Bye */
                destroyApp();
            }

            /* If touched */
            if (_data.hal->tp.isTouched())
            {
                _gui.buttonPressed();
                while (_data.hal->tp.isTouched())
                {
                    delay(5);
                }
                _gui.buttonReleased();
            }

            // delay(5);
        }


        void VideoShit::onDestroy()
        {
            printf("[%s] onDestroy\n", getAppName().c_str());
        }
    }
}

