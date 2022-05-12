#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "pico/stdlib.h"

#include "inputs.hpp"

#include "gamecube_definitions.h"

enum class ParasolDashing { BAN, DONT_BAN };
enum class SlightSideB { BAN, DONT_BAN };

/* Pick whether to apply optional B0XX/F1 bans */
void initLogic(ParasolDashing parasolDashingConfig, SlightSideB slightSideBConfig);

/* Makes a B0XX/F1 report from the provided RectangleInput */
void makeReport(const RectangleInput &ri, gc_report_t *report);

#endif
