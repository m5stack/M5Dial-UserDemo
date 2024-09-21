/**
 * @file app_rfid_test.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_rfid_test.h"
#include <esp_log.h>
#include "../common_define.h"


#define RFID_I2C_PORT I2C_NUM_0


using namespace MOONCAKE::USER_APP;



void RFID_Test::_rfid_event_handler(void* arg, esp_event_base_t base, int32_t event_id, void* event_data)
{
    if (event_id == RC522_EVENT_TAG_SCANNED)
    {
        /* Get data */
        rc522_event_data_t* data = (rc522_event_data_t*) event_data;
        rc522_tag_t* tag = (rc522_tag_t*) data->ptr;
        // ESP_LOGI("rfid", "Tag scanned (sn: %" PRIu64 ")", tag->serial_number);

        /* Get App and hit callback */
        ((RFID_Test*)arg)->_callback_get_rfid_card(tag->serial_number);
    }
}


void RFID_Test::_rfid_init()
{
    _log("init rc522");

    /* Setup config */
    rc522_config_t config;
    memset(&config, 0, sizeof(rc522_config_t));
    config.transport = RC522_TRANSPORT_I2C;
    config.i2c.port = RFID_I2C_PORT;

    /* Create handler */
    _data.rc522_handler = new rc522_handle_t;

    /* Init */
    rc522_create(&config, _data.rc522_handler);
    /* Set event handler */
    rc522_register_events(*_data.rc522_handler, RC522_EVENT_ANY, _rfid_event_handler, this);
    /* Start this shit */
    rc522_start(*_data.rc522_handler);
}


void RFID_Test::_callback_get_rfid_card(const uint64_t& sn)
{
    _log("Tag scanned (sn: %" PRIu64 ")", sn);

    /* Bi */
    _data.hal->buzz.tone(4000, 100);

    /* Updata page */
    _gui.renderPage(sn);
}


void RFID_Test::onSetup()
{
    // setAppName("RFID_Test");
    setAllowBgRunning(false);

    /* Copy default value */
    APP_RFID_TEST::Data_t default_data;
    _data = default_data;

    _data.hal = (HAL::HAL*)getUserData();
}


/* Life cycle */
void RFID_Test::onCreate()
{
    _log("onCreate");

    _rfid_init();
}


void RFID_Test::onRunning()
{
    // if (_data.hal->tp.isTouched())
    // {
    //     _data.hal->tp.update();
    //     printf("%d %d\n", _data.hal->tp.getTouchPointBuffer().x, _data.hal->tp.getTouchPointBuffer().y);
    // }

    /* If button pressed */
    if (!_data.hal->encoder.btn.read())
    {
        /* Hold until button release */
        while (!_data.hal->encoder.btn.read())
            delay(5);

        /* Bye */
        destroyApp();
    }
}


void RFID_Test::onDestroy()
{
    _log("onDestroy");

    /* Deinit RC522 */
    rc522_unregister_events(*_data.rc522_handler, RC522_EVENT_ANY, _rfid_event_handler);
    rc522_destroy(*_data.rc522_handler);

    /* Free */
    delete _data.rc522_handler;
}
