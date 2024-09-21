/**
 * @file hal_tp.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <driver/i2c.h>
#include <esp_log.h>
#include <cstring>


/** @brief FT5x06 register map and function codes */
#define FT5x06_ADDR                    (0x38)

#define FT5x06_DEVICE_MODE             (0x00)
#define FT5x06_GESTURE_ID              (0x01)
#define FT5x06_TOUCH_POINTS            (0x02)

#define FT5x06_TOUCH1_EV_FLAG          (0x03)
#define FT5x06_TOUCH1_XH               (0x03)
#define FT5x06_TOUCH1_XL               (0x04)
#define FT5x06_TOUCH1_YH               (0x05)
#define FT5x06_TOUCH1_YL               (0x06)

#define FT5x06_TOUCH2_EV_FLAG          (0x09)
#define FT5x06_TOUCH2_XH               (0x09)
#define FT5x06_TOUCH2_XL               (0x0A)
#define FT5x06_TOUCH2_YH               (0x0B)
#define FT5x06_TOUCH2_YL               (0x0C)

#define FT5x06_TOUCH3_EV_FLAG          (0x0F)
#define FT5x06_TOUCH3_XH               (0x0F)
#define FT5x06_TOUCH3_XL               (0x10)
#define FT5x06_TOUCH3_YH               (0x11)
#define FT5x06_TOUCH3_YL               (0x12)

#define FT5x06_TOUCH4_EV_FLAG          (0x15)
#define FT5x06_TOUCH4_XH               (0x15)
#define FT5x06_TOUCH4_XL               (0x16)
#define FT5x06_TOUCH4_YH               (0x17)
#define FT5x06_TOUCH4_YL               (0x18)

#define FT5x06_TOUCH5_EV_FLAG          (0x1B)
#define FT5x06_TOUCH5_XH               (0x1B)
#define FT5x06_TOUCH5_XL               (0x1C)
#define FT5x06_TOUCH5_YH               (0x1D)
#define FT5x06_TOUCH5_YL               (0x1E)

#define FT5x06_ID_G_THGROUP            (0x80)
#define FT5x06_ID_G_THPEAK             (0x81)
#define FT5x06_ID_G_THCAL              (0x82)
#define FT5x06_ID_G_THWATER            (0x83)
#define FT5x06_ID_G_THTEMP             (0x84)
#define FT5x06_ID_G_THDIFF             (0x85)
#define FT5x06_ID_G_CTRL               (0x86)
#define FT5x06_ID_G_TIME_ENTER_MONITOR (0x87)
#define FT5x06_ID_G_PERIODACTIVE       (0x88)
#define FT5x06_ID_G_PERIODMONITOR      (0x89)
#define FT5x06_ID_G_AUTO_CLB_MODE      (0xA0)
#define FT5x06_ID_G_LIB_VERSION_H      (0xA1)
#define FT5x06_ID_G_LIB_VERSION_L      (0xA2)
#define FT5x06_ID_G_CIPHER             (0xA3)
#define FT5x06_ID_G_MODE               (0xA4)
#define FT5x06_ID_G_PMODE              (0xA5)
#define FT5x06_ID_G_FIRMID             (0xA6)
#define FT5x06_ID_G_STATE              (0xA7)
#define FT5x06_ID_G_FT5201ID           (0xA8)
#define FT5x06_ID_G_ERR                (0xA9)


namespace FT3267
{
    static const char* TAG = "ft3267";


    enum ft3267_gesture_t
    {
        ft3267_gesture_none         = 0x00,
        ft3267_gesture_move_up      = 0x10,
        ft3267_gesture_move_left    = 0x14,
        ft3267_gesture_move_down    = 0x18,
        ft3267_gesture_move_right   = 0x1c,
        ft3267_gesture_zoom_in      = 0x48,
        ft3267_gesture_zoom_out     = 0x49,
    };


    struct TouchPoint_t
    {
        uint8_t touch_num = 0;
        int x = -1;
        int y = -1;
    };


    struct Config_t
    {
        i2c_port_t i2c_port = I2C_NUM_0;
        uint8_t dev_addr = FT5x06_ADDR;
    };


    class TP_FT3267
    {
        private:
            Config_t _cfg;
            uint8_t _data_buffer[7];
            TouchPoint_t _touch_point_buffer;


