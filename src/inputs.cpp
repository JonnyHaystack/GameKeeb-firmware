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

    for (int button = 0; button < keymapLength_; ++button) {
        ri.*keymap_[button].buttonState = false;
    }

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
        for (uint8_t i = 0; i < 6; i++) {
            uint8_t keycode = kbd_report->keycode[i];
            if (keymap_[button].keycode == keycode) {
                ri.*keymap_[button].buttonState = true;
            }
        }
    }

    return ri;
}
