/**
 * @file more_menu_render_callback.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once


/* Render setting */
#define MORE_MENU_COLOR_SELECTOR           (uint32_t)0xfa7000
#define MORE_MENU_COLOR_BG                  TFT_BLACK


struct MoreMenuRender_CB_t : public SMOOTH_MENU::SimpleMenuCallback_t
{
    private:
        LGFX_Sprite* _canvas;

        float approxSin(float x)
        {
            float t = x * 0.15915f;
            t = t - (int)t;
            if (t < 0.5)
                return (-16.0f * t * t) + (8.0f * t);
            else
                return (16.0f * t * t) - (16.0f * t) - (8.0f * t) + 8.0f;
        }
        

    public:
        inline void setCanvas(LGFX_Sprite* canvasPtr) { _canvas = canvasPtr; }

        /* Override render callback */
        void renderCallback(
            const std::vector<SMOOTH_MENU::Item_t*>& menuItemList,
            const SMOOTH_MENU::RenderAttribute_t& selector,
            const SMOOTH_MENU::RenderAttribute_t& camera
        ) override
        {
            _canvas->fillScreen(MORE_MENU_COLOR_BG);
            


            int menu_start_y_offset = 108;
            float menu_rounded_x_offset = 0;


            
            // /* Draw selector */
            // _canvas->fillSmoothRoundRect(
            //     selector.x,
            //     // selector.x + (menuItemList[selector.targetItem]->width - selector.width) / 2,
            //     menu_start_y_offset + (menuItemList[selector.targetItem]->height - selector.height) / 2,
            //     selector.width,
            //     selector.height,
            //     5,
            //     MORE_MENU_COLOR_SELECTOR
            // );
            


            /* Draw menu */
            _canvas->setFont(GUI_FONT_CN_BIG);
            uint8_t text_tag_color;
            
            for (int i = 0; i < menuItemList.size(); i++)
            {
                /* Draw menu label */
                if (i == 0)
                {
                    _canvas->setTextColor(MORE_MENU_COLOR_SELECTOR);
                    _canvas->drawCenterString("MORE", 120, menuItemList[0]->y - selector.y + 20);
                }


                /* Calculate item x offset */
                menu_rounded_x_offset = menuItemList[i]->y - selector.y;

                /* Calculate item text color */
                text_tag_color = 255 - std::abs(menu_rounded_x_offset) * 2;
                _canvas->setTextColor(lgfx::color565(text_tag_color, text_tag_color, text_tag_color));

                // menu_rounded_x_offset = 120 * std::sin((menu_rounded_x_offset / 120) + (3 * 3.14159f / 2)) + 120;
                menu_rounded_x_offset = 120 * approxSin((menu_rounded_x_offset / 120) + (3 * 3.14159f / 2)) + 120;
                // printf("%f\n", menu_rounded_x_offset);

                

                /* Draw tags */
                _canvas->setTextSize(menuItemList[i]->height / 24);
                _canvas->drawString(
                    menuItemList[i]->tag.c_str(),
                    menuItemList[i]->x + menu_rounded_x_offset,
                    // menuItemList[i]->x,
                    menuItemList[i]->y - selector.y + menu_start_y_offset
                );
            }




            /* Draw selector in difference stack */
            _canvas->fillSmoothRoundRectInDifference(
                selector.x,
                // selector.x + (menuItemList[selector.targetItem]->width - selector.width) / 2,
                menu_start_y_offset + (menuItemList[selector.targetItem]->height - selector.height) / 2,
                selector.width,
                selector.height,
                5,
                MORE_MENU_COLOR_SELECTOR
            );

    


            // /* Drwa camera */
            // _canvas->drawRect(camera.x, camera.y, camera.width, camera.height, TFT_GREENYELLOW);


            _canvas->pushSprite(0, 0);
        }
};