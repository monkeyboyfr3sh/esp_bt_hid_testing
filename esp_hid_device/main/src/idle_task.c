#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "io_led.h"

void idle_task(void *pvParameters)
{
    while(1)
    {
        io_led_on(100);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}