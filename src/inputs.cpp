#include "bsp/board.h"
#include "inputs.hpp"
#include "tusb.h"

const KeyMapping *keymap_;
size_t keymapLength_;

void initInputs(const KeyMapping *keymap, size_t keymapLength) {
    keymap_ = keymap;
    keymapLength_ = keymapLength;
}

RectangleInput getRectangleInput(hid_keyboard_report_t const *p_new_report) {
    RectangleInput ri;

    for (int button = 0; button < keymapLength_; ++button) {
        ri.*keymap_[button].buttonState = false;
    }

    for (uint8_t i = 0; i < 6; i++) {
        uint8_t keycode = p_new_report->keycode[i];
        // If keycode is non-zero
        if (keycode) {
            for (int button = 0; button < keymapLength_; ++button) {
                if (keymap_[button].keycode == keycode) {
                    ri.*keymap_[button].buttonState = true;
                }
            }
        }
    }

    // Key to controller state translation
    //for (int pinNo = 0; pinNo < keymapLength_; ++pinNo) {
        //ri.*keymap_[pinNo].buttonState = key_pressed;
    //}

    return ri;
}
