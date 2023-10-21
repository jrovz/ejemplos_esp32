#ifndef TB6612FNG
#define TB6612FNG

#include "driver/gpio.h"

typedef struct {
    gpio_num_t in1;
    gpio_num_t in2;
    gpio_num_t pwm;
} DCMotor;

void dcmotor_init(DCMotor* motor);
esp_err_t dcmotor_set_speed(DCMotor* motor, uint8_t speed);
esp_err_t dcmotor_brake(DCMotor* motor);

#endif