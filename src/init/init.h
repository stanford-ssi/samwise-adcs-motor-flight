#pragma once

#include "hardware/i2c.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"

#include "macros.h"
#include "pins.h"
#include "slate.h"

#include "drivers/adm1176/adm1176.h"
#include "drivers/watchdog/watchdog.h"
#include "drivers/motor/motor.h"

bool init(slate_t *slate);
