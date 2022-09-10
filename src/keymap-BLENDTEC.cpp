//#include "pico/stdlib.h"
#include "inputs.hpp"
#include "keycode.h"

#include "persistence/functions.hpp"
#include "persistence/pages/runtime_remapping.hpp"

#include <stdlib.h>

const KeyMapping defaultKeymap[24] = {
    {&RectangleInput::left,    KC_A        },
    { &RectangleInput::right,  KC_D        },
    { &RectangleInput::down,   KC_S        },
    { &RectangleInput::up,     KC_W        },

    { &RectangleInput::mx,     KC_LSFT     },
    { &RectangleInput::my,     KC_LALT     },

    { &RectangleInput::start,  KC_ENT      },

    { &RectangleInput::cLeft,  KC_P4       },
    { &RectangleInput::cRight, KC_P6       },
    { &RectangleInput::cDown,  KC_P2       },
    { &RectangleInput::cUp,    KC_P8       },

    { &RectangleInput::a,      KC_P5       },
    { &RectangleInput::b,      KC_P3       },
    { &RectangleInput::x,      KC_RIGHT    },
    { &RectangleInput::y,      KC_P7       },
    { &RectangleInput::z,      KC_P9       },

    { &RectangleInput::l,      KC_LCTL     },
    { &RectangleInput::r,      KC_P1       },

    { &RectangleInput::ls,     KC_CAPS     },
    { &RectangleInput::ms,     KC_TAB      },

    { &RectangleInput::dLeft,  KC_J},
    { &RectangleInput::dRight, KC_L},
    { &RectangleInput::dDown,  KC_K},
    { &RectangleInput::dUp,    KC_I},
};

const KeyMapping remappedKeymap[24] = {
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
