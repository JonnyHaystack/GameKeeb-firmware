#include "hardware/gpio.h"

#include "inputs.hpp"
#include "keycode.h"
#include "logic.hpp"

#include "joybusComms.hpp"

#include "bsp/board.h"
#include "tusb.h"

#define LED_PIN 25
#define USB_POWER_PIN 24

const uint32_t us = 125;

const uint8_t gcDataPin = 0;

uint8_t keyboard_addr = 1;


CFG_TUSB_MEM_SECTION static hid_keyboard_report_t usb_keyboard_report;

#define NUMBER_OF_INPUTS 20
const KeyMapping keymap[NUMBER_OF_INPUTS] = {
    {KC_U, &RectangleInput::start},
    {KC_5, &RectangleInput::right},
    {KC_4, &RectangleInput::down},
    {KC_3, &RectangleInput::left},
    {KC_Q, &RectangleInput::l},
    {KC_B, &RectangleInput::mx},
    {KC_SPACE, &RectangleInput::my},
    {KC_KP_1, &RectangleInput::cUp},
    {KC_UP, &RectangleInput::cLeft},
    {KC_RIGHT, &RectangleInput::a},
    {KC_DOWN, &RectangleInput::cDown},
    {KC_KP_0, &RectangleInput::cRight},
    {KC_KP_PLUS, &RectangleInput::up},
    {KC_KP_ASTERISK, &RectangleInput::ms},
    {KC_KP_9, &RectangleInput::z},
    {KC_NO, &RectangleInput::ls},
    {KC_KP_8, &RectangleInput::x},
    {KC_KP_SLASH, &RectangleInput::y},
    {KC_KP_7, &RectangleInput::b},
    {KC_NUMLOCK, &RectangleInput::r}
};

void tuh_hid_keyboard_mounted_cb(uint8_t dev_addr) {
  keyboard_addr = dev_addr;
  tuh_hid_keyboard_get_report(dev_addr, &usb_keyboard_report);
}

void tuh_hid_keyboard_unmounted_cb(uint8_t dev_addr) {
}

// invoked ISR context
void tuh_hid_keyboard_isr(uint8_t dev_addr, xfer_result_t event) {
  (void)dev_addr;
  (void)event;
}

int main() {
  board_init();

  // Clock at 125MHz
  set_sys_clock_khz(us * 1000, true);

  stdio_init_all();

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_put(LED_PIN, 1);

  gpio_init(USB_POWER_PIN);
  gpio_set_dir(USB_POWER_PIN, GPIO_IN);

  initLogic(ParasolDashing::BAN, SlightSideB::BAN);
  initInputs(keymap, NUMBER_OF_INPUTS);
  initComms(gcDataPin, us);

  tusb_init();

  GCReport gcReport;
  RectangleInput ri;

  while (1) {
    awaitPoll();

    tuh_task();

    if (tuh_hid_keyboard_is_mounted(keyboard_addr)) {
      if (!tuh_hid_keyboard_is_busy(keyboard_addr)) {
        tuh_hid_keyboard_get_report(keyboard_addr, &usb_keyboard_report);
        ri = getRectangleInput(&usb_keyboard_report);
        //tuh_hid_keyboard_get_report(keyboard_addr, &usb_keyboard_report);
      }
    }

    gcReport = makeReport(ri);
    respondToPoll(&gcReport);
  }

  return 1;
}
