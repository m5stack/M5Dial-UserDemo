/**
 * @file gui_wifi_scan.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "gui_wifi_scan.h"


#define delay(ms) SDL_Delay(ms)


void GUI_WiFi_Scan::init()
{   
    // _canvas->fillScreen(_theme_color);
    _canvas->fillScreen(TFT_DARKGRAY);
    _canvas->fillSmoothCircle(120, 120, 120, _theme_color);

    /* Icon */
    _draw_top_icon();

    /* Info */
    BasicObeject_t bubble;
    bubble.x = 120;
    bubble.y = 120;
    bubble.width = 240;
    bubble.height = 140;
    _canvas->fillSmoothRoundRect(bubble.x - bubble.width / 2, bubble.y - bubble.height / 2, bubble.width, bubble.height, 36, TFT_WHITE);

    _canvas->setTextColor(_theme_color);
    _canvas->drawCenterString("WIFI SCAN", bubble.x, bubble.y - 65);
    _canvas->drawCenterString("Scanning...", bubble.x, bubble.y - 12);


    /* Quit button */
    _draw_quit_button();

    _canvas->drawCircle(120, 120, 120, TFT_DARKGRAY);
    _canvas->pushSprite(0, 0);
}


void GUI_WiFi_Scan::renderPage(int menuY_offet, const std::string& menu)
{
    _canvas->fillScreen(_theme_color);

    
    /* Info */
    BasicObeject_t bubble;
    bubble.x = 120;
    bubble.y = 120;
    bubble.width = 240;
    bubble.height = 140;
    _canvas->fillSmoothRoundRect(bubble.x - bubble.width / 2, bubble.y - bubble.height / 2, bubble.width, bubble.height, 36, TFT_WHITE);
    


    _canvas->setTextColor(_theme_color);
    _canvas->drawCenterString("WIFI LIST", bubble.x, bubble.y - 65 + menuY_offet);
    
    int line_width = 90;
    _canvas->drawFastHLine(bubble.x - line_width / 2, bubble.y - 34 + 0 + menuY_offet, line_width, _theme_color);
    // _canvas->drawFastHLine(bubble.x - line_width / 2, bubble.y - 40 + 1 + menuY_offet, line_width, _theme_color);
    
    
    _canvas->setFont(GUI_FONT_CN_SMALL);
    _canvas->setCursor(0, bubble.y - 20 + menuY_offet);
    _canvas->printf("%s", menu.c_str());
    _canvas->setFont(GUI_FONT_CN_BIG);




    /* Icon */
    _draw_top_icon();

    /* Quit button */
    _draw_quit_button();

    _canvas->pushSprite(0, 0);
}
