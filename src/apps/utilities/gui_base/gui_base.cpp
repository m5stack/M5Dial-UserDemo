/**
 * @file gui_base.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-07-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "gui_base.h"


void GUI_Base::_draw_quit_button(const int& buttonColor)
{
    // int button_width = 4 * 14;
    // int button_height = 22;
    // int button_x = 120;
    // int button_y = 120 + 98;
    // _canvas->fillSmoothRoundRect(button_x - button_width / 2, button_y - button_height / 2, button_width, button_height, 10, buttonColor);
    // _canvas->fillTriangle(button_x - 10, button_y, button_x + 10, button_y, button_x, button_y + 16, buttonColor);
    // _canvas->setTextColor(_theme_color);
    // _canvas->drawCenterString("Quit", button_x, button_y - 12);

    _canvas->setTextColor(buttonColor);
    _canvas->drawCenterString("<", _canvas_half_width, 215);
}


void GUI_Base::_draw_banner(const std::string& label, int x, int y, const int& bannerColor)
{
    int banner_width = label.size() * 15;
    int banner_height = 26;
    _canvas->fillSmoothRoundRect(x - banner_width / 2, y - banner_height / 2, banner_width, banner_height, 10, bannerColor);
    _canvas->setTextColor(_theme_color);
    _canvas->drawCenterString(label.c_str(), x, y - 12);
}


void GUI_Base::_draw_top_banner(const std::string& label, const int& bannerColor)
{
    // _canvas->fillSmoothRoundRect(41, -20, 150, 58, 25, bannerColor);
    // _canvas->fillRect(0, 0, 240, 40, bannerColor);
    // _canvas->setTextColor(_theme_color);
    // _canvas->drawCenterString(label.c_str(), _canvas_half_width, 12);

    // _canvas->setTextColor(bannerColor);
    // _canvas->drawCenterString(label.c_str(), _canvas_half_width, 12);
}


void GUI_Base::_draw_top_icon()
{
    _icon->pushRotateZoom(_canvas, _canvas_half_width, 24, 0, 1, 1, TFT_BLACK);

}



void GUI_Base::init()
{
    // _canvas->fillScreen(_theme_color);
    _canvas->fillScreen(TFT_DARKGRAY);
    _canvas->fillSmoothCircle(120, 120, 120, _theme_color);

    /* Icon */
    _draw_top_icon();
    
    /* Quit button */
    _draw_quit_button();

    _canvas->drawCircle(120, 120, 120, TFT_DARKGRAY);
    _canvas->pushSprite(0, 0);
}
