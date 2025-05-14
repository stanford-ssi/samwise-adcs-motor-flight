#include "init/init.h"
#include "pico/printf.h"

static bool init_gpio_pins(slate_t *slate){
    i2c_init(SAMWISE_POWER_MONITOR_I2C, 100 * 1000);
    gpio_set_function(SAMWISE_POWER_MONITOR_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SAMWISE_POWER_MONITOR_SCL_PIN, GPIO_FUNC_I2C);

	return true;
}

static adm1176_t power_monitor;

static bool init_drivers(slate_t *slate){

	power_monitor = adm1176_mk(SAMWISE_POWER_MONITOR_I2C, 
					ADM1176_I2C_ADDR,
					ADM1176_DEFAULT_SENSE_RESISTOR,
					ADM1176_DEFAULT_VOLTAGE_RANGE);

	slate->power_monitor = power_monitor;

	return true;
}

bool init(slate_t *slate) {
	printf("Initializing...\n");
    gpio_init(SAMWISE_WATCHDOG_FEED_PIN);
	ASSERT(init_gpio_pins(slate));
    gpio_set_dir(SAMWISE_WATCHDOG_FEED_PIN, GPIO_OUT);

	ASSERT(init_drivers(slate));

	return true;
}
