/**
 * @file gui_wifi_scan.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../utilities/gui_base/gui_base.h"



class GUI_WiFi_Scan : public GUI_Base
{
    private:

    public:
        void init() override;
        void renderPage(int menuY_offet, const std::string& menu);
        
};