            inline esp_err_t _writr_reg(uint8_t reg, uint8_t data)
            {
                _data_buffer[0] = reg;
                _data_buffer[1] = data; 
                return i2c_master_write_to_device(_cfg.i2c_port, _cfg.dev_addr, _data_buffer, 2, pdMS_TO_TICKS(200));
            }


            inline esp_err_t _read_reg(uint8_t reg, uint8_t readSize)
            {
                /* Store data into buffer */
                return i2c_master_write_read_device(_cfg.i2c_port, _cfg.dev_addr, &reg, 1, _data_buffer, readSize, pdMS_TO_TICKS(200));
            }


            inline void _tp_init()
            {
                // Valid touching detect threshold
                _writr_reg(FT5x06_ID_G_THGROUP, 70);

                // valid touching peak detect threshold
                _writr_reg(FT5x06_ID_G_THPEAK, 60);

                // Touch focus threshold
                _writr_reg(FT5x06_ID_G_THCAL, 16);

                // threshold when there is surface water
                _writr_reg(FT5x06_ID_G_THWATER, 60);

                // threshold of temperature compensation
                _writr_reg(FT5x06_ID_G_THTEMP, 10);

                // Touch difference threshold
                _writr_reg(FT5x06_ID_G_THDIFF, 20);

                // Delay to enter 'Monitor' status (s)
                _writr_reg(FT5x06_ID_G_TIME_ENTER_MONITOR, 2);

                // Period of 'Active' status (ms)
                _writr_reg(FT5x06_ID_G_PERIODACTIVE, 12);

                // Timer to enter 'idle' when in 'Monitor' (ms)
                _writr_reg(FT5x06_ID_G_PERIODMONITOR, 40);

                // _read_reg(0x90, 1);
                // printf("0x%X\n", _data_buffer[0]);
                // _read_reg(FT5x06_ID_G_FIRMID, 1);
                // printf("0x%X\n", _data_buffer[0]);
                // _read_reg(FT5x06_ID_G_FT5201ID, 1);
                // printf("0x%X\n", _data_buffer[0]);
            }


        public:
            TP_FT3267()
            {
                memset(_data_buffer, 0, sizeof(_data_buffer));
            }
            ~TP_FT3267() = default;

            
            /* Config */
            inline Config_t getConfig() { return _cfg; }
            inline void setConfig(const Config_t& cfg) { _cfg = cfg; }


            inline bool init()
            {
                ESP_LOGI(TAG, "init tp ft3267");
                
                /* Interrupt pin */
                gpio_reset_pin(GPIO_NUM_14);
                gpio_set_direction(GPIO_NUM_14, GPIO_MODE_INPUT);
                gpio_set_pull_mode(GPIO_NUM_14, GPIO_PULLUP_ONLY);

                _tp_init();

                return true;
            }


            inline uint8_t getTouchPointsNum()
            {
                _data_buffer[0] = 0;
                _read_reg(FT5x06_TOUCH_POINTS, 1);
                return _data_buffer[0];
            }


            inline const TouchPoint_t& readPos()
            {
                _touch_point_buffer.touch_num = 0;
                _touch_point_buffer.x = -1;
                _touch_point_buffer.y = -1;

                /* Get touch num */
                _read_reg(FT5x06_TOUCH_POINTS, 1);
                _data_buffer[0] = _data_buffer[0] & 0x0F;
                _touch_point_buffer.touch_num = _data_buffer[0];

                /* Get postion */
                if (_data_buffer[0] != 0)
                {
                    _read_reg(FT5x06_TOUCH1_XH, 4);
                    _touch_point_buffer.x = ((_data_buffer[0] & 0x0f) << 8) + _data_buffer[1];
                    _touch_point_buffer.y = ((_data_buffer[2] & 0x0f) << 8) + _data_buffer[3];
                }

                return _touch_point_buffer;
            }


            inline bool isTouched()
            {
                return (getTouchPointsNum() > 0);
            }


            /**
             * @brief Update internal touch point buffer
             * 
             */
            inline void update()
            {
                readPos();
            }


            /**
             * @brief Get internal touch point buffer
             * 
             * @return TouchPoint_t 
             */
            inline TouchPoint_t getTouchPointBuffer()
            {
                return _touch_point_buffer;
            }
    };


}
