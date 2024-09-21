/**
 * @file gui_lcd_test.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-07-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "gui_lcd_test.h"



void GUI_LCD_TEST::init()
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
    _canvas->drawCenterString("Rotate Encoder", bubble.x, bubble.y - 55);
    _canvas->drawCenterString("To Change Color", bubble.x, bubble.y - 55 + 22);
    _canvas->drawCenterString("Touch Screen To", bubble.x, bubble.y + 15);
    _canvas->drawCenterString("Draw Points", bubble.x, bubble.y + 15 + 22);


    /* Quit button */
    _draw_quit_button();
    _canvas->pushSprite(0, 0);
}


void GUI_LCD_TEST::renderPage(const int& currentPageNum)
{
    printf("render page: %d\n", currentPageNum);

    /* Default pages */
    if (currentPageNum == 0)
    {
        GUI_LCD_TEST::init();
    }
    /* Test page */
    else if (currentPageNum == 6)
    {
        _canvas->fillScreen(TFT_WHITE);
        _canvas->fillCircle(_canvas->width() / 2, _canvas->height() / 2, 2, TFT_WHITE);
        _canvas->drawCircle(_canvas->width() / 2, _canvas->height() / 2, _canvas->width() / 2 - 1, TFT_GREEN);
        _canvas->drawCircle(_canvas->width() / 2, _canvas->height() / 2, _canvas->width() / 4, TFT_GREEN);
        _canvas->drawLine(0, _canvas->height() / 2, _canvas->width(), _canvas->height() / 2, TFT_GREEN);
        _canvas->drawLine(_canvas->width() / 2, 0, _canvas->width() / 2, _canvas->height(), TFT_GREEN);
    }
    /* Just fill background */
    else 
    {
        _canvas->fillScreen(_bg_color_list[currentPageNum]);
    }

    
    /* Render */
    _canvas->pushSprite(0, 0);
}


void GUI_LCD_TEST::goNextPage()
{
    _current_page_num++;
    if (_current_page_num > _max_page_num)
    {
        _current_page_num = 0;
    }
    renderPage(_current_page_num);
}


void GUI_LCD_TEST::goLastPage()
{
    _current_page_num--;
    if (_current_page_num < 0)
    {
        _current_page_num = _max_page_num;
    }
    renderPage(_current_page_num);
}


void GUI_LCD_TEST::renderTp(const int& tpX, const int& tpY)
{
    /* If in test page */
    if (_current_page_num == _max_page_num)
    {
        _canvas->setTextSize(0.7);
        _canvas->setTextColor(TFT_WHITE, TFT_BLACK);
        _canvas->setCursor(5, 120);
        _canvas->printf("%3d,%3d", tpX, tpY);
        _canvas->setTextSize(1);
    }
    /* Draw point */
    _canvas->fillCircle(tpX, tpY, 2, _tp_color_list[_current_page_num]);
    _canvas->pushSprite(0, 0);
}
