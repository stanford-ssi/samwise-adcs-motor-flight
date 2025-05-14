#include neopixel.h

neopixel_t neopixel_mk(PIO pio, uint8_t r, uint8_t g, uint8_t b){
	return (neopixel_t){
		.pio = pio,
		.r = r,
		.g = g,
		.b = b,
	}
}

void neopixel_init();

