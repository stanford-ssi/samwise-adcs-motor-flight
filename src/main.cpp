#include "pico/stdlib.h"
#include "pico/float.h"

#include "slate.h"
#include "pins.h"
#include "init/init.h"
#include "drivers/motor/motor.h"
#include "hardware/gpio.h"

#define TEST

slate_t slate;

bool timer_callback(struct repeating_timer *t) {

    float kp = 0.3f;

    for (int m = 1; m < 4; m++) {
        float diff = slate.motor_state[1].rpm_ - slate.motor_measured[1].rpm_;
        float du = kp*diff;

        slate.motor_state[m].speed_ += (int)round(du);
        slate.motor_state[m].speed_ &= 0b11111111111;
    }

    return true;
}

int main()
{
    stdio_init_all();
	sleep_ms(1000);
	init(&slate);

    for (int m = 1; m < 4; m++){
        motor_enable(&slate.motors[m]);
        slate.motor_state[m].enabled_ = 1;
    }

    int period_ms = 100;
    struct repeating_timer  timer;
    add_repeating_timer_ms(period_ms, timer_callback, NULL, &timer);

    slate.rx_package.target_rpm_[1] = 1500.f;
    slate.motor_state[1].rpm_ = 1500.f;
	
	sleep_ms(1000);

    char* rx_bytes = (char*) &slate.rx_package;
    int rx_count = 0;

	//motor_set_speed(&slate.motors[3], 1<<12);
#ifdef TEST
    while (1)
    {
        /*
        float v = adm1176_get_voltage(&slate.power_monitor);
        float c = adm1176_get_current(&slate.power_monitor);

        printf("Battery voltage: %f \n", v);
		printf("Battery current: %f \n", c);
        */

        
        if (uart_is_readable(uart1)) {
            char read = uart_getc(uart1);
            uart_putc(uart1, read);
            rx_bytes[rx_count] = read; 
            rx_count += 1;
            rx_count %= 20;
            //slate.motor_state[1].speed_ = 1<<shift;
        }

        for (int m = 1; m < 4; m++) {

            slate.motor_state[m].rpm_ = slate.rx_package.target_rpm_[m];
            if (slate.motor_state[m].enabled_) {
                // printf("Setting motor %d\n", m);
                int motor_speed = slate.motor_state[m].speed_;
                motor_set_speed(&slate.motors[m], motor_speed);
            }
        }
        /*
        
        uint8_t arb = motor_read_register(&slate.motors[1], 0x0);
        //printf("Motor 3 status bit: %x\n", arb);
        */
        printf("Motor speed at %f\n", slate.motor_measured[1].rpm_);
        sleep_ms(100);
    }
#else
#endif
	printf("Uh oh\n");

    while (1)
        ;
}
