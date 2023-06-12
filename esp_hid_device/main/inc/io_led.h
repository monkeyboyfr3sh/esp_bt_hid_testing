#ifndef _IO_LED_H_
#define _IO_LED_H_

#include "esp_err.h"

#define IO_LED_PIN    GPIO_NUM_2

esp_err_t io_led_init(void);
esp_err_t io_led_on(int on_period_ms);

#endif