#include "util/timer_util.h"

bool control_timer_callback(struct repeating_timer *t){ 
    float kp = 0.3f;

    for (int m = 1; m < 4; m++) {
        float diff = slate.motor_state[1].rpm_ - slate.motor_measured[1].rpm_;
        float du = kp*diff;

        slate.motor_state[m].speed_ += (int)round(du);
        slate.motor_state[m].speed_ &= 0b11111111111;
    }

    return true;

}

bool telem_timer_callback(struct repeating_timer *t) {
    char* tx_bytes = (char*) &slate.tx_package;
    for (int i = 0; i < sizeof(tx_package_t); i++){
        uart_putc(uart1, tx_bytes[i]);
    }

    return true;
}

