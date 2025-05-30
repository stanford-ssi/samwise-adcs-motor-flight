#include "motor.h"

#include "pico/printf.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

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

	gpio_init(motor.FAULT_pin_); // Sets function SIO
	gpio_set_dir(motor.FAULT_pin_, GPIO_IN);
	gpio_disable_pulls(motor.FAULT_pin_);

	pwm_set_wrap(slice_num, 1<<12);
	// SPI Driver
	gpio_init(motor.SCS_pin_);
    gpio_set_dir(motor.SCS_pin_, GPIO_OUT);
	gpio_pull_down(motor.SCS_pin_);
    gpio_put(motor.SCS_pin_, 1);

	return motor;
}

void motor_enable(motor_t* motor){
	// First take it out of sleep
	gpio_init(motor->SLEEP_pin_); // Sets function SIO
	gpio_set_dir(motor->SLEEP_pin_, GPIO_OUT);
	gpio_pull_up(motor->SLEEP_pin_);
	gpio_put(motor->SLEEP_pin_, 1);

	// duty_buf sets the pwm duty characteristics
	uint8_t reg_lock_buf[2] = { 0x3, 0b11};

    gpio_put(motor->SCS_pin_, 0);  // Select device
    spi_write_blocking(spi0, reg_lock_buf, 2);
    gpio_put(motor->SCS_pin_, 1);  // Deselect device

	pwm_set_enabled(motor->pwm_slice_, true);
}

void motor_disable(motor_t* motor) {
	pwm_set_enabled(motor->pwm_slice_, false);
	gpio_put(motor->SLEEP_pin_, 0);
}

void motor_set_speed(motor_t* motor, uint16_t speed) {
	pwm_set_gpio_level(motor->PWM_pin_, speed);
	pwm_set_enabled(motor->pwm_slice_, true);
}

uint8_t motor_read_register(motor_t* motor, uint8_t reg_addr) {
    uint8_t tx_buf[2];
    uint8_t rx_buf[2];

    // Construct the read command (MSB = 1 for read)
    tx_buf[0] = 0x8b;  // Read from register
    tx_buf[1] = 0x00;                      // Dummy byte
	
	printf("tx_buf: %x\n", tx_buf[0]);

    gpio_put(motor->SCS_pin_, 0);
    spi_write_read_blocking(spi0, tx_buf, rx_buf, 2);
    gpio_put(motor->SCS_pin_, 1);

    return rx_buf[1];  // Second byte contains the register value
}

void motor_reset_fault(motor_t* motor) {
	/*
    uint8_t buf[2] = { 0x4, 0b11 };

    gpio_put(motor->SCS_pin_, 0);  // Select device
    spi_write_blocking(spi0, buf, 2);
    gpio_put(motor->SCS_pin_, 1);  // Deselect device
	*/
    gpio_put(motor->SLEEP_pin_, 0);
	sleep_us(30);
    gpio_put(motor->SLEEP_pin_, 1);
}

void motor_buck_enable(motor_t* motor) {
    uint8_t buck_buf[2] = { 0x8, 0b00011010 };

    gpio_put(motor->SCS_pin_, 0);  // Select device
    spi_write_blocking(spi0, buck_buf, 2);
    gpio_put(motor->SCS_pin_, 1);  // Deselect device
}
