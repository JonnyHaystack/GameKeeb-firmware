#include "hardware/gpio.h"

#include "bsp/board.h"
#include "tusb.h"

#include "joybusComms.hpp"

#include "inputs.hpp"
#include "keycode.h"
#include "keymap.hpp"
#include "logic.hpp"
#include "runtime_remapping.hpp"

#define LED_PIN 25

#define NUMBER_OF_INPUTS 24

CFG_TUSB_MEM_SECTION extern hid_keyboard_report_t usb_keyboard_report;

const uint32_t us = 125;

const uint8_t gcDataPin = 0;

bool keyboard_mounted = false;

int main() {
  board_init();

  // Clock at 125MHz
  set_sys_clock_khz(us * 1000, true);

  stdio_init_all();

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_put(LED_PIN, 1);

  initLogic(ParasolDashing::BAN, SlightSideB::BAN);

  KeyMapping *keymap = getKeymap();
  initInputs(keymap, NUMBER_OF_INPUTS);

  initComms(gcDataPin, us);

  tusb_init();

  GCReport gcReport;
  RectangleInput ri;

  while (1) {
    awaitPoll();

    // Poll keyboard
    tuh_task();
    if (!keyboard_mounted && usb_keyboard_report.keycode[0] != 0 ) {
        keyboard_mounted = true;
        if (findFirstPressedKey(&usb_keyboard_report) == KC_ESC) {
            sleep_ms(3000);
            remap();
        }
    }

    ri = getRectangleInput(&usb_keyboard_report);

    gcReport = makeReport(ri);
    respondToPoll(&gcReport);
  }

  return 1;
}
