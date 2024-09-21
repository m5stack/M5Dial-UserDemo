/**
 * @file io_test.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../app_factory_test.h"
#include "../../utilities/rgb/io_test_rgb.h"
#include "../../utilities/adc_read/adc_read.h"
#include "../ft_common_define.h"


static led_strip_handle_t _led_strip;


using namespace MOONCAKE::USER_APP;






void FactoryTest::_io_test()
{
    _log("io test");



    
    // _canvas->fillScreen(TFT_BLACK);
    _canvas->setTextSize(1);
    _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
    _canvas->setCursor(0, 40);
    _canvas->printf("  [IO 测试]");
    _canvas_update();


    _io_test_rgb_init();
    _io_test_adc_init();


    // uint8_t shit = 0;
    int adc_read_buffer = 0;
    int led_light_num = 0;

    uint32_t i2c_scan_time_count = 0;
    std::vector<uint8_t> i2c_scan_result;



    while (1)
    {
        // shit++;
        // led_strip_set_pixel(_led_strip, 13, shit, shit, shit);
        // led_strip_refresh(_led_strip);

        // _log("%d", adc_read_get_value());


        /* Update Port B shit */
        adc_read_buffer = adc_read_get_value();
        adc_read_buffer = 3000 - adc_read_buffer;
        if (adc_read_buffer > 2900)
        {
            adc_read_buffer = 3000;
        }
    
        led_light_num = adc_read_buffer / 500;

        for (int i = 0; i < 14; i++)
        {
            // led_strip_set_pixel(_led_strip, i, 12, 123, 12);
            // led_strip_set_pixel(_led_strip, (13 - i), 12, 123, 12);

            if (i <= led_light_num)
            {
                led_strip_set_pixel(_led_strip, i, 1, 23, 1);
            }
            else if ((13 - i) <= led_light_num)
            {
                led_strip_set_pixel(_led_strip, i, 1, 23, 1);
            }
            else 
            {
                led_strip_set_pixel(_led_strip, i, 0, 0, 0);
            }
        }
        led_strip_refresh(_led_strip);
        

        // _log("%d %d", led_light_num, adc_read_buffer);


        




        /* Update Port A shit */
        if ((millis() - i2c_scan_time_count) > 800)
        {

            _io_test_i2c_scan(i2c_scan_result);


            // _log("%d\n", i2c_scan_result.size());


            i2c_scan_time_count = millis();
        }








        




        _canvas->fillScreen(TFT_BLACK);
        _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
        _canvas->setCursor(0, 40);
        _canvas->printf("  [IO 测试]\n");



        _canvas->setTextColor(TFT_WHITE, TFT_BLACK);
        _canvas->printf("\n  [电池] ");
        _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
        _canvas->printf("%.1fv\n", ((float)adc_read_buffer / 1000));




        _canvas->setTextColor(TFT_WHITE, TFT_BLACK);
        _canvas->printf("  [PORT-B] ");
        _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
        _canvas->printf("%d\n", adc_read_buffer);





        _canvas->setTextColor(TFT_WHITE, TFT_BLACK);
        _canvas->printf("  [PORT-A] ");



        
        if (i2c_scan_result.size() > 0)
        {
            _canvas->setTextColor(TFT_YELLOW, TFT_BLACK);
            // _canvas->printf("%d个\n  ", i2c_scan_result.size());

            _canvas->setTextColor(TFT_GREEN, TFT_BLACK);
            for (const auto& i : i2c_scan_result)
            {
                _canvas->printf("0x%02X ", i);
            }
        }
        else
        {
            _canvas->setTextColor(TFT_RED, TFT_BLACK);
            _canvas->printf("无");
        }




        _canvas_update();







        if (!_data.hal->encoder.btn.read())
        {
            while (!_data.hal->encoder.btn.read())
            {
                delay(10);
            }
            break;
        }
    }



    _log("quit io test");
}




void FactoryTest::_io_test_rgb_init()
{

    // led_strip_handle_t led_shit = rgb_configure_led();

    _led_strip = rgb_configure_led();

    

    // uint8_t shit = 0;


    // while (1)
    // {
    //     shit++;

    

    //     for (int i = 0; i < 14; i++)
    //     {
    //         ESP_ERROR_CHECK(led_strip_set_pixel(led_shit, i, shit, shit, shit));
    //     }
    //     ESP_ERROR_CHECK(led_strip_refresh(led_shit));

    //     _log("??? %d", shit);
    //     delay(10);
    // }

}


void FactoryTest::_io_test_adc_init()
{
    adc_read_init();
}


#define TAG "i2c"

static bool _is_i2c_inited = false;

uint8_t FactoryTest::_io_test_i2c_scan(std::vector<uint8_t>& addrList)
{   
    i2c_port_t i2c_master_port = I2C_NUM_1;



    if (!_is_i2c_inited)
    {
        ESP_LOGD(TAG, "init i2c");

        esp_err_t ret;

        /* I2C config */
        i2c_config_t conf;
        memset(&conf, 0, sizeof(i2c_config_t));
        conf.mode = I2C_MODE_MASTER;
        conf.sda_io_num = 13;
        conf.scl_io_num = 15;
        conf.master.clk_speed = 100000;
        // if (pullUpEnable)
        // {
            conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
            conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
        // }
        // else
        // {
        //     conf.sda_pullup_en = GPIO_PULLUP_DISABLE;
        //     conf.scl_pullup_en = GPIO_PULLUP_DISABLE;
        // }
        conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;
        ret = i2c_param_config(i2c_master_port, &conf);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "I2C config failed");
            return false;
        }
        ESP_LOGI(TAG, "I2C config ok");

        /* Install driver */
        ret = i2c_driver_install(i2c_master_port, I2C_MODE_MASTER, 0, 0, 0);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "I2C driver install failed");
            return false;
        }
        ESP_LOGI(TAG, "I2C driver install ok");

        // return true;

        _is_i2c_inited = true;
    }




    addrList.clear();



    uint8_t WRITE_BIT = I2C_MASTER_WRITE;  /*!< I2C master write */
    // uint8_t READ_BIT = I2C_MASTER_READ;    /*!< I2C master read */
    uint8_t ACK_CHECK_EN = 0x1;            /*!< I2C master will check ack from slave*/
    // uint8_t ACK_CHECK_DIS = 0x0;           /*!< I2C master will not check ack from slave */

    uint8_t address;
    printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");
    for (int i = 0; i < 128; i += 16)
    {
        printf("%02x: ", i);
        for (int j = 0; j < 16; j++)
        {
            fflush(stdout);
            address = i + j;
            i2c_cmd_handle_t cmd = i2c_cmd_link_create();
            i2c_master_start(cmd);
            i2c_master_write_byte(cmd, (address << 1) | WRITE_BIT, ACK_CHECK_EN);
            i2c_master_stop(cmd);
            esp_err_t ret = i2c_master_cmd_begin(i2c_master_port, cmd, portMAX_DELAY);
            i2c_cmd_link_delete(cmd);
            if (ret == ESP_OK)
            {
                printf("%02x ", address);
                addrList.push_back(address);
            }
            else if (ret == ESP_ERR_TIMEOUT)
            {
                printf("UU ");
            }
            else
            {
                printf("-- ");
            }
        }
        printf("\r\n");
    }



    return 0;
}


