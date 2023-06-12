#include "io_led.h"
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <driver/gpio.h>
#include <driver/timer.h>

// Create the timer
esp_timer_handle_t io_timer;

#define MS_TO_US(X) X*1000

// Timer ISR callback function
static void timer_isr(void* arg)
{
    gpio_set_level(IO_LED_PIN, 0);
    esp_timer_stop(io_timer);    
}

esp_err_t io_led_init(void)
{
    // Init the io led
    gpio_pad_select_gpio(IO_LED_PIN);
    gpio_set_direction(IO_LED_PIN, GPIO_MODE_OUTPUT);

    // Configure timer parameters
    esp_timer_create_args_t timer_args = {
        .callback = timer_isr,    // ISR callback function
        .arg = NULL,              // Argument to pass to the ISR callback
        .dispatch_method = ESP_TIMER_TASK,  // Run ISR callback in a task
        .name = "io_led"        // Timer name (for debugging)
    };

    // Create the timer
    return esp_timer_create(&timer_args, &io_timer);
}

esp_err_t io_led_on(int on_period_ms)
{
    // Turn on led
    gpio_set_level(IO_LED_PIN, 1);
    // Start the timer
    return esp_timer_start_periodic(io_timer, MS_TO_US(on_period_ms));    
}