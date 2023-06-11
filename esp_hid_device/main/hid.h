#ifndef _HID_H_
#define _HID_H_

#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_gatt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"

#include "esp_hidd.h"
#include "esp_hid_gap.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

typedef struct {
    xTaskHandle task_hdl;
    esp_hidd_dev_t *hid_dev;
    uint8_t protocol_mode;
    uint8_t *buffer;
} local_param_t;

extern esp_hid_device_config_t ble_hid_config;
extern local_param_t s_ble_hid_param;
extern esp_hid_device_config_t bt_hid_config;
extern local_param_t s_bt_hid_param;
void ble_hidd_event_callback(void *handler_args, esp_event_base_t base, int32_t id, void *event_data);
void bt_hidd_event_callback(void *handler_args, esp_event_base_t base, int32_t id, void *event_data);

#endif