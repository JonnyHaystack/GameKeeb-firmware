#include "hardware/gpio.h"

#include "inputs.hpp"
#include "keycode.h"
#include "logic.hpp"

#include "joybusComms.hpp"

#include "bsp/board.h"
#include "tusb.h"

#define LED_PIN 25

#define MAX_REPORT  4

#define NUMBER_OF_INPUTS 20

static uint8_t const keycode2ascii[128][2] =  { HID_KEYCODE_TO_ASCII };

const uint32_t us = 125;

const uint8_t gcDataPin = 0;

CFG_TUSB_MEM_SECTION extern hid_keyboard_report_t usb_keyboard_report;

static void process_kbd_report(hid_keyboard_report_t const *report);
static void process_mouse_report(hid_mouse_report_t const * report);
static void process_generic_report(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len);

const KeyMapping keymap[NUMBER_OF_INPUTS] = {
    {&RectangleInput::l, KC_Q},
    {&RectangleInput::left, KC_3},
    {&RectangleInput::down, KC_4},
    {&RectangleInput::right, KC_5},
    {&RectangleInput::mx, KC_B},
    {&RectangleInput::my, KC_SPACE},
    {&RectangleInput::start, KC_U},
    {&RectangleInput::cLeft, KC_UP},
    {&RectangleInput::cRight, KC_KP_0},
    {&RectangleInput::cDown, KC_DOWN},
    {&RectangleInput::cUp, KC_KP_1},
    {&RectangleInput::a, KC_RIGHT},
    {&RectangleInput::b, KC_KP_7},
    {&RectangleInput::x, KC_KP_8},
    {&RectangleInput::z, KC_KP_9},
    {&RectangleInput::up, KC_KP_PLUS},
    {&RectangleInput::r, KC_NUMLOCK},
    {&RectangleInput::y, KC_KP_SLASH},
    {&RectangleInput::ls, KC_NO},
    {&RectangleInput::ms, KC_KP_ASTERISK},
};

int main() {
  board_init();

  // Clock at 125MHz
  set_sys_clock_khz(us * 1000, true);

  stdio_init_all();

  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_put(LED_PIN, 1);

  initLogic(ParasolDashing::BAN, SlightSideB::BAN);
  initInputs(keymap, NUMBER_OF_INPUTS);
  initComms(gcDataPin, us);

  tusb_init();

  GCReport gcReport;
  RectangleInput ri;

  while (1) {
    awaitPoll();

    // Poll keyboard
    tuh_task();

    ri = getRectangleInput(&usb_keyboard_report);

    gcReport = makeReport(ri);
    respondToPoll(&gcReport);
  }

  return 1;
}
