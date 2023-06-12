#include "joystick.h"
#include "joystick_defs.h"

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "driver/adc.h"

esp_err_t joystick_init(void)
{
    const adc_bits_width_t adc_width = ADC_WIDTH_BIT_12;

    // Configure ADC
    adc1_config_width(adc_width);
    adc1_config_channel_atten(X_ADC_CHANNEL, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(Y_ADC_CHANNEL, ADC_ATTEN_DB_11);

    // Configure digital input
    gpio_pad_select_gpio(DIGITAL_INPUT);
    gpio_set_direction(DIGITAL_INPUT, GPIO_MODE_INPUT);
    gpio_set_pull_mode(DIGITAL_INPUT, GPIO_PULLUP_ONLY);

    return ESP_OK;
}

static int map_value(int value, int in_min, int in_max, int out_min, int out_max)
{

    // Perform mapping
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static void joysitck_remap_xy(int *x_value, int *y_value)
{
    // Map params
    const int in_min = 0;
    const int in_max = 0xfa0;
    const int out_min = -10;
    const int out_max = 10;
    const int x_off = 1;
    const int y_off = 1;

    // Now do the mapping
    *x_value = map_value(*x_value, in_min, in_max, out_min, out_max) + x_off;   
    *y_value = map_value(*y_value, in_min, in_max, out_min, out_max) + y_off;   
}

static esp_err_t get_joystick_xy_raw(int* x_adc_reading, int* y_adc_reading)
{
    const int num_samples = 64;
    int x_raw_reading = 0;
    int y_raw_reading = 0;

    // Perform ADC sampling
    for (int i = 0; i < num_samples; i++) {

        // Read ADC values for X and Y channels
        x_raw_reading += adc1_get_raw(X_ADC_CHANNEL);
        y_raw_reading += adc1_get_raw(Y_ADC_CHANNEL);
    }

    // Calculate average ADC readings
    *x_adc_reading = x_raw_reading / num_samples;
    *y_adc_reading = y_raw_reading / num_samples;

    return ESP_OK;
}

static int get_joystick_sw(void)
{
    return !gpio_get_level(DIGITAL_INPUT);
}

esp_err_t get_joystick(int * x_mapped, int * y_mapped, int * sw_state)
{
    // Check for NULL
    if ( (x_mapped==NULL) || (y_mapped==NULL) || (sw_state==NULL) ){
        return ESP_ERR_INVALID_ARG;
    }

    // Perform ADC sampling
    ESP_ERROR_CHECK( get_joystick_xy_raw(x_mapped, y_mapped) );

    // Perform mapping 
    joysitck_remap_xy(x_mapped, y_mapped);

    // Read digital input state
    *sw_state = get_joystick_sw();

    return ESP_OK;
}