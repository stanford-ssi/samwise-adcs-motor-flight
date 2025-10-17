/**
 * @author  The ADCS Team :)
 * @date    2024-02-08
 *
 * This file defines the slate struct, a static struct which stores all data on
 * the satellite. At init time, a single instance of this struct gets statically
 * allocated, and it is referenced by all tasks and functions.
 *
 * Look up "blackboard pattern" for more info.
 */

#pragma once

#include "linalg.h"
#include "pico/types.h"
#include "drivers/adm1176/adm1176.h"
#include "drivers/watchdog/watchdog.h"
#include "drivers/motor/motor.h"
#include "util/uart_package.h"

using namespace linalg::aliases;
using namespace linalg;

typedef struct 
{
	watchdog_t watchdog;
	adm1176_t power_monitor;

	motor_t motors[4];
    motor_state_t motor_state[4];
    volatile motor_state_t  motor_measured[4];

    rx_package_t rx_package;
    tx_package_t tx_package;
} slate_t;

extern slate_t slate;
