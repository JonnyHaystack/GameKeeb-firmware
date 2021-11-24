#ifndef RUNTIME_REMAPPING_HPP_9W0CSZJJ
#define RUNTIME_REMAPPING_HPP_9W0CSZJJ

#include <sys/types.h>

#include "tusb.h"

void remap(void);

uint8_t findPressed(hid_keyboard_report_t const *kbd_report);

#endif /* end of include guard: RUNTIME_REMAPPING_HPP_9W0CSZJJ */
