#include "pico/printf.h"
#include "pico/stdlib.h"

#include "slate.h"
#include "pins.h"
#include "init/init.h"


#define TEST

int main()
{
    stdio_init_all();
	sleep_ms(5000);
	printf("Code start\n");
	slate_t slate;
	init(&slate);
#ifdef TEST
    while (1)
    {
		printf("...\n");
		float voltage = adm1176_get_voltage(&slate.power_monitor);
		float current = adm1176_get_current(&slate.power_monitor);
		printf("Battery voltage: %f \n", voltage);
		printf("Battery current: %f \n", current);
    	sleep_ms(1000);
    }
#else
#endif

    while (1)
        ;
}
