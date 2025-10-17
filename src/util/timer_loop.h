#pragma once

#include "hardware/timer.h"

void init_timer(int period_ms);
bool timer_callback(struct repeating_timer *t);
