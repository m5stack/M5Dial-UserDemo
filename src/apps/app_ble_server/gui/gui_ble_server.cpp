/**
 * @file gui_ble_server.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "gui_ble_server.h"


#define delay(ms) SDL_Delay(ms)


void GUI_BLE_Server::init()
{   
    // _canvas->fillScreen(_theme_color);
    _canvas->fillScreen(TFT_DARKGRAY);
    _canvas->fillSmoothCircle(120, 120, 120, _theme_color);

    /* Icon */
    _draw_top_icon();


    // renderPage(disconnet, "..", "..", "..");


    /* Quit button */
    _draw_quit_button();

    _canvas->drawCircle(120, 120, 120, TFT_DARKGRAY);
    _canvas->pushSprite(0, 0);
}


void GUI_BLE_Server::renderPage(BLEStatus_t status, const std::string& name, const std::string& info)
{
    // _canvas->fillScreen(_theme_color);
    _canvas->fillScreen(TFT_DARKGRAY);
    _canvas->fillSmoothCircle(120, 120, 120, _theme_color);

    
    /* Info */
    BasicObeject_t bubble;
    bubble.x = 120;
    bubble.y = 120;
    bubble.width = 240;
    bubble.height = 140;
    _canvas->fillSmoothRoundRect(bubble.x - bubble.width / 2, bubble.y - bubble.height / 2, bubble.width, bubble.height, 36, TFT_WHITE);

    _canvas->setTextColor(_theme_color);
    _canvas->drawCenterString("BLE SERVER", bubble.x, bubble.y - 65);

    // int line_width = 90;
    // _canvas->drawFastHLine(bubble.x - line_width / 2, bubble.y - 34, line_width, _theme_color);



    int label_infos_x = 30;

    _canvas->setFont(GUI_FONT_CN_SMALL);

    _canvas->setCursor(label_infos_x, bubble.y - 26);
    _canvas->printf("[Name]:    %s", name.c_str());

    _canvas->setCursor(label_infos_x, bubble.y - 6);
    // _canvas->printf("[UUID]:    %s", uuid.c_str());
    _canvas->printf("[UUID]:    0x180D");

    // _canvas->setFont(GUI_FONT_CN_BIG);




    if (status == disconnet)
    {
        _canvas->setCursor(label_infos_x, bubble.y + 14);

        // _canvas->printf("[Info]:    disconnect");

        _canvas->setTextColor(_theme_color);
        _canvas->printf("[Info]:");

        _canvas->setTextColor(TFT_ORANGE, TFT_WHITE);
        _canvas->printf("    disconnect");

    }



    else if (status == connected)
    {
        _canvas->setCursor(label_infos_x, bubble.y + 14);
        _canvas->printf("[Info]:");

        _canvas->setTextColor(TFT_DARKGREEN);
        _canvas->printf("    connected");


        _canvas->setTextColor(TFT_BLUE, TFT_WHITE);
        _canvas->setCursor(label_infos_x, bubble.y + 34);
        _canvas->printf("           %s", info.c_str());
    }





    _canvas->setFont(GUI_FONT_CN_BIG);


    /* Icon */
    _draw_top_icon();

    /* Quit button */
    _draw_quit_button();


    _canvas->drawCircle(120, 120, 120, TFT_DARKGRAY);
    _canvas->pushSprite(0, 0);
}
