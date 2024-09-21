/**
 * @file gui_rfid_test.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "gui_rfid_test.h"
#include <inttypes.h>


#define delay(ms) SDL_Delay(ms)


void GUI_RFID_Test::init()
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
    
    _canvas->setTextColor(_theme_color);
    _canvas->drawCenterString("RFID TEST", bubble.x, bubble.y - 55);
    _canvas->drawCenterString("Place Your RFID", bubble.x, bubble.y - 12);
    _canvas->drawCenterString("Card Above Screen", bubble.x, bubble.y + 14);
    _canvas->drawCenterString("To Read", bubble.x, bubble.y + 14 + 26);


    /* Quit button */
    _draw_quit_button();


    _canvas->pushSprite(0, 0);
}


void GUI_RFID_Test::renderPage(const uint64_t& sn)
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
    
    char string_buffer[24];
    snprintf(string_buffer, 24, "SN: %" PRIu64 "", sn);

    _canvas->setTextColor(_theme_color);
    _canvas->drawCenterString("TAG SCANNED", bubble.x, bubble.y - 55);
    _canvas->drawCenterString(string_buffer, bubble.x, bubble.y - 12);


    /* Quit button */
    _draw_quit_button();


    _canvas->drawCircle(120, 120, 120, TFT_DARKGRAY);
    _canvas->pushSprite(0, 0);
}
