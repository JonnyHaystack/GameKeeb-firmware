#include <stdlib.h>
#include <sys/types.h>
#include <vector>

#include "inputs.hpp"
#include "tusb.h"

#include "persistence/functions.hpp"
#include "persistence/pages/runtime_remapping.hpp"

#define LED_PIN 25

CFG_TUSB_MEM_SECTION extern hid_keyboard_report_t usb_keyboard_report;

uint8_t lastPressed = 0;

void remap() {
  std::vector<uint8_t> keysPressedInOrder{};

  int led = 0;
  gpio_put(LED_PIN, led);

  while (keysPressedInOrder.size() != 24) {
    // Poll keyboard
    tuh_task();

    uint8_t pressedKey = findFirstPressedKey(&usb_keyboard_report);
    if (pressedKey > 0 && pressedKey != lastPressed) {
      keysPressedInOrder.push_back(pressedKey);
      led = !led;
      gpio_put(LED_PIN, led);
    }
    lastPressed = pressedKey;
  }

  gpio_put(LED_PIN, 1);

  Persistence::Pages::RuntimeRemapping remapping =
      Persistence::clone<Persistence::Pages::RuntimeRemapping>();

  remapping.keyRemapping.configured = 0;

  remapping.keyRemapping.leftKey = keysPressedInOrder[0];    // Left
  remapping.keyRemapping.rightKey = keysPressedInOrder[1];   // Right
  remapping.keyRemapping.downKey = keysPressedInOrder[2];    // Down
  remapping.keyRemapping.upKey = keysPressedInOrder[3];      // Up
  remapping.keyRemapping.mxKey = keysPressedInOrder[4];      // MX
  remapping.keyRemapping.myKey = keysPressedInOrder[5];      // MY
  remapping.keyRemapping.startKey = keysPressedInOrder[6];   // Start
  remapping.keyRemapping.cLeftKey = keysPressedInOrder[7];   // CLeft
  remapping.keyRemapping.cRightKey = keysPressedInOrder[8];  // CRight
  remapping.keyRemapping.cDownKey = keysPressedInOrder[9];   // CDown
  remapping.keyRemapping.cUpKey = keysPressedInOrder[10];    // CUp
  remapping.keyRemapping.aKey = keysPressedInOrder[11];      // A
  remapping.keyRemapping.bKey = keysPressedInOrder[12];      // B
  remapping.keyRemapping.xKey = keysPressedInOrder[13];      // X
  remapping.keyRemapping.yKey = keysPressedInOrder[14];      // Y
  remapping.keyRemapping.zKey = keysPressedInOrder[15];      // Z
  remapping.keyRemapping.lKey = keysPressedInOrder[16];      // L
  remapping.keyRemapping.rKey = keysPressedInOrder[17];      // R
  remapping.keyRemapping.lsKey = keysPressedInOrder[18];     // LS
  remapping.keyRemapping.msKey = keysPressedInOrder[19];     // MS
  remapping.keyRemapping.dLeftKey = keysPressedInOrder[20];  // D-Pad Left
  remapping.keyRemapping.dRightKey = keysPressedInOrder[21]; // D-Pad Right
  remapping.keyRemapping.dDownKey = keysPressedInOrder[22];  // D-Pad Down
  remapping.keyRemapping.dUpKey = keysPressedInOrder[23];    // D-Pad Up

  Persistence::commit(remapping);

  while (1) {
    led = !led;
    gpio_put(LED_PIN, led);
    sleep_ms(1000);
  }
}
