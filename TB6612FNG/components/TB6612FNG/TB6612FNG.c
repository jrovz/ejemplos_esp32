#include "TB6612FNG.h"

void dcmotor_init(DCMotor* motor) {
    gpio_set_direction(motor->in1, GPIO_MODE_OUTPUT);
    gpio_set_direction(motor->in2, GPIO_MODE_OUTPUT);
    gpio_set_direction(motor->pwm, GPIO_MODE_OUTPUT);
    gpio_set_level(motor->in1, 0);
    gpio_set_level(motor->in2, 0);
    gpio_set_level(motor->pwm, 0);
}

esp_err_t dcmotor_set_speed(DCMotor* motor, uint8_t speed) {
    if (speed > 255) {
        return ESP_ERR_INVALID_ARG;
    }

    if (gpio_set_level(motor->in1, 1) != ESP_OK) {
        return ESP_FAIL;
    }
    if (gpio_set_level(motor->in2, 0) != ESP_OK) {
        return ESP_FAIL;
    }
    if (gpio_set_level(motor->pwm, 1) != ESP_OK) {
        return ESP_FAIL;
    }

    if (ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, speed) != ESP_OK) {
        return ESP_FAIL;
    }
    if (ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0) != ESP_OK) {
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t dcmotor_brake(DCMotor* motor) {
    if (gpio_set_level(motor->in1, 1) != ESP_OK) {
        return ESP_FAIL;
    }
    if (gpio_set_level(motor->in2, 1) != ESP_OK) {
        return ESP_FAIL;
    }
    if (gpio_set_level(motor->pwm, 0) != ESP_OK) {
        return ESP_FAIL;
    }

    if (ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0) != ESP_OK) {
        return ESP_FAIL;
    }
    if (ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0) != ESP_OK) {
        return ESP_FAIL;
    }

    return ESP_OK;
}