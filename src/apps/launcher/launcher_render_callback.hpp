/**
 * @file launcher_render_callback.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-07-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "launcher_icons/launcher_icons.h"
#include <iostream>
#include <array>


/* Render setting */
#define THEME_COLOR_FG              (uint32_t)0xfa7000
// #define THEME_COLOR_BG              (uint32_t)0x424242
#define THEME_COLOR_BG              TFT_BLACK
#define SELECTOR_COLOR              (uint32_t)0xF3E9D2
#define SELECTOR_RADIUS             5
#define ICON_RADIUS                 22
#define ICON_SELECTED_R_OFFSET      3
#define ICON_TAG_COLOR              SELECTOR_COLOR
#define ICON_TAG_UP_OFFSET          -24
#define ICON_TAG_DOWN_OFFSET        0

#define ICON_NUM                    8


/* Strucut to hold icon value */
struct Icon_t
{
    std::string tag_up;
    std::string tag_down;
    void* icon_pic;
    uint32_t color;
    int x;
    int y;
};

/* Icon list */
static std::array<Icon_t, ICON_NUM> icon_list;
/* Icon color */
static std::array<uint32_t, ICON_NUM> icon_color_list = {
    0xFD5C4C,
    0x577EFF,
    0x03A964,
    0x1AA198,
    0xEB8429,
    0x04A279,
    0x008CD6,
    0x5D7BA2
    // 0x000000
};
/* Icon tag */
static std::array<std::string, ICON_NUM * 2> icon_tag_list = {
    "LCD", "TEST",
    "RTC", "TIME",
    "RFID", "TEST",
    "BRIGHTNESS", "SET",
    "WIFI", "SCAN",
    "BLE", "SERVER",
    "TEMP CTRL", "DEMO",
    "MORE", ""
};
/* Icon pic */
static std::array<const uint16_t*, ICON_NUM> icon_pic_list = {
    image_data_icon_lcd,
    image_data_icon_rtc,
    image_data_icon_rfid,
    image_data_icon_brigntness,
    image_data_icon_wifi,
    image_data_icon_ble,
    image_data_icon_temp,
    image_data_icon_more
};
/* Sprite to render icon with transparency */
static LGFX_Sprite icon_sprite_list[ICON_NUM];




struct LauncherRender_CB_t : public SMOOTH_MENU::SimpleMenuCallback_t
{
    private:
        LGFX_Sprite* _canvas;

    public:
        // LauncherRender_CB_t() = default;
        // ~LauncherRender_CB_t() = default;

        inline void setCanvas(LGFX_Sprite* canvasPtr) { _canvas = canvasPtr; }

        /* Override render callback */
        void renderCallback(
            const std::vector<SMOOTH_MENU::Item_t*>& menuItemList,
            const SMOOTH_MENU::RenderAttribute_t& selector,
            const SMOOTH_MENU::RenderAttribute_t& camera
        ) override
        {
            /* Clear screen */
            _canvas->fillScreen(THEME_COLOR_BG);

            /* Draw selector */
            _canvas->fillSmoothCircle(selector.x, selector.y, SELECTOR_RADIUS, SELECTOR_COLOR);
            // printf("%d %d\n", selector.x, selector.y);
            // printf("%d %d\n", menuItemList[selector.targetItem]->x, menuItemList[selector.targetItem]->y);


            /* Draw icon that moves with menu item */
            int icon_r = 190;
            int x;
            int y;
            for (int i = 0; i < icon_list.size(); i++)
            {
                /* Calculate position */
                x = (menuItemList[i]->x - 120) * icon_r / 120 + 120;
                y = (menuItemList[i]->y - 120) * icon_r / 120 + 120;

                if (i == selector.targetItem)
                {
                    _canvas->fillSmoothCircle(x, y, selector.width + ICON_SELECTED_R_OFFSET, icon_list[i].color);
                    icon_sprite_list[i].pushRotateZoom(_canvas, x, y, 0, 1.1, 1.1, TFT_BLACK);
                }
                else
                {
                    _canvas->fillSmoothCircle(x, y, ICON_RADIUS, icon_list[i].color);
                    icon_sprite_list[i].pushRotateZoom(_canvas, x, y, 0, 1, 1, TFT_BLACK);
                }
            }


            /* Draw Icon tag */
            /* Get Icon offset position */
            int new_r = 20;
            int icon_tag_x = (selector.x - 120) * new_r / 120 + 120;
            int icon_tag_y = (selector.y - 120) * new_r / 120 + 120;

            /* If pointing a icon */
            if (selector.targetItem < icon_list.size())
            {
                _canvas->setFont(GUI_FONT_CN_BIG);
                _canvas->setTextColor(ICON_TAG_COLOR);

                /* Darw tag with offset */
                _canvas->drawCenterString(
                    icon_list[selector.targetItem].tag_up.c_str(),
                    icon_tag_x,
                    icon_tag_y + ICON_TAG_UP_OFFSET
                );
                _canvas->drawCenterString(
                    icon_list[selector.targetItem].tag_down.c_str(),
                    icon_tag_x,
                    icon_tag_y + ICON_TAG_DOWN_OFFSET
                );
            }
            else 
            {
                _canvas->drawCenterString(
                    "-. -",
                    icon_tag_x,
                    icon_tag_y + ICON_TAG_UP_OFFSET
                );
            }


            // _canvas->fillScreen(TFT_BLACK);

            // _canvas->pushSprite(0, 0);
        }
};



