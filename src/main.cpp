#include "GamecubeConsole.hpp"
#include "inputs.hpp"
#include "keycode.h"
#include "keymap.hpp"
#include "logic.hpp"
#include "runtime_remapping.hpp"
#include "tusb.h"

#include "bsp/board.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "pico/bootrom.h"
#include "pico/multicore.h"
#include "pico/time.h"

#define REV1 10
#define REV2 20
#define REV2_2 22

#define REVISION REV2
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

bool mode_selected = false;

RectangleInput rectangleInput;
gc_report_t gcReport = default_gc_report;

int main() {
    board_init();

    // Clock at 130MHz
    set_sys_clock_khz(130'000, true);

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
        makeReport(rectangleInput, &gcReport);
    }

    return 1;
}

void joybus_loop() {
    GamecubeConsole *gc = new GamecubeConsole(GC_DATA_PIN, pio0);

    while (1) {
        gc->WaitForPoll();
        gc->SendReport(&gcReport);
    }
}
