#include "inputs.hpp"
#include "joybusComms.hpp"
#include "keycode.h"
#include "keymap.hpp"
#include "logic.hpp"
#include "runtime_remapping.hpp"
#include "tusb.h"

#include "bsp/board.h"
#include "hardware/gpio.h"
#include "pico/bootrom.h"
#include "pico/multicore.h"
#include "pico/time.h"

#define REV1 1
#define REV2 2
#define REV2_2 2.2

#define REVISION REV2_2
#define WONKY false

#if REVISION == REV1
#define GC_DATA_PIN 0
#elif REVISION == REV2 && !WONKY
#define GC_DATA_PIN 0
#define GC_3V3_PIN 1
#elif REVISION == REV2 && WONKY
#define GC_DATA_PIN 1
#define GC_3V3_PIN 0
#elif REVISION == REV2_2
#define GC_DATA_PIN 28
#define GC_3V3_PIN 27
#endif

#define LED_PIN 25

#define NUMBER_OF_INPUTS 24

void joybus_loop();

CFG_TUSB_MEM_SECTION extern hid_keyboard_report_t usb_keyboard_report;

const uint32_t us = 125;

bool mode_selected = false;

RectangleInput rectangleInput;
GCReport gcReport;

int main() {
    board_init();

    // Clock at 125MHz
    set_sys_clock_khz(us * 1000, true);

    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

#if REVISION >= REV2
    gpio_init(GC_3V3_PIN);
    gpio_set_dir(GC_3V3_PIN, GPIO_IN);
    gpio_pull_down(GC_3V3_PIN);

    sleep_ms(200);

    if (!gpio_get(GC_3V3_PIN))
        reset_usb_boot(0, 0);
#endif

    initLogic(ParasolDashing::BAN, SlightSideB::BAN);

    KeyMapping *keymap = getKeymap();
    initInputs(keymap, NUMBER_OF_INPUTS);

    multicore_launch_core1(joybus_loop);

    tusb_init();

    while (1) {
        // Poll keyboard
        tuh_task();
        if (!mode_selected) {
            uint8_t key = findFirstPressedKey(&usb_keyboard_report);
            if (key != 0) {
                if (key == KC_ESC) {
                    sleep_ms(3000);
                    remap();
                }
                mode_selected = true;
            }
        }

        /* TODO: Shouldn't be doing this stuff on every iteration, but only when we
            actually get a report from the keyboard. */
        // Map keyboard inputs to rectangle button state.
        rectangleInput = getRectangleInput(&usb_keyboard_report);

        // Map rectangle button state to GC controller state.
        gcReport = makeReport(rectangleInput);
    }

    return 1;
}

void joybus_loop() {
    initComms(GC_DATA_PIN, us);

    while (1) {
        awaitPoll();
        wait2Us();
        respondToPoll(&gcReport);
    }
}
