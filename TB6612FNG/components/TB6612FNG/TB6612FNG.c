#include "TB6612FNG.h"
#include "driver/ledc"

void dcmotor_init(DCMotor* motor) {
    // Configurar pines como salidas y establecer niveles iniciales
    gpio_set_direction(motor->in1, GPIO_MODE_OUTPUT);
    gpio_set_direction(motor->in2, GPIO_MODE_OUTPUT);
    gpio_set_level(motor->in1, 0);
    gpio_set_level(motor->in2, 0);

    // Configurar el canal LEDC
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY,
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .channel = LEDC_CHANNEL,
        .duty = 0, // Iniciar con un ciclo de trabajo de 0
        .gpio_num = motor->pwm,
        .intr_type = LEDC_INTR_DISABLE,
        .speed_mode = LEDC_MODE,
        .timer_sel = LEDC_TIMER
    };
    ledc_channel_config(&ledc_channel);
    ledc_fade_func_install(0);
}

esp_err_t dcmotor_set_speed(DCMotor* motor, uint8_t speed) {
    if (speed > 255) {
        return ESP_ERR_INVALID_ARG;
    }

    // Configurar la dirección de los pines
    gpio_set_level(motor->in1, 1);
    gpio_set_level(motor->in2, 0);

    // Establecer el ciclo de trabajo del canal LEDC
    esp_err_t err = ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, speed);
    if (err != ESP_OK) {
        return err;
    }

    // Actualizar el ciclo de trabajo
    return ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

esp_err_t dcmotor_brake(DCMotor* motor) {
    // Configurar la dirección de los pines para frenar
    gpio_set_level(motor->in1, 1);
    gpio_set_level(motor->in2, 1);

    // Establecer el ciclo de trabajo del canal LEDC a 0
    esp_err_t err = ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0);
    if (err != ESP_OK) {
        return err;
    }

    // Actualizar el ciclo de trabajo
    return ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}
