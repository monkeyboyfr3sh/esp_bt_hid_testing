#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include "esp_err.h"

esp_err_t joystick_init(void);
esp_err_t get_joystick(int * x_mapped, int * y_mapped, int * sw_state);

#endif