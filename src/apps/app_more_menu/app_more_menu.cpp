/**
 * @file app_more_menu.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_more_menu.h"
#include "../common_define.h"


using namespace MOONCAKE::USER_APP;


void MoreMenu::_create_menu()
{
    /* Create a menu to handle selector */
    _data.menu = new SMOOTH_MENU::Simple_Menu;
    _data.menu_render_cb = new MoreMenuRender_CB_t;
    _data.menu_render_cb->setCanvas(_data.hal->canvas);

    _data.menu->init(240, 240);
    _data.menu->setRenderCallback(_data.menu_render_cb);

    /* Set selector anim */
    auto cfg_selector = _data.menu->getSelector()->config();
    cfg_selector.animPath_x = LVGL::overshoot;
    cfg_selector.animPath_y = LVGL::overshoot;
    cfg_selector.animTime_x = 400;
    cfg_selector.animTime_y = 400;
    _data.menu->getSelector()->config(cfg_selector);

    /* Set menu loop mode */
    _data.menu->setMenuLoopMode(false);


    /* Add menu item tag */
    int text_width = 12;
    int text_height = 24;
    int text_size = 1;
    std::vector<std::string> tag_list = {
        "Quit",
        "Power Off",
        "LVGL Widgets",
        "LVGL Benchmark",
        "LVGL Stress",
        "???",
        ":):):):)",
        "This",
        "Is",
        "A",
        "Really",
        "Really",
        "Really",
        "Really",
        "Long",
        "List"
    };


    /* Push item into menu */
    for (int i = 0; i < tag_list.size(); i++)
    {
        _data.menu->getMenu()->addItem(
            tag_list[i].c_str(),
            24,
            10 + (text_height + 2) * text_size * i,
            text_width * text_size * tag_list[i].size(),
            text_height * text_size
        );
    }
}


void MoreMenu::_menu_loop()
{
    _data.menu->update(millis());
    _canvas_update();
    // delay(5);

    /* If scrolled */
    if (_data.hal->encoder.wasMoved(true))
    {
        // printf("%d\n", _data.hal->encoder.getPosition());
        if (_data.hal->encoder.getDirection() < 1)
            _data.menu->goNext();
        else 
            _data.menu->goLast();
    }

    /* If button pressed */
    if (!_data.hal->encoder.btn.read())
    {
        _data.menu->getSelector()->pressed();
        /* Hold until button release */
        while (!_data.hal->encoder.btn.read())
        {
            _data.menu->update(millis());
            _canvas_update();
        }

        _data.menu->getSelector()->released();
        /* Hold until anim finish */
        while (!_data.menu->getSelector()->isAnimFinished())
        {
            _data.menu->update(millis());
            _canvas_update();
        }

        /* App open callback */
        _item_selected_callback(_data.menu->getSelector()->getTargetItem());
    }
}


void MoreMenu::onSetup()
{
    setAppName("MoreMenu");
    setAllowBgRunning(false);

    /* Copy default value */
    MORE_MENU::Data_t default_data;
    _data = default_data;

    _data.hal = (HAL::HAL*)getUserData();
}


/* Life cycle */
void MoreMenu::onCreate()
{
    _log("onCreate");
    _create_menu();
}


void MoreMenu::onRunning()
{
    _menu_loop();

    // /* If touched */
    // if (_data.hal->tp.isTouched())
    // {
    //     _data.hal->tp.update();
    //     _log("%d %d", _data.hal->tp.getTouchPointBuffer().x, _data.hal->tp.getTouchPointBuffer().y);
    // }
}


void MoreMenu::onDestroy()
{
    _log("onDestroy");

    delete _data.menu;
    delete _data.menu_render_cb;
}
