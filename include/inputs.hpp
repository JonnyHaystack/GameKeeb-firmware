#ifndef INPUTS_HPP
#define INPUTS_HPP

#include "pico/stdlib.h"
#include "tusb.h"

struct RectangleInput {
  bool a;
  bool b;
  bool x;
  bool y;
  bool z;
  bool l;
  bool r;
  bool ls;
  bool ms;
  bool mx;
  bool my;
  bool start;
  bool left;
  bool right;
  bool up;
  bool down;
  bool cLeft;
  bool cRight;
  bool cUp;
  bool cDown;
};

struct KeyMapping {
  bool RectangleInput::*buttonState;
  uint8_t keycode;
};

/* Initializes the keymap */
void initInputs(const KeyMapping *keymap, size_t keymapLength);

/* Read keycodes from keyboard report and provide the corresponding
 * RectangleInput */
RectangleInput getRectangleInput(hid_keyboard_report_t const *p_new_report);

#endif
