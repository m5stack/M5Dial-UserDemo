/*
	Button - a small library for Arduino to handle button debouncing
	
	MIT licensed.
*/
#pragma once
// #ifndef Button_h
// #define Button_h
// #include "Arduino.h"
#include <stdio.h>

namespace SIMPLE_ENCODER_PCNT {

    class Button
    {
        public:
            Button(uint8_t pin = 0, uint16_t debounce_ms = 100);
            void setPin(uint8_t pin);
            void setDebounce(uint16_t ms);
            void begin();
            bool read();
            bool toggled();
            bool pressed();
            bool released();
            bool has_changed();
            
            const static bool PRESSED = 0;
            const static bool RELEASED = 1;


            /**
             * @brief Set the Pressed Callback
             * 
             * @param pressedCallback 
             * @param userData 
             */
            inline void setPressedCallback(void (*pressedCallback)(Button*, void*), void* userData)
            {
                _pressed_callback = pressedCallback;
                _user_data = userData;
            }
        
        private:
            uint8_t  _pin;
            uint16_t _delay;
            bool     _state;
            uint32_t _ignore_until;
            bool     _has_changed;

            /* Pressed callback */
            void* _user_data = nullptr;
            void (*_pressed_callback)(Button*, void*) = nullptr;
    };

}

// #endif