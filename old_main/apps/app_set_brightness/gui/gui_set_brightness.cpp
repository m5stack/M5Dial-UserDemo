/**
 * @file gui_set_brightness.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "gui_set_brightness.h"


#define delay(ms) SDL_Delay(ms)



void GUI_SetBrightness::init()
{
}


void GUI_SetBrightness::renderPage(uint8_t brightness)
{
    _canvas->fillScreen(_theme_color);

    /* Icon */
    _draw_top_icon();


    /* Info */
    BasicObeject_t bubble;
    bubble.x = 120;
    bubble.y = 120;
    bubble.width = 240;
    bubble.height = 140;
    _canvas->fillSmoothRoundRect(bubble.x - bubble.width / 2, bubble.y - bubble.height / 2, bubble.width, bubble.height, 36, TFT_WHITE);


    


    char string_buffer[24];
    snprintf(string_buffer, 24, "%d", brightness);


    _canvas->setTextColor(_theme_color);
    _canvas->setTextSize(3);
    _canvas->drawCenterString(string_buffer, bubble.x, bubble.y - 56);
    _canvas->setTextSize(1);
    _canvas->drawCenterString("BRIGHTNESS", bubble.x, bubble.y + 26);
    

    
    

    /* Quit button */
    _draw_quit_button();

    _canvas->pushSprite(0, 0);
}
