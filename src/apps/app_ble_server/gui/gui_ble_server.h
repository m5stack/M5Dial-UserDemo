/**
 * @file gui_ble_server.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../utilities/gui_base/gui_base.h"



class GUI_BLE_Server : public GUI_Base
{
    private:

    public:

        enum BLEStatus_t
        {
            disconnet = 0,
            connected,
        };

        void init() override;
        void renderPage(BLEStatus_t status, const std::string& name, const std::string& info);
        
};
