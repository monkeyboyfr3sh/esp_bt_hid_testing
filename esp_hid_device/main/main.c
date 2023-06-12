#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "io_led.h"

void app_main()
{
    io_led_init();

    // Main application loop
    while (1) {
        io_led_on(100);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/event_groups.h"
// #include "esp_system.h"
// #include "esp_log.h"
// #include "nvs_flash.h"

// #include "esp_hid_gap.h"
// #include "app_hid_shared.h"
// #include "media_hid.h"
// #include "device_input_hid.h"

// static const char *TAG = "HID_DEV_DEMO";

// void app_main(void)
// {
//     esp_err_t ret;

//     // Init flash
//     ret = nvs_flash_init();
//     if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
//         ESP_ERROR_CHECK(nvs_flash_erase());
//         ret = nvs_flash_init();
//     }
//     ESP_ERROR_CHECK( ret );

//     // Init GAP
//     ESP_ERROR_CHECK( esp_hid_gap_init(HID_DEV_MODE)) ;

//     // // Init media hid
//     // ESP_ERROR_CHECK( media_hid_init() );

//     // Init device input task
//     ESP_ERROR_CHECK( device_input_hid_init() );

// }
