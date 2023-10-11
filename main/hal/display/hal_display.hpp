/**
 * @file hal_display.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
// #include <M5GFX.h>
// #include <lgfx/v1/panel/Panel_ST7789.hpp>

#define LGFX_USE_V1
#include <LovyanGFX.hpp>



#define LCD_MOSI_PIN 5
#define LCD_MISO_PIN -1
#define LCD_SCLK_PIN 6
#define LCD_DC_PIN   4
#define LCD_CS_PIN   7
#define LCD_RST_PIN  8
#define LCD_BUSY_PIN -1
#define LCD_BL_PIN   9


class LGFX_StampRing : public lgfx::LGFX_Device {
    lgfx::Panel_GC9A01 _panel_instance;
    lgfx::Bus_SPI _bus_instance;
    lgfx::Light_PWM _light_instance;

   public:
    LGFX_StampRing(void)
    {
        {
            auto cfg = _bus_instance.config();

            cfg.spi_host = SPI3_HOST;
            cfg.spi_mode = 0;
            cfg.freq_write = 80000000;
            cfg.freq_read = 16000000;
            cfg.spi_3wire = true;
            cfg.use_lock = true;
            cfg.dma_channel = SPI_DMA_CH_AUTO;
            cfg.pin_sclk = LCD_SCLK_PIN;
            cfg.pin_mosi = LCD_MOSI_PIN;
            cfg.pin_miso = LCD_MISO_PIN;
            cfg.pin_dc = LCD_DC_PIN;

            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }

        {
            auto cfg = _panel_instance.config();

            cfg.pin_cs = LCD_CS_PIN;
            cfg.pin_rst = LCD_RST_PIN;
            cfg.pin_busy = LCD_BUSY_PIN;

            cfg.panel_width = 240;
            cfg.panel_height = 240;
            cfg.offset_x = 0;
            cfg.offset_y = 0;
            cfg.offset_rotation = 0;
            cfg.dummy_read_pixel = 8;
            cfg.dummy_read_bits = 1;
            cfg.readable = true;
            cfg.invert = true;
            cfg.rgb_order = false;
            cfg.dlen_16bit = false;
            cfg.bus_shared = true;

            _panel_instance.config(cfg);
        }

        {
            auto cfg = _light_instance.config();

            cfg.pin_bl = LCD_BL_PIN;
            cfg.invert = false;
            cfg.freq = 44100;
            cfg.pwm_channel = 7;

            _light_instance.config(cfg);
            _panel_instance.setLight(&_light_instance);
        }

        // {
        //     // 要修改LCD 初始化的RST 延时时间
        //     auto cfg = _touch_instance.config();

        //     cfg.x_min = 0;
        //     cfg.x_max = LCD_HEIGHT;
        //     cfg.y_min = 0;
        //     cfg.y_max = LCD_WIDTH;
        //     cfg.pin_int = TOUCH_IRQ;
        //     cfg.pin_rst = TOUCH_RST;
        //     cfg.bus_shared = true;
        //     cfg.offset_rotation = 0;

        //     cfg.i2c_port = TOUCH_I2C_PORT;
        //     cfg.i2c_addr = TOUCH_I2C_ADDR;
        //     cfg.pin_sda = TOUCH_SDA;
        //     cfg.pin_scl = TOUCH_SCL;
        //     cfg.freq = 100000;

        //     _touch_instance.config(cfg);
        //     _panel_instance.setTouch(&_touch_instance);
        // }

        setPanel(&_panel_instance);
    }
};





// // #define LGFX_USE_V1
// // #include <LovyanGFX.hpp>

// // ESP32でLovyanGFXを独自設定で利用する場合の設定例

// /// 独自の設定を行うクラスを、LGFX_Deviceから派生して作成します。
// class LGFX_VAMeter : public lgfx::LGFX_Device
// {

// // 接続するパネルの型にあったインスタンスを用意します。
// lgfx::Panel_ST7789      _panel_instance;


// // パネルを接続するバスの種類にあったインスタンスを用意します。
//   lgfx::Bus_SPI       _bus_instance;   // SPIバスのインスタンス

// // バックライト制御が可能な場合はインスタンスを用意します。(必要なければ削除)
//   lgfx::Light_PWM     _light_instance;

// public:

//   // コンストラクタを作成し、ここで各種設定を行います。
//   // クラス名を変更した場合はコンストラクタも同じ名前を指定してください。
//   LGFX_VAMeter(void)
//   {
//     { // バス制御の設定を行います。
//       auto cfg = _bus_instance.config();    // バス設定用の構造体を取得します。

// // SPIバスの設定
//       cfg.spi_host = SPI2_HOST;     // 使用するSPIを選択  ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
//       // ※ ESP-IDFバージョンアップに伴い、VSPI_HOST , HSPI_HOSTの記述は非推奨になるため、エラーが出る場合は代わりにSPI2_HOST , SPI3_HOSTを使用してください。
//       cfg.spi_mode = 2;             // SPI通信モードを設定 (0 ~ 3)
//       cfg.freq_write = 40000000;    // 送信時のSPIクロック (最大80MHz, 80MHzを整数で割った値に丸められます)
//       cfg.freq_read  = 16000000;    // 受信時のSPIクロック
//       cfg.spi_3wire  = true;        // 受信をMOSIピンで行う場合はtrueを設定
//       cfg.use_lock   = true;        // トランザクションロックを使用する場合はtrueを設定
//       cfg.dma_channel = SPI_DMA_CH_AUTO; // 使用するDMAチャンネルを設定 (0=DMA不使用 / 1=1ch / 2=ch / SPI_DMA_CH_AUTO=自動設定)
//       // ※ ESP-IDFバージョンアップに伴い、DMAチャンネルはSPI_DMA_CH_AUTO(自動設定)が推奨になりました。1ch,2chの指定は非推奨になります。
//       cfg.pin_sclk = LCD_SCLK_PIN;            // SPIのSCLKピン番号を設定
//       cfg.pin_mosi = LCD_MOSI_PIN;            // SPIのMOSIピン番号を設定
//       cfg.pin_miso = -1;            // SPIのMISOピン番号を設定 (-1 = disable)
//       cfg.pin_dc   = LCD_DC_PIN;            // SPIのD/Cピン番号を設定  (-1 = disable)
//      // SDカードと共通のSPIバスを使う場合、MISOは省略せず必ず設定してください。
// //*/


