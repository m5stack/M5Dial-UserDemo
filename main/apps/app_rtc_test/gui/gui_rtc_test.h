/**
 * @file gui_rtc_test.h
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



class GUI_RTC_Test : public GUI_Base
{
    private:

    public:
        void init() override;
        void renderPage(const uint8_t& hour, const uint8_t& minute, const uint8_t& second);
        
};
