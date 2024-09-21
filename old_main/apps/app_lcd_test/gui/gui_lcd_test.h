/**
 * @file gui_lcd_test.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-07-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../utilities/gui_base/gui_base.h"



class GUI_LCD_TEST : public GUI_Base
{
    private:
        /* 0~6 */
        const uint8_t _max_page_num = 6;
        int _current_page_num;
        std::array<int, 7> _bg_color_list = {TFT_BLACK, TFT_RED, TFT_GREEN, TFT_BLUE, TFT_WHITE, TFT_BLACK, TFT_BLACK};
        std::array<int, 7> _tp_color_list = {TFT_BROWN, TFT_WHITE, TFT_BLUE, TFT_WHITE, TFT_BLUE, TFT_YELLOW, TFT_BLUE};
           

    public:
        GUI_LCD_TEST() :
            _current_page_num(0)
            {}

        void init() override;

        void renderPage(const int& currentPageNum);
        void goNextPage();
        void goLastPage();
        void renderTp(const int& tpX, const int& tpY);

};
