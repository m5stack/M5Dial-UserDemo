/**
 * @file launcher.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-07-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "launcher.h"
#include "../common_define.h"


using namespace MOONCAKE::USER_APP;


void Launcher::_menu_init()
{
    /* Create a menu to handle selector */
    _data.menu = new SMOOTH_MENU::Simple_Menu;
    _data.menu_render_cb = new LauncherRender_CB_t;
    _data.menu_render_cb->setCanvas(_data.hal->canvas);

    _data.menu->init(240, 240);
    _data.menu->setRenderCallback(_data.menu_render_cb);

    /* Set selector anim */
    auto cfg_selector = _data.menu->getSelector()->config();
    cfg_selector.animPath_x = LVGL::overshoot;
    cfg_selector.animPath_y = LVGL::overshoot;
    cfg_selector.animTime_x = 300;
    cfg_selector.animTime_y = 300;
    _data.menu->getSelector()->config(cfg_selector);

    /* Set menu looply */
    _data.menu->setMenuLoopMode(true);
    _data.menu->getMenu()->x = 0;
    _data.menu->getMenu()->y = 0;

    /* Push selector points into menu */
    int a = 120;
    int b = 120;
    int r = 60;
    int n = 10;
    int x;
    int y;
    for (int i = 0; i < n; i++)
    {
        x = a + r * std::cos(2 * 3.14 * i / n);
        y = b + r * std::sin(2 * 3.14 * i / n);
        _data.menu->getMenu()->addItem("", x, y, ICON_RADIUS, ICON_RADIUS);
    }
}


void Launcher::_icon_list_init()
{
    for (int i = 0; i < icon_list.size(); i++)
    {
        /* Set colors */
        icon_list[i].color = icon_color_list[i];

        /* Set tags */
        icon_list[i].tag_up = icon_tag_list[i * 2];
        icon_list[i].tag_down = icon_tag_list[i * 2 + 1];

        /* Push Icon pic into sprite */
        icon_sprite_list[i].createSprite(42, 42);
        icon_sprite_list[i].pushImage(0, 0, 42, 42, icon_pic_list[i]);
    }

    /* Icon position */
    int a = 120;
    int b = 120;
    int r = 190 / 2;
    int n = 10;
    int x;
    int y;
    for (int i = 0; i < icon_list.size(); i++)
    {
        x = a + r * std::cos(2 * 3.14 * i / n);
        y = b + r * std::sin(2 * 3.14 * i / n);

        icon_list[i].x = x;
        icon_list[i].y = y;
    }
}


void Launcher::_launcher_init()
{
    _menu_init();
    _icon_list_init();
}


void Launcher::_launcher_loop()
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

        // /* Hold until anim finish */
        // while (!_data.menu->getSelector()->isAnimFinished())
        // {
        //     _data.menu->update(millis());
        //     _canvas_update();
        // }

        /* App open callback */
        _app_open_callback(_data.menu->getSelector()->getTargetItem());
    }

    /* If touched */
    if (_data.hal->tp.isTouched())
    {
        _data.hal->tp.update();

        // printf("%d %d\n", _data.hal->tp.getTouchPointBuffer().x, _data.hal->tp.getTouchPointBuffer().y);
        // return;

        /* Check if in the center circle (r = 50) */
        int x = _data.hal->tp.getTouchPointBuffer().x - 120;
        int y = _data.hal->tp.getTouchPointBuffer().y - 120;
        if ((x * x + y * y) > (50 * 50))
        {
            // printf("no\n");
            return;
        }
        // printf("yes\n");

        /* Call button pressed callback */
        HAL::HAL::_encoder_button_pressed_callback(nullptr, _data.hal);


        if (_data.menu->getSelector()->isAnimFinished())
        {
            /* App open callback */
            _app_open_callback(_data.menu->getSelector()->getTargetItem());

            /* Wait until released */
            while (_data.hal->tp.isTouched())
            {
                _data.menu->update(millis());
                _canvas_update();
            }
        }
    }
}


