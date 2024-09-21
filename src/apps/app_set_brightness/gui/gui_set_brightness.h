/**
 * @file gui_set_brightness.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../utilities/gui_base/gui_base.h"



class GUI_SetBrightness : public GUI_Base
{
    private:

    public:
        void init() override;
        void renderPage(uint8_t brightness);
        
};
