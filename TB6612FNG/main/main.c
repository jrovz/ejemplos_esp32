#include "TB6612FNG.h"

// Definiciones de pines GPIO para los motores
#define MOTOR1_IN1 GPIO_NUM_4
#define MOTOR1_IN2 GPIO_NUM_5
#define MOTOR1_PWM GPIO_NUM_18

#define MOTOR2_IN1 GPIO_NUM_19
#define MOTOR2_IN2 GPIO_NUM_21
#define MOTOR2_PWM GPIO_NUM_22

void app_main() {
    // Configurar pines para los motores
    DCMotor motor1 = {MOTOR1_IN1, MOTOR1_IN2, MOTOR1_PWM};
    DCMotor motor2 = {MOTOR2_IN1, MOTOR2_IN2, MOTOR2_PWM};

    // Inicializar motores
    dcmotor_init(&motor1);
    dcmotor_init(&motor2);

    // Controlar la velocidad de los motores PWM valores entre 0 - 255
    esp_err_t err1 = dcmotor_set_speed(&motor1, 150);
    esp_err_t err2 = dcmotor_set_speed(&motor2, 200);

    if (err1 != ESP_OK || err2 != ESP_OK) {
        // Manejo de errores
    }

    // Esperar durante 5 segundos
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    // Frenar los motores
    dcmotor_brake(&motor1);
    dcmotor_brake(&motor2);
}