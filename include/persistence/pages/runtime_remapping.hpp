#ifndef PERSISTENCE_PAGES__RUNTIME_REMAPPING_HPP
#define PERSISTENCE_PAGES__RUNTIME_REMAPPING_HPP

#include "pico/stdlib.h"
#include "persistence/page_indexes.hpp"

namespace Persistence {
namespace Pages {

struct RuntimeRemapping {
    static const int index = (int) PageIndexes::RUNTIME_REMAPPING;

    struct __attribute__((packed)) KeyRemapping {
        uint8_t configured;

        uint8_t startKey;
        uint8_t rightKey;
        uint8_t downKey;
        uint8_t leftKey;
        uint8_t lKey;
        uint8_t mxKey;
        uint8_t myKey;
        uint8_t cUpKey;
        uint8_t cLeftKey;
        uint8_t aKey;
        uint8_t cDownKey;
        uint8_t cRightKey;
        uint8_t upKey;
        uint8_t msKey;
        uint8_t zKey;
        uint8_t lsKey;
        uint8_t xKey;
        uint8_t yKey;
        uint8_t bKey;
        uint8_t rKey;
        uint8_t dUpKey;
        uint8_t dLeftKey;
        uint8_t dDownKey;
        uint8_t dRightKey;
    } keyRemapping;
    
};

}
}

#endif
