//#include "pico/stdlib.h"
#include <stdlib.h>

#include "inputs.hpp"
#include "keycode.h"
#include "persistence/functions.hpp"
#include "persistence/pages/runtime_remapping.hpp"

const KeyMapping defaultKeymap[24] = {
    {&RectangleInput::left, KC_P4},
    {&RectangleInput::right, KC_P6},
    {&RectangleInput::down, KC_P5},
    {&RectangleInput::up, KC_P8},
    {&RectangleInput::mx, KC_P0},
    {&RectangleInput::my, KC_PPLS},
    {&RectangleInput::start, KC_5},
    {&RectangleInput::cLeft, KC_A},
    {&RectangleInput::cRight, KC_D},
    {&RectangleInput::cDown, KC_S},
    {&RectangleInput::cUp, KC_W},
    {&RectangleInput::a, KC_Q},
    {&RectangleInput::b, KC_R},
    {&RectangleInput::x, KC_T},
    {&RectangleInput::y, KC_SPC},
    {&RectangleInput::z, KC_3},
    {&RectangleInput::l, KC_PENT},
    {&RectangleInput::r, KC_E},
    {&RectangleInput::ls, KC_F},
    {&RectangleInput::ms, KC_G},
    {&RectangleInput::dLeft, KC_LEFT},
    {&RectangleInput::dRight, KC_RIGHT},
    {&RectangleInput::dDown, KC_DOWN},
    {&RectangleInput::dUp, KC_UP},
};

const KeyMapping remappedKeymap[24] = {
    { &RectangleInput::left, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.leftKey },
    { &RectangleInput::right, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.rightKey },
    { &RectangleInput::down, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.downKey },
    { &RectangleInput::up, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.upKey },
    { &RectangleInput::mx, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.mxKey },
    { &RectangleInput::my, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.myKey },
    { &RectangleInput::start, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.startKey },
    { &RectangleInput::cLeft, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.cLeftKey },
    { &RectangleInput::cRight, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.cRightKey },
    { &RectangleInput::cDown, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.cDownKey },
    { &RectangleInput::cUp, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.cUpKey },
    { &RectangleInput::a, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.aKey },
    { &RectangleInput::b, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.bKey },
    { &RectangleInput::x, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.xKey },
    { &RectangleInput::y, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.yKey },
    { &RectangleInput::z, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.zKey },
    { &RectangleInput::l, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.lKey },
    { &RectangleInput::r, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.rKey },
    { &RectangleInput::ls, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.lsKey },
    { &RectangleInput::ms, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.msKey },
    { &RectangleInput::dLeft, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.dLeftKey },
    { &RectangleInput::dRight, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.dRightKey },
    { &RectangleInput::dDown, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.dDownKey },
    { &RectangleInput::dUp, Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.dUpKey },
};

KeyMapping* getKeymap() {
  bool remapped = Persistence::isnt0xFF(
      Persistence::read<Persistence::Pages::RuntimeRemapping>()
          ->keyRemapping.configured);

  return remapped ? (KeyMapping*)remappedKeymap : (KeyMapping*)defaultKeymap;
}
