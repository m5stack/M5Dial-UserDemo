// /**
//  * @file app_template.h
//  * @author Forairaaaaa
//  * @brief 
//  * @version 0.1
//  * @date 2023-07-28
//  * 
//  * @copyright Copyright (c) 2023
//  * 
//  */
// #pragma once
// #include "../app.h"
// #include "../../hal/hal.h"
// #include "gui/gui_lcd_test.h"


// namespace MOONCAKE
// {
//     namespace USER_APP
//     {
//         namespace APP_TEMPLATE
//         {
//             struct Data_t
//             {
//                 HAL::HAL* hal = nullptr;
//             };
//         }

//         class AppTemplate : public APP_BASE
//         {
//             private:
//                 const char* _tag = "AppTemplate";

//             public:
//                 APP_TEMPLATE::Data_t _data;
//                 GUI_LCD_TEST _gui;


//                 /**
//                  * @brief Get gui pointer for basic settings 
//                  * 
//                  * @return GUI_Base* 
//                  */
//                 GUI_Base* getGui() override { return &_gui; }


//                 /**
//                  * @brief Lifecycle callbacks for derived to override
//                  * 
//                  */
//                 /* Setup App configs, called when App "install()" */
//                 void onSetup();

//                 /* Life cycle */
//                 void onCreate();
//                 void onRunning();
//                 void onDestroy();
//         };

//     }
// }