//       _bus_instance.config(cfg);    // 設定値をバスに反映します。
//       _panel_instance.setBus(&_bus_instance);      // バスをパネルにセットします。
//     }

//     { // 表示パネル制御の設定を行います。
//       auto cfg = _panel_instance.config();    // 表示パネル設定用の構造体を取得します。

//       cfg.pin_cs           =    LCD_CS_PIN;  // CSが接続されているピン番号   (-1 = disable)
//       cfg.pin_rst          =    LCD_RST_PIN;  // RSTが接続されているピン番号  (-1 = disable)
//       cfg.pin_busy         =    -1;  // BUSYが接続されているピン番号 (-1 = disable)

//       // ※ 以下の設定値はパネル毎に一般的な初期値が設定されていますので、不明な項目はコメントアウトして試してみてください。

//       cfg.panel_width      =   240;  // 実際に表示可能な幅
//       cfg.panel_height     =   240;  // 実際に表示可能な高さ
//       cfg.offset_x         =     0;  // パネルのX方向オフセット量
//       cfg.offset_y         =     0;  // パネルのY方向オフセット量
//       cfg.offset_rotation  =     0;  // 回転方向の値のオフセット 0~7 (4~7は上下反転)
//       cfg.dummy_read_pixel =     8;  // ピクセル読出し前のダミーリードのビット数
//       cfg.dummy_read_bits  =     1;  // ピクセル以外のデータ読出し前のダミーリードのビット数
//       cfg.readable         =  true;  // データ読出しが可能な場合 trueに設定
//       cfg.invert           = true;  // パネルの明暗が反転してしまう場合 trueに設定
//       cfg.rgb_order        = false;  // パネルの赤と青が入れ替わってしまう場合 trueに設定
//       cfg.dlen_16bit       = false;  // 16bitパラレルやSPIでデータ長を16bit単位で送信するパネルの場合 trueに設定
//       cfg.bus_shared       =  true;  // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)

// // 以下はST7735やILI9163のようにピクセル数が可変のドライバで表示がずれる場合にのみ設定してください。
// //    cfg.memory_width     =   240;  // ドライバICがサポートしている最大の幅
// //    cfg.memory_height    =   320;  // ドライバICがサポートしている最大の高さ

//       _panel_instance.config(cfg);
//     }

// //*
//     { // バックライト制御の設定を行います。（必要なければ削除）
//       auto cfg = _light_instance.config();    // バックライト設定用の構造体を取得します。

//       cfg.pin_bl = LCD_BL_PIN;              // バックライトが接続されているピン番号
//       cfg.invert = false;           // バックライトの輝度を反転させる場合 true
//       cfg.freq   = 44100;           // バックライトのPWM周波数
//       cfg.pwm_channel = 7;          // 使用するPWMのチャンネル番号

//       _light_instance.config(cfg);
//       _panel_instance.setLight(&_light_instance);  // バックライトをパネルにセットします。
//     }
// //*/

//     setPanel(&_panel_instance); // 使用するパネルをセットします。
//   }
// };

