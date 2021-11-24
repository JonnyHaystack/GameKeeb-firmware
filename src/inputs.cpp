#include "bsp/board.h"
#include "inputs.hpp"
#include "tusb.h"

const KeyMapping *keymap_;
size_t keymapLength_;

void initInputs(const KeyMapping *keymap, size_t keymapLength) {
    keymap_ = keymap;
    keymapLength_ = keymapLength;
}

RectangleInput getRectangleInput(hid_keyboard_report_t const *kbd_report) {
    RectangleInput ri;

    // Clear all previous inputs.
    for (int button = 0; button < keymapLength_; ++button) {
        ri.*keymap_[button].buttonState = false;
    }

    // Loop through each button in keymap.
    for (int button = 0; button < keymapLength_; ++button) {
        // If button keycode >= E0 then the button is mapped to a modifier
        if (keymap_[button].keycode >= 0xE0) {
            // Create bitmask from the modifier keycode to check the
            // corresponding bit in the modifier byte
            uint8_t bitmask = 1 << (keymap_[button].keycode & 0x0F);
            if (kbd_report->modifier & bitmask) {
                ri.*keymap_[button].buttonState = true;
            }
            continue;
        }
        // If button is not mapped to modifier, loop through keycodes in
        // keyboard report to see if one of them matches the button's key
        // mapping.
        for (int i = 0; i < 6; i++) {
            uint8_t keycode = kbd_report->keycode[i];
            if (keycode > 0 && keymap_[button].keycode == keycode) {
                ri.*keymap_[button].buttonState = true;
            }
        }
    }

    return ri;
}

uint8_t findFirstPressedKey(hid_keyboard_report_t const *kbd_report) {
  // If a modifier is pressed, we'll just return the first pressed modifier that
  // we find and ignore the real keycodes.
  if (kbd_report->modifier > 0) {
    int i = 0;
    while (i < 8 && !(kbd_report->modifier & (1 << i))) {
      i++;
    }
    return 0xE0 + i;
  }

  // Loop through keycodes and return the first that is non-zero.
  for (int i = 0; i < 6; i++) {
    uint8_t keycode = kbd_report->keycode[i];
    if (keycode > 0) {
      return keycode;
    }
  }

  return 0;
}

