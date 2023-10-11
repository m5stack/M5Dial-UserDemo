/**
 * @file gui_temp_demo.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../utilities/gui_base/gui_base.h"


#include "temp_demo_icons/temp_demo_button_pressed.h"
#include "temp_demo_icons/temp_demo_button_released.h"
#include "temp_demo_icons/temp_demo_1.h"
#include "temp_demo_icons/temp_demo_2.h"
#include "temp_demo_icons/temp_demo_3.h"
#include "temp_demo_icons/temp_demo_4.h"
#include "temp_demo_icons/temp_demo_5.h"
#include "temp_demo_icons/temp_demo_6.h"
#include "temp_demo_icons/temp_demo_7.h"
#include "temp_demo_icons/temp_demo_8.h"
#include "temp_demo_icons/temp_demo_9.h"


static std::array<const uint16_t*, 9> _pic_temp_list =
{
    image_data_temp_demo_1,
    image_data_temp_demo_2,
    image_data_temp_demo_3,
    image_data_temp_demo_4,
    image_data_temp_demo_5,
    image_data_temp_demo_6,
    image_data_temp_demo_7,
    image_data_temp_demo_8,
    image_data_temp_demo_9
};
static std::array<const uint16_t*, 2> _pic_button_list =
{
    image_data_temp_demo_button_released,
    image_data_temp_demo_button_pressed
};



class GUI_VideoShit : public GUI_Base
{
    private:
        int _temp;
        bool _button_state;
        

    public:
        GUI_VideoShit() :
            _temp(3),
            _button_state(false)
            {}

        void init() override;

        void renderPage();
        void tempUp();
        void tempDown();
        void buttonPressed();
        void buttonReleased();

};
