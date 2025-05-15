#include "motor.h"

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

motor_t motor_init(int FAULT_pin, 
					int SLEEP_pin, 
					int DRVOFF_pin,
					int SCS_pin,
					int BRAKE_pin,
					int PWM_pin,
					int FGOUT_pin){

	gpio_set_function(PWM_pin, GPIO_FUNC_PWM);
	int slice_num = pwm_gpio_to_slice_num(PWM_pin);

	motor_t motor = (motor_t) {
		.FAULT_pin_ = FAULT_pin,
		.SLEEP_pin_ = SLEEP_pin,
		.DRVOFF_pin_ = DRVOFF_pin,
		.SCS_pin_ = SCS_pin,
		.BRAKE_pin_ = BRAKE_pin,
		.PWM_pin_ = PWM_pin,
		.FGOUT_pin_ = FGOUT_pin,
		.pwm_slice_ = slice_num, 
		.set_speed_ = 0,
	};

	gpio_init(SLEEP_pin); // Sets function SIO
	pwm_set_wrap(slice_num, 1<<12);

	motor_enable(&motor);

	return motor;
}

void motor_enable(motor_t* motor){
	gpio_put(motor->SLEEP_pin_, 1);
	pwm_set_enabled(motor->pwm_slice_, true);
}

void motor_disable(motor_t* motor) {
	pwm_set_enabled(motor->pwm_slice_, false);
	gpio_put(motor->SLEEP_pin_, 0);
}

void motor_set_speed(motor_t* motor, uint16_t speed) {
	pwm_set_gpio_level(motor->PWM_pin_, speed);
}
