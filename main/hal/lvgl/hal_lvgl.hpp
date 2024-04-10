/**
 * @file hal_lvgl.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-06-28
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <lvgl.h>
#include "porting/lv_port_disp.h"
#include "porting/lv_port_indev.h"

class LVGL_PORT
{
private:
public:
    LVGL_PORT() = default;
    ~LVGL_PORT() = default;

    inline void init(LGFX_Device* display, ESP32Encoder* encoder, FT3267::TP_FT3267* tp, void* displayBuffer)
    {
        // printf("1\n");

        lv_init();

        // printf("2\n");

        lv_port_disp_init(display, displayBuffer);

        // printf("3\n");

        lv_port_indev_init(encoder, tp);

        // /* Clear screen */
        // lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0), LV_PART_MAIN);
        // lv_obj_invalidate(lv_scr_act());
        // lv_timer_handler();
    }

    // inline void deInit()
    // {
    //     lv_mem_deinit();
    // }
};
