#include "pico/printf.h"
#include "pico/stdlib.h"

#include "slate.h"
#include "pins.h"
#include "init/init.h"
#include "drivers/motor/motor.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"

#define TEST

int main()
{
    stdio_init_all();
	sleep_ms(3000);
	slate_t slate;
	init(&slate);

    for (int m = 1; m < 4; m++){
        motor_enable(&slate.motors[m]);
        slate.motor_state[m].enabled_ = 1;
    }
	
	sleep_ms(1000);

	//motor_set_speed(&slate.motors[3], 1<<12);
#ifdef TEST
    while (1)
    {
        float v = adm1176_get_voltage(&slate.power_monitor);
        float c = adm1176_get_current(&slate.power_monitor);

        printf("Battery voltage: %f \n", v);
		printf("Battery current: %f \n", c);

        if (uart_is_readable(uart1)) {
            char read = uart_getc(uart1);
            uart_putc(uart1, read);
            int shift = (int) read;
            shift = shift - 0x30 + 3;
            printf("%d", shift);
            slate.motor_state[1].speed_ = 1<<shift;
        }

        for (int m = 1; m < 4; m++) {
            if (slate.motor_state[m].enabled_) {
                printf("Setting motor %d\n", m);
                int motor_speed = slate.motor_state[m].speed_;
                motor_set_speed(&slate.motors[m], motor_speed);
            }
        }
        /*
        if (slate.motor_state[1].speed_ == 0) {
            slate.motor_state[1].speed_ = 1<<11;
        } else {
            slate.motor_state[1].speed_ = 0;
        }
        */
        uint8_t arb = motor_read_register(&slate.motors[1], 0x0);
        printf("Motor 3 status bit: %x\n", arb);
    }
#else
#endif
	printf("Uh oh\n");

    while (1)
        ;
}
