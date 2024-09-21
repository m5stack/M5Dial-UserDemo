/**
 * @file gui_temp_demo.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "gui_temp_demo.h"


#define delay(ms) SDL_Delay(ms)


void GUI_VideoShit::init()
{
    _theme_color = 0x008CD6;

    _canvas->fillScreen(_theme_color);
    

    printf("%d\n", _temp);
    _canvas->pushImage(0, 50 - 10, 240, 110, _pic_temp_list[_temp]);

    if (_button_state)
        _canvas->pushImage(0, 160, 240, 82, _pic_button_list[0]);
    else
        _canvas->pushImage(0, 160, 240, 82, _pic_button_list[1]);

    /* Cover shit */
    _canvas->fillRect(0, 120, 10, 40, _theme_color);
    _canvas->fillRect(240 - 10, 120, 10, 40, _theme_color);



    _canvas->pushSprite(0, 0);
}


void GUI_VideoShit::renderPage()
{
    init();
}


void GUI_VideoShit::tempUp()
{
    _temp++;
    if (_temp > _pic_temp_list.size() - 1)
    {
        _temp = _pic_temp_list.size() - 1;
    }
    renderPage();
}


void GUI_VideoShit::tempDown()
{
    _temp--;
    if (_temp < 0)
    {
        _temp = 0;
    }
    renderPage();
}


void GUI_VideoShit::buttonPressed()
{
    _button_state = true;
    renderPage();
}


void GUI_VideoShit::buttonReleased()
{
    _button_state = false;
    renderPage();
}
