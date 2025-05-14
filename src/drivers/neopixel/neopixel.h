#pragma once

#include "hardware/pio.h"

#define NEOPIXEL_GPIO 39

typedef struct {
	PIO pio,
	uint8_t r,
	uint8_t g,
	uint8_t b,
} neopixel_t;

neopixel_t* neopixel_init();
