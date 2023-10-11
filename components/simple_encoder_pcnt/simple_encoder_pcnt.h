/**
 * @file simple_encoder_pcnt.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-07-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "simple_encoder_pcnt.h"
#include <driver/pulse_cnt.h>
#include <esp_log.h>
#include <driver/gpio.h>
#include "Button/Button.h"


namespace SIMPLE_ENCODER_PCNT
{
    struct EncoderConfig_t
    {
        /* Pin configs */
        int encoderA_gpio_num = GPIO_NUM_NC;
        int encoderB_gpio_num = GPIO_NUM_NC;
        int pinBTN;

        /* Pcnt unit configs */
        int pcnt_high_limit = 1000;
        int pcnt_low_limit = -1000;
    }; 

    class Encoder
    {
        private:
            EncoderConfig_t _cfg;
            pcnt_unit_handle_t _pcnt_unit_handler;
            pcnt_channel_handle_t _pcnt_chan_a_handler = NULL;
            pcnt_channel_handle_t _pcnt_chan_b_handler = NULL;

            int _direction;
            int _position_buffer;

            /* Move callback */
            void* _user_data = nullptr;
            void (*_move_callback)(Encoder*, void*) = nullptr;

        public:
            Encoder();
            ~Encoder();

            /**
             * @brief Configs
             * 
             * @return EncoderConfig_t 
             */
            inline EncoderConfig_t config(void) { return _cfg; }
            inline void config(const EncoderConfig_t& cfg) { _cfg = cfg; }

            void setPins(const int& encoderA_gpio_num, const int& encoderB_gpio_num, const int& pinBTN);
            
            /**
             * @brief Init with gpio set
             * 
             * @param encoderA_gpio_num 
             * @param encoderB_gpio_num 
             */
            inline void init(const int& encoderA_gpio_num, const int& encoderB_gpio_num, const int& pinBTN)
            {
                setPins(encoderA_gpio_num, encoderB_gpio_num, pinBTN);
                init();
            }
            void init(void);

            // inline void deInit() { this->~Encoder(); }
            void deInit();
            
            /* Wrap */
            // inline esp_err_t enable() { return pcnt_unit_enable(_pcnt_unit_handler); }
            // inline esp_err_t disable() { return pcnt_unit_disable(_pcnt_unit_handler); }
            // inline esp_err_t start() { return pcnt_unit_start(_pcnt_unit_handler); }
            // inline esp_err_t stop() { return pcnt_unit_stop(_pcnt_unit_handler); }
            // inline esp_err_t clear() { return pcnt_unit_clear_count(_pcnt_unit_handler); }
            esp_err_t enable();
            esp_err_t disable();
            esp_err_t start();
            esp_err_t stop();
            esp_err_t clear();

            /**
             * @brief Read encoder current count
             * 
             * @return int 
             */
            int readCount();

            /**
             * @brief Read encoder current count then clear
             * 
             * @return int 
             */
            int readCountClear();


            /* Same API to Simple encoder */
            const int& getDirection();
            inline int getPosition() { return readCount(); }
            void resetPosition();
            bool wasMoved(bool updateDirection = false);

            /* Button */
            Button btn;


            /**
             * @brief Set the encoder Moved Callback 
             * 
             * @param moveCallback 
             * @param userData 
             */
            inline void setMovedCallback(void (*moveCallback)(Encoder*, void*), void* userData)
            {
                _move_callback = moveCallback;
                _user_data = userData;
            }

    };

}
