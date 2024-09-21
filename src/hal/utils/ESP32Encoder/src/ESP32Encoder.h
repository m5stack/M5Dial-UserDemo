#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/portable.h>
#include <freertos/semphr.h>
#include <driver/gpio.h>
#include <driver/pcnt.h>
#define MAX_ESP32_ENCODERS PCNT_UNIT_MAX
#define _INT16_MAX 32766
#define _INT16_MIN -32766
#define ISR_CORE_USE_DEFAULT (0xffffffff)
#include "../../Button/Button.h"

enum encType
{
    single,
    half,
    full
};

enum puType
{
    UP,
    DOWN,
    NONE
};

class ESP32Encoder;

typedef void (*enc_isr_cb_t)(void*);

class ESP32Encoder
{
public:
    /**
     * @brief Construct a new ESP32Encoder object
     *
     * @param always_interrupt set to true to enable interrupt on every encoder pulse, otherwise false
     * @param enc_isr_cb callback executed on every encoder ISR, gets a pointer to
     * 	the ESP32Encoder instance as an argument, no effect if always_interrupt is
     * 	false
     */
    ESP32Encoder(bool always_interrupt = false, enc_isr_cb_t enc_isr_cb = nullptr, void* enc_isr_cb_data = nullptr);
    ~ESP32Encoder();
    void attachHalfQuad(int aPintNumber, int bPinNumber);
    void attachFullQuad(int aPintNumber, int bPinNumber);
    void attachSingleEdge(int aPintNumber, int bPinNumber);
    int64_t getCount();
    int64_t clearCount();
    int64_t pauseCount();
    int64_t resumeCount();
    void detach();
    [[deprecated("Replaced by detach")]] void detatch();
    bool isAttached() { return attached; }
    void setCount(int64_t value);
    void setFilter(uint16_t value);
    static ESP32Encoder* encoders[MAX_ESP32_ENCODERS];
    bool always_interrupt;
    gpio_num_t aPinNumber;
    gpio_num_t bPinNumber;
    pcnt_unit_t unit;
    int countsMode = 2;
    volatile int64_t count = 0;
    pcnt_config_t r_enc_config;
    static enum puType useInternalWeakPullResistors;
    static uint32_t isrServiceCpuCore;
    enc_isr_cb_t _enc_isr_cb;
    void* _enc_isr_cb_data;

private:
    static bool attachedInterrupt;
    void attach(int aPintNumber, int bPinNumber, enum encType et);
    int64_t getCountRaw();
    bool attached;
    bool direction;
    bool working;

public:
    bool wasMoved(bool updateDirection = false);
    int getDirection();
    inline void clear() { clearCount(); }
    inline int readCount() { return static_cast<int>(getCount()) / 2; }
    Button btn;

    /* Move callback */
    void* _user_data = nullptr;
    void (*_move_callback)(ESP32Encoder*, void*) = nullptr;
    inline void setMovedCallback(void (*moveCallback)(ESP32Encoder*, void*), void* userData)
    {
        _move_callback = moveCallback;
        _user_data = userData;
    }

};

// Added by Sloeber
#pragma once
