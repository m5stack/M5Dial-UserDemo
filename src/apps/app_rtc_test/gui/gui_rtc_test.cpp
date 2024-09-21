/**
 * @file gui_rtc_test.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "gui_rtc_test.h"


#define delay(ms) SDL_Delay(ms)



void GUI_RTC_Test::init()
{
    _canvas->fillScreen(_theme_color);

    /* Icon */
    _draw_top_icon();
    

    /* Quit button */
    _draw_quit_button();


    _canvas->pushSprite(0, 0);
}


void GUI_RTC_Test::renderPage(const uint8_t& hour, const uint8_t& minute, const uint8_t& second)
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
    snprintf(string_buffer, 24, "%02d:%02d:%02d", hour, minute, second);

    _canvas->setTextColor(_theme_color);

    _canvas->setTextSize(2);
    _canvas->drawCenterString(string_buffer, bubble.x, bubble.y - 24);
    _canvas->setTextSize(1);


    /* Quit button */
    _draw_quit_button();

    _canvas->pushSprite(0, 0);
}

