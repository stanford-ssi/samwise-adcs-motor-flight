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
	printf("Code start\n");
	sleep_ms(3000);
	slate_t slate;
	init(&slate);

	printf("Enable motors 1 to 3\n");
	motor_enable(&slate.motors[2]);
	
	uint8_t arb_2 = motor_read_register(&slate.motors[2], 0x5);

	sleep_ms(1000);
	printf("Motor 3 arbitrary: %x\n", arb_2);

	printf("Sleeping!\n");
	sleep_ms(1000);

	//motor_set_speed(&slate.motors[3], 1<<12);
#ifdef TEST
    while (1)
    {
		uint8_t fault_3 = motor_read_register(&slate.motors[2], 0x0);
		uint8_t arb = motor_read_register(&slate.motors[2], 0x5);
		uint8_t reg_4 = motor_write_register(&slate.motors[2], 0x4, 0x82);
		printf("---\n");
		printf("Motor 3 fault bit: %x\n", fault_3);
		printf("Motor 3 arbitrary: %x\n", arb);
		printf("Motor 3 reg_4 bit: %x\n", reg_4);

		/*
		printf("Motor half speed\n"); 
		motor_set_speed(&slate.motors[3], 1<<11);


		printf("Motor at no speed\n");
		motor_set_speed(&slate.motors[3], 0);
		sleep_ms(1000);
		*/

		//uint8_t fault = motor_read_register(&slate.motors[1], 0x5);
		//uint8_t fault_2 = motor_read_register(&slate.motors[2], 0x5);

		//printf("Motor 1 fault bit: %x\n", fault);
		//printf("Motor 2 fault bit: %x\n", fault_2);
	
		//printf("Battery voltage: %x-%x \n", buf[0], buf[1]);
		/*
		printf("...\n");
		float voltage = adm1176_get_voltage(&slate.power_monitor);
	//float current = adm1176_get_current(&slate.power_monitor);
		//uint8_t buf[2];
    	//i2c_read_blocking(i2c0, 0x94 , buf, 2, false);
	
		printf("Battery voltage: %f \n", voltage);
		//printf("Battery voltage: %x-%x \n", buf[0], buf[1]);
		//printf("Battery current: %f \n", current);

		printf("Motor half speed\n"); 
		motor_set_speed(&slate.motors[3], 1<<11);
    	sleep_ms(500);

		printf("Motor at no speed\n");
		motor_set_speed(&slate.motors[3], 0);
		sleep_ms(500);

	//motor_reset_fault(&slate.motors[3]);
		*/
    }
#else
#endif
	printf("Uh oh\n");

    while (1)
        ;
}
