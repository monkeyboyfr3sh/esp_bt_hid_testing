set(srcs    "main.c"
            "src/esp_hid_gap.c"
            "src/device_input_hid.c"
            "src/app_hid_shared.c"
            "src/media_hid.c"
            "src/joystick.c"
            "src/io_led.c"
            "src/idle_task.c"
            )
set(include_dirs "." "./inc/")

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "${include_dirs}"
                       REQUIRES esp_hid)
