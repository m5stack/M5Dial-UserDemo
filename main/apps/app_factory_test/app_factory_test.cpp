/**
 * @file app_factory_test.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-08-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "app_factory_test.h"
#include "../common_define.h"

using namespace MOONCAKE::USER_APP;

void FactoryTest::onSetup()
{
    setAppName("FactoryTest");
    setAllowBgRunning(false);

    /* Copy default value */
    FACTORY_TEST::Data_t default_data;
    _data = default_data;

    _data.hal = (HAL::HAL*)getUserData();
}

/* Life cycle */
void FactoryTest::onCreate()
{
    _log("onCreate");

    // _wifi_test_start_task();
    _lcd_test();
    _rtc_test();
    _rfid_test();
    _io_test();
    // _wifi_test();
    // _ble_test();
    _rtc_wakeup_test();
}

void FactoryTest::onRunning()
{
    /* If scrolled */
    if (_data.hal->encoder.wasMoved(true))
    {
        // printf("%d\n", _data.hal->encoder.getPosition());
        if (_data.hal->encoder.getDirection() < 1)
        {
        }
        else
        {
        }
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
        _data.hal->tp.update();
        _log("%d %d", _data.hal->tp.getTouchPointBuffer().x, _data.hal->tp.getTouchPointBuffer().y);
    }
}

void FactoryTest::onDestroy() { _log("onDestroy"); }
