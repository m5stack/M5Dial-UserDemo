/**
 * @file gui_base.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-07-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <stdint.h>
#include <LovyanGFX.hpp>


struct BasicObeject_t
{
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
};


/**
 * @brief Base class for app gui
 * 
 */
class GUI_Base
{
    protected:
        LGFX_Sprite* _canvas;
        LGFX_Sprite* _icon;
        uint32_t _theme_color;

        int _canvas_half_width;
        int _canvas_half_height;
    
    public:
        GUI_Base() :
            _canvas(nullptr),
            _theme_color(0xFFFFFF)
            {}
        virtual ~GUI_Base() = default;

        /* Basic settings */
        inline void setCanvas(LGFX_Sprite* canvas, LGFX_Sprite* icon)
        {
            _canvas = canvas;
            _icon = icon;
            _canvas_half_width = _canvas->width() / 2;
            _canvas_half_height = _canvas->height() / 2;
        }
        inline void setThemeColor(const uint32_t& color) { _theme_color = color; }
        
        /* Entry for override */
        virtual void init();
        void init(LGFX_Sprite* canvas, LGFX_Sprite* icon)
        {
            setCanvas(canvas, icon);
            init();
        }


    /* Common drawing api */
    protected:
        void _draw_quit_button(const int& buttonColor = TFT_WHITE);
        void _draw_banner(const std::string& label, int x, int y, const int& bannerColor = TFT_WHITE);
        void _draw_top_banner(const std::string& label, const int& bannerColor = TFT_WHITE);
        void _draw_top_icon();
};
