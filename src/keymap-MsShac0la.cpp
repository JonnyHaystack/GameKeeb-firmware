//#include "pico/stdlib.h"
#include "inputs.hpp"
#include "keycode.h"

#include "persistence/functions.hpp"
#include "persistence/pages/runtime_remapping.hpp"

#include <stdlib.h>

const KeyMapping defaultKeymap[25] = {
    {&RectangleInput::left,    KC_A     },
    { &RectangleInput::right,  KC_D     },
    { &RectangleInput::down,   KC_S     },
    { &RectangleInput::up,     KC_W     },

    { &RectangleInput::mx,     KC_C     },
    { &RectangleInput::mx2,    KC_N     },
    { &RectangleInput::my,     KC_LCTL  },

    { &RectangleInput::start,  KC_ENT   },

    { &RectangleInput::cLeft,  KC_J     },
    { &RectangleInput::cRight, KC_L     },
    { &RectangleInput::cDown,  KC_K     },
    { &RectangleInput::cUp,    KC_I     },

    { &RectangleInput::a,      KC_U     },
    { &RectangleInput::b,      KC_O     },
    { &RectangleInput::x,      KC_SPC   },
    { &RectangleInput::y,      KC_0     },

    { &RectangleInput::z,      KC_H     },
    { &RectangleInput::l,      KC_LSHIFT},
    { &RectangleInput::r,      KC_SCLN  },

    { &RectangleInput::ls,     KC_G     },
    { &RectangleInput::ms,     KC_B     },

    { &RectangleInput::dLeft,  KC_2     },
    { &RectangleInput::dRight, KC_3     },
    { &RectangleInput::dDown,  KC_4     },
    { &RectangleInput::dUp,    KC_1     },
};

const KeyMapping remappedKeymap[25] = {
    {&RectangleInput::left,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.leftKey  },
    { &RectangleInput::right,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.rightKey },
    { &RectangleInput::down,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.downKey  },
    { &RectangleInput::up,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.upKey    },
    { &RectangleInput::mx,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.mxKey    },
    { &RectangleInput::my,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.myKey    },
    { &RectangleInput::start,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.startKey },
    { &RectangleInput::cLeft,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.cLeftKey },
    { &RectangleInput::cRight,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.cRightKey},
    { &RectangleInput::cDown,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.cDownKey },
    { &RectangleInput::cUp,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.cUpKey   },
    { &RectangleInput::a,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.aKey     },
    { &RectangleInput::b,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.bKey     },
    { &RectangleInput::x,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.xKey     },
    { &RectangleInput::y,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.yKey     },
    { &RectangleInput::z,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.zKey     },
    { &RectangleInput::l,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.lKey     },
    { &RectangleInput::r,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.rKey     },
    { &RectangleInput::ls,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.lsKey    },
    { &RectangleInput::ms,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.msKey    },
    { &RectangleInput::dLeft,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.dLeftKey },
    { &RectangleInput::dRight,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.dRightKey},
    { &RectangleInput::dDown,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.dDownKey },
    { &RectangleInput::dUp,
     Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.dUpKey   },
};

KeyMapping *getKeymap() {
    bool remapped = Persistence::isnt0xFF(
        Persistence::read<Persistence::Pages::RuntimeRemapping>()->keyRemapping.configured
    );

    return remapped ? (KeyMapping *)remappedKeymap : (KeyMapping *)defaultKeymap;
}
