/**
 * @file hal.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#define LVGL_ENABLE 0

#include "hal_common_define.h"
#include "display/hal_display.hpp"
#include "buzzer/hal_buzzer.hpp"
#include <simple_encoder_pcnt.h>
#if LVGL_ENABLE
#include "lvgl/hal_lvgl.hpp"
#endif
#include "tp/hal_tp.hpp"
#include "rtc/hal_rtc.hpp"




namespace HAL
{
    class HAL
    {
        private:
            bool _is_low_current;

            void _display_init();
            void _encoder_init();
            void _buzz_init();
            

        public:
            HAL() = default;
            ~HAL() = default;

            /* Display */
            LGFX_StampRing display;
            LGFX_Sprite* canvas;

            /* Buzzer */
            BUZZER::BUZZER buzz;

            /* Lvgl */
            #if LVGL_ENABLE
            LVGL_PORT lvgl;
            #endif

            /* Encoder */
            SIMPLE_ENCODER_PCNT::Encoder encoder;

            /* Touchpad */
            FT3267::TP_FT3267 tp;

            /* RTC */
            PCF8563::PCF8563 rtc;


            /**
             * @brief Init 
             * 
             */
            void init();

            void powerOn();
            void powerOff();


            static void _encoder_moved_callback(SIMPLE_ENCODER_PCNT::Encoder* encoder, void* userData);
            static void _encoder_button_pressed_callback(SIMPLE_ENCODER_PCNT::Button* button, void* userData);
    };



    bool i2c_init(i2c_port_t i2cPort, int sda, int scl, uint32_t clkSpeed, bool pullUpEnable);
    void encoder_test(HAL& hal);
    void i2c_scan(i2c_port_t i2c_master_port);
    void tp_test(HAL& hal);
    void rtc_test(HAL& hal);
}


