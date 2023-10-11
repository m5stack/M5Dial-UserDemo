// /**
//  * @file app_template.cpp
//  * @author Forairaaaaa
//  * @brief 
//  * @version 0.1
//  * @date 2023-07-28
//  * 
//  * @copyright Copyright (c) 2023
//  * 
//  */
// #include "app_template.h"
// #include "../common_define.h"


// using namespace MOONCAKE::USER_APP;


// void AppTemplate::onSetup()
// {
//     setAppName("AppTemplate");
//     setAllowBgRunning(false);

//     /* Copy default value */
//     APP_TEMPLATE::Data_t default_data;
//     _data = default_data;

//     _data.hal = (HAL::HAL*)getUserData();
// }


// /* Life cycle */
// void AppTemplate::onCreate()
// {
//     _log("onCreate");
// }


// void AppTemplate::onRunning()
// {
//     /* If scrolled */
//     if (_data.hal->encoder.wasMoved(true))
//     {
//         // printf("%d\n", _data.hal->encoder.getPosition());
//         if (_data.hal->encoder.getDirection() < 1)
//         {

//         }
//         else
//         {

//         }
//     }

//     /* If button pressed */
//     if (!_data.hal->encoder.btn.read())
//     {
//         /* Hold until button release */
//         while (!_data.hal->encoder.btn.read())
//             delay(5);

//         /* Bye */
//         destroyApp();
//     }

//     /* If touched */
//     if (_data.hal->tp.isTouched())
//     {
//         _data.hal->tp.update();
//         _log("%d %d", _data.hal->tp.getTouchPointBuffer().x, _data.hal->tp.getTouchPointBuffer().y);
//     }
// }


// void AppTemplate::onDestroy()
// {
//     _log("onDestroy");
// }