void Launcher::_app_open_callback(uint8_t selectedNum)
{
    _log("selected %d", selectedNum);

    /* If not in icon list */
    if (selectedNum >= icon_list.size())
    {
        return;
    }


    /* Special color for app more menu */
    uint32_t theme_color = 0;
    if (selectedNum != 7)
        theme_color = icon_list[selectedNum].color;
    else
        theme_color = 0;


    /* Play app open anim */
    for (int i = 0; i < 10; i++)
    {
        _data.hal->canvas->fillSmoothCircle(icon_list[selectedNum].x, icon_list[selectedNum].y, i * 24, theme_color);
        _canvas_update();
    }

    

    // /* ----------------------- Simple test ----------------------- */
    // std::array<GUI_Base*, ICON_NUM> gui_list;
    // gui_list[0] = new GUI_Base;
    // gui_list[1] = new GUI_Base;
    // gui_list[2] = new GUI_Base;
    // gui_list[3] = new GUI_Base;
    // gui_list[4] = new GUI_Base;
    // gui_list[5] = new GUI_Base;
    // gui_list[6] = new GUI_Base;
    // gui_list[7] = new GUI_Base;

    // /* Open app */
    // gui_list[selectedNum]->setThemeColor(icon_list[selectedNum].color);
    // gui_list[selectedNum]->init(_data.hal->canvas, &icon_sprite_list[selectedNum]);
    // while (1)
    // {
    //     if (_data.hal->encoder.btn.pressed())
    //     {
    //         /* Hold until button release */
    //         while (!_data.hal->encoder.btn.read());
    //         break;
    //     }
    // }
    // /* ----------------------- Simple test ----------------------- */






    // /* ----------------------- Simple app test ----------------------- */
    // std::array<MOONCAKE::APP_BASE*, ICON_NUM> app_list;
    // app_list[0] = new MOONCAKE::USER_APP::LCD_Test;
    // app_list[1] = new MOONCAKE::USER_APP::RTC_Test;
    // app_list[2] = new MOONCAKE::USER_APP::RFID_Test;
    // app_list[3] = new MOONCAKE::USER_APP::Set_Brightness;
    // app_list[4] = new MOONCAKE::USER_APP::WiFi_Scan;
    // app_list[5] = new MOONCAKE::APP_BASE;
    // app_list[6] = new MOONCAKE::APP_BASE;
    // app_list[7] = new MOONCAKE::USER_APP::VideoShit;

    // if (app_list[selectedNum]->getGui() != nullptr)
    // {
    //     app_list[selectedNum]->getGui()->setThemeColor(icon_list[selectedNum].color);
    //     app_list[selectedNum]->getGui()->init(_data.hal->canvas, &icon_sprite_list[selectedNum]);

    //     _simple_app_manager(app_list[selectedNum]);
    // }

    // /* Free */
    // for (auto& i : app_list)
    // {
    //     delete i;
    // }
    // /* ----------------------- Simple app test ----------------------- */




    /* Memery leak check */
    size_t mem_before_open = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
    _log("free mem: %d", mem_before_open);



    MOONCAKE::APP_BASE* app_ptr = nullptr;

    /* Create app */
    switch (selectedNum)
    {
        case 0:
            app_ptr = new MOONCAKE::USER_APP::LCD_Test;
            break;
        case 1:
            app_ptr = new MOONCAKE::USER_APP::RTC_Test;
            break;
        case 2:
            app_ptr = new MOONCAKE::USER_APP::RFID_Test;
            break;
        case 3:
            app_ptr = new MOONCAKE::USER_APP::Set_Brightness;
            break;
        case 4:
            app_ptr = new MOONCAKE::USER_APP::WiFi_Scan;
            break;
        case 5:
            app_ptr = new MOONCAKE::USER_APP::BLE_Server;
            break;
        case 6:
            app_ptr = new MOONCAKE::USER_APP::VideoShit;
            break;
        case 7:
            app_ptr = new MOONCAKE::USER_APP::MoreMenu;
            break;
        default:
            break;
    };

    /* If app created */
    if (app_ptr != nullptr)
    {
        /* Init if gui module exsit */
        if (app_ptr->getGui() != nullptr)
        {
            app_ptr->getGui()->setThemeColor(icon_list[selectedNum].color);
            app_ptr->getGui()->init(_data.hal->canvas, &icon_sprite_list[selectedNum]);
        }

        /* Run app */
        _simple_app_manager(app_ptr);
        
        /* Free app */
        delete app_ptr;
    }



    /* Memery leak check */
    _log_mem();
    if (heap_caps_get_free_size(MALLOC_CAP_INTERNAL) < mem_before_open)
    {
        _log_e("memory leak: %d", mem_before_open - heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    }
    
    

    /* Play app close anim */
    for (int i = 10; i > 1; i--)
    {
        _data.menu->update(millis());
        _data.hal->canvas->fillSmoothCircle(icon_list[selectedNum].x, icon_list[selectedNum].y, i * 24, theme_color);
        _canvas_update();
    }
}


void Launcher::_simple_app_manager(MOONCAKE::APP_BASE* app)
{
    app->setUserData((void*)_data.hal);
    app->onSetup();
    app->onCreate();
    while (1)
    {
        app->onRunning();
        if (app->isGoingDestroy())
        {
            app->resetGoingDestroyFlag();
            app->onDestroy();
            break;
        }

        // if (_data.hal->encoder.btn.pressed())
        // {
        //     /* Hold until button release */
        //     while (!_data.hal->encoder.btn.read());
        //     break;
        // }
    }
}


Launcher::~Launcher()
{
    delete _data.menu;
    delete _data.menu_render_cb;
}


void Launcher::onSetup()
{
    setAppName("Launcher");
    setAllowBgRunning(false);

    /* Init with default value */
    LAUNCHER::Data_t default_data;
    _data = default_data;

    _data.hal = (HAL::HAL*)getUserData();
}


/* Life cycle */
void Launcher::onCreate()
{
    _log("onCreate");
    
    _launcher_init();
    _data.menu->getSelector()->reset(millis());
}


void Launcher::onRunning()
{
    _launcher_loop();
}

