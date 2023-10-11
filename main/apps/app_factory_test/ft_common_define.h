/**
 * @file ft_common_define.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#define delay(ms) vTaskDelay(pdMS_TO_TICKS(ms))
#define millis() (esp_timer_get_time() / 1000)

#define _log(fmt, args...) ESP_LOGI("ft", fmt, ##args)
#define _log_w(fmt, args...) ESP_LOGW("ft", fmt, ##args)
#define _log_e(fmt, args...) ESP_LOGE("ft", fmt, ##args)

#define _log_mem() _log("free mem: %d", heap_caps_get_free_size(MALLOC_CAP_INTERNAL))
#define _log_block() _log("free block: %d", heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL))

#define _canvas _data.hal->canvas
#define _canvas_update() _data.hal->canvas->pushSprite(0, 0)
