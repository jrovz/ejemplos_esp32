/*
    Control de 2 motores DC +9V, mediante integrado L293D.
*/
/*
#include <stdio.h>
#include <stdbool.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/ledc.h"
#include <ultrasonic.h>
#include <esp_err.h>

// definiciones para el HC-SR04: puertos y distancia maxima
#define MAX_DISTANCE_CM 500 // 5m max

#define TRIGGER_GPIO 5
#define ECHO_GPIO 18

// definiciones para las salidas al L293D
#define M1O1 12
#define M1O2 13
#define M2O1 34
#define M2O2 35

int dutyM1 = 0;
int dutyM2 = 0;

float distance;

uint8_t M1O1_level = 0;
uint8_t M2O1_level = 0;
uint8_t M1O2_level = 0;
uint8_t M2O2_level = 0;

esp_err_t set_direction(void);
esp_err_t set_pwm_adelante(void);
esp_err_t set_pwm_duty(void);
esp_err_t init_motors(void);
esp_err_t turn_right(void);
esp_err_t turn_left(void);
esp_err_t backwards(void);
void ultrasonic_test();

void app_main(void)
{   
    xTaskCreate(ultrasonic_test, "ultrasonic_test", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    init_motors();
    set_pwm_adelante();
    set_direction();
}

// Funcion que habilita puertos 33 y 25 para PWM
esp_err_t set_pwm_adelante(void)
{

    // configuracion del canal del motor 1
    ledc_channel_config_t ChConfig_motor1 = {0};
    ChConfig_motor1.gpio_num = 33;
    ChConfig_motor1.speed_mode = LEDC_HIGH_SPEED_MODE;
    ChConfig_motor1.channel = LEDC_CHANNEL_0;
    ChConfig_motor1.intr_type = LEDC_INTR_DISABLE;
    ChConfig_motor1.timer_sel = LEDC_TIMER_0;
    ChConfig_motor1.duty = 0;

    // configuracion del canal del motor 2
    ledc_channel_config_t ChConfig_motor2 = {0};
    ChConfig_motor1.gpio_num = 25;
    ChConfig_motor1.speed_mode = LEDC_HIGH_SPEED_MODE;
    ChConfig_motor1.channel = LEDC_CHANNEL_1;
    ChConfig_motor1.intr_type = LEDC_INTR_DISABLE;
    ChConfig_motor1.timer_sel = LEDC_TIMER_1;
    ChConfig_motor1.duty = 0;

    ledc_channel_config(&ChConfig_motor1);
    ledc_channel_config(&ChConfig_motor2);

    // configuracion del timer para el PWM
    ledc_timer_config_t timerConfig = {0};
    timerConfig.speed_mode = LEDC_HIGH_SPEED_MODE;
    timerConfig.duty_resolution = LEDC_TIMER_10_BIT;
    timerConfig.timer_num = LEDC_TIMER_0;
    timerConfig.freq_hz = 20000;

    ledc_timer_config(&timerConfig);

    return ESP_OK;
}

esp_err_t set_pwm_duty(void)
{

    // set duty para cada canal disponible
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, dutyM1);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, dutyM2);

    // actualiza el duty
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
    return ESP_OK;
}

esp_err_t init_motors(void)
{
    gpio_reset_pin(M2O1);
    gpio_reset_pin(M2O2);
    gpio_set_direction(M2O1, GPIO_MODE_DEF_OUTPUT);
    gpio_set_direction(M2O2, GPIO_MODE_DEF_OUTPUT);

    gpio_reset_pin(M1O1);
    gpio_reset_pin(M1O2);
    gpio_set_direction(M1O1, GPIO_MODE_DEF_OUTPUT);
    gpio_set_direction(M1O2, GPIO_MODE_DEF_OUTPUT);
    return ESP_OK;
}

esp_err_t set_direction(void)
{
    
    if (distance > 30)
    {
        dutyM1 = 820;
        dutyM1 = 820;
        M1O1_level = 1;
        M1O2_level = 0;
        M2O1_level = 1;
        M2O2_level = 0;
    }
    if (distance < 10)
    {
        dutyM1 = 820;
        dutyM1 = 410;
        M1O1_level = 1;
        M1O2_level = 0;
        M2O1_level = 1;
        M2O2_level = 0;
    }
    if (distance < 5)
    {
        vTaskDelay(pdMsToTick(500));
        dutyM1 = 0;
        dutyM1 = 0;
        M2O1_level = 0;
        M2O2_level = 0;
        M1O1_level = 0;
        M1O2_level = 0;
    }

    set_pwm_duty();
    gpio_set_level(M1O1, M1O1_level);
    gpio_set_level(M1O2, M1O2_level);
    gpio_set_level(M2O1, M2O1_level);
    gpio_set_level(M2O2, M2O2_level);
    return ESP_OK;
}

void ultrasonic_test(void *pvParameters)
{
    ultrasonic_sensor_t sensor = {
        .trigger_pin = TRIGGER_GPIO,
        .echo_pin = ECHO_GPIO};

    ultrasonic_init(&sensor);

    while (true)
    {
        esp_err_t res = ultrasonic_measure(&sensor, MAX_DISTANCE_CM, &distance);
        if (res != ESP_OK)
        {
            printf("Error %d: ", res);
            switch (res)
            {
            case ESP_ERR_ULTRASONIC_PING:
                printf("Cannot ping (device is in invalid state)\n");
                break;
            case ESP_ERR_ULTRASONIC_PING_TIMEOUT:
                printf("Ping timeout (no device found)\n");
                break;
            case ESP_ERR_ULTRASONIC_ECHO_TIMEOUT:
                printf("Echo timeout (i.e. distance too big)\n");
                break;
            default:
                printf("%s\n", esp_err_to_name(res));
            }
        }
        else
            distance = distance * 100;
        printf("Distance: %0.04f cm\n", distance);

        vTaskDelay(pdMsToTick(500));
    }
}
*/
/*
#include <stdio.h>
#include <stdbool.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/ledc.h"
#include <ultrasonic.h>
#include <esp_err.h>

// Definiciones para el HC-SR04: pines y distancia máxima
#define MAX_DISTANCE_CM 500 // 5m máx.

#define TRIGGER_GPIO 5
#define ECHO_GPIO 18

// Definiciones para las salidas al L293D
#define M1O1 12
#define M1O2 13
#define M2O1 34
#define M2O2 35

int dutyM1 = 0;
int dutyM2 = 0;

float distance;

uint8_t M1O1_level = 0;
uint8_t M2O1_level = 0;
uint8_t M1O2_level = 0;
uint8_t M2O2_level = 0;

esp_err_t set_direction(void);
esp_err_t set_pwm_adelante(void);
esp_err_t set_pwm_duty(void);
esp_err_t init_motors(void);
esp_err_t turn_right(void);
esp_err_t turn_left(void);
esp_err_t backwards(void);
void ultrasonic_test();

void app_main(void)
{
    init_motors();
    set_pwm_adelante();
    set_direction();

    xTaskCreate(ultrasonic_test, "ultrasonic_test", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}

// Función que habilita los pines 33 y 25 para PWM
esp_err_t set_pwm_adelante(void)
{
    // Configuración del canal del motor 1
    ledc_channel_config_t ChConfig_motor1 = {
        .gpio_num = 33,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0
    };

    // Configuración del canal del motor 2
    ledc_channel_config_t ChConfig_motor2 = {
        .gpio_num = 25,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0
    };

    ledc_channel_config(&ChConfig_motor1);
    ledc_channel_config(&ChConfig_motor2);

    // Configuración del timer para el PWM
    ledc_timer_config_t timerConfig = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 20000
    };

    ledc_timer_config(&timerConfig);

    return ESP_OK;
}

esp_err_t set_pwm_duty(void)
{
    // Establecer el duty para cada canal disponible
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, dutyM1);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, dutyM2);

    // Actualizar el duty
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
    return ESP_OK;
}

esp_err_t init_motors(void)
{
    gpio_reset_pin(M2O1);
    gpio_reset_pin(M2O2);
    gpio_set_direction(M2O1, GPIO_MODE_OUTPUT);
    gpio_set_direction(M2O2, GPIO_MODE_OUTPUT);

    gpio_reset_pin(M1O1);
    gpio_reset_pin(M1O2);
    gpio_set_direction(M1O1, GPIO_MODE_OUTPUT);
    gpio_set_direction(M1O2, GPIO_MODE_OUTPUT);
    return ESP_OK;
}

esp_err_t set_direction(void)
{
    if (distance > 30)
    {
        dutyM1 = 820;
        dutyM2 = 820;
        M1O1_level = 1;
        M1O2_level = 0;
        M2O1_level = 1;
        M2O2_level = 0;
    }
    else if (distance < 10)
    {
        dutyM1 = 820;
        dutyM2 = 410;
        M1O1_level = 1;
        M1O2_level = 0;
        M2O1_level = 1;
        M2O2_level = 0;
    }
    else if (distance < 5)
    {
        vTaskDelay(pdMS_TO_TICKS(500));
        dutyM1 = 0;
        dutyM2 = 0;
        M2O1_level = 0;
        M2O2_level = 0;
        M1O1_level = 0;
        M1O2_level = 0;
    }

    set_pwm_duty();
    gpio_set_level(M1O1, M1O1_level);
    gpio_set_level(M1O2, M1O2_level);
    gpio_set_level(M2O1, M2O1_level);
    gpio_set_level(M2O2, M2O2_level);
    return ESP_OK;
}

void ultrasonic_test(void *pvParameters)
{
    ultrasonic_sensor_t sensor = {
        .trigger_pin = TRIGGER_GPIO,
        .echo_pin = ECHO_GPIO
    };

    ultrasonic_init(&sensor);

    while (true)
    {
        esp_err_t res = ultrasonic_measure(&sensor, MAX_DISTANCE_CM, &distance);
        if (res != ESP_OK)
        {
            printf("Error %d: ", res);
            switch (res)
            {
                case ESP_ERR_ULTRASONIC_PING:
                    printf("Cannot ping (device is in an invalid state)\n");
                    break;
                case ESP_ERR_ULTRASONIC_PING_TIMEOUT:
                    printf("Ping timeout (no device found)\n");
                    break;
                case ESP_ERR_ULTRASONIC_ECHO_TIMEOUT:
                    printf("Echo timeout (i.e. distance too big)\n");
                    break;
                default:
                    printf("%s\n", esp_err_to_name(res));
            }
        }
        else
            distance = distance * 100;
        printf("Distance: %0.04f cm\n", distance);

        set_direction();  // Actualizar la dirección basada en la nueva distancia

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
*/

#include <stdio.h>
#include <stdbool.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/ledc.h"
#include <ultrasonic.h>
#include <esp_err.h>

// Definiciones para el HC-SR04: pines y distancia máxima
#define MAX_DISTANCE_CM 500 // 5m máx.

#define TRIGGER_GPIO 5
#define ECHO_GPIO 18

// Definiciones para las salidas al L293D
#define M1O1 12
#define M1O2 13
#define M2O1 34
#define M2O2 35

int dutyM1 = 0;
int dutyM2 = 0;

float distance;

uint8_t M1O1_level = 0;
uint8_t M2O1_level = 0;
uint8_t M1O2_level = 0;
uint8_t M2O2_level = 0;

esp_err_t set_direction(void);
esp_err_t set_pwm_adelante(void);
esp_err_t set_pwm_duty(void);
esp_err_t init_motors(void);
void ultrasonic_test();

void app_main(void)
{

    init_motors();
    set_pwm_adelante();
    set_direction();

    xTaskCreate(ultrasonic_test, "ultrasonic_test", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}

// Función que habilita los pines 33 y 25 para PWM
esp_err_t set_pwm_adelante(void)
{
    // Configuración del canal del motor 1
    ledc_channel_config_t ChConfig_motor1 = {
        .gpio_num = 33,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0
    };

    // Configuración del canal del motor 2
    ledc_channel_config_t ChConfig_motor2 = {
        .gpio_num = 25,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0
    };

    ledc_channel_config(&ChConfig_motor1);
    ledc_channel_config(&ChConfig_motor2);

    // Configuración del timer para el PWM
    ledc_timer_config_t timerConfig = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 20000
    };

    ledc_timer_config(&timerConfig);

    return ESP_OK;
}

esp_err_t set_pwm_duty(void)
{
    // Establecer el duty para cada canal disponible
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, dutyM1);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, dutyM2);

    // Actualizar el duty
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
    return ESP_OK;
}

esp_err_t init_motors(void)
{
    gpio_reset_pin(M2O1);
    gpio_reset_pin(M2O2);
    gpio_set_direction(M2O1, GPIO_MODE_OUTPUT);
    gpio_set_direction(M2O2, GPIO_MODE_OUTPUT);

    gpio_reset_pin(M1O1);
    gpio_reset_pin(M1O2);
    gpio_set_direction(M1O1, GPIO_MODE_OUTPUT);
    gpio_set_direction(M1O2, GPIO_MODE_OUTPUT);
    return ESP_OK;
}

esp_err_t set_direction(void)
{
    if (distance > 20)
    {
        dutyM1 = 820;
        dutyM2 = 820;
        M1O1_level = 1;
        M1O2_level = 0;
        M2O1_level = 1;
        M2O2_level = 0;
    }
    else if (distance < 10)
    {
        dutyM1 = 820;
        dutyM2 = 410;
        M1O1_level = 1;
        M1O2_level = 0;
        M2O1_level = 1;
        M2O2_level = 0;
    }
    else if (distance < 5)
    {
        vTaskDelay(pdMS_TO_TICKS(500));
        dutyM1 = 0;
        dutyM2 = 0;
        M2O1_level = 0;
        M2O2_level = 0;
        M1O1_level = 0;
        M1O2_level = 0;
    }

    set_pwm_duty();
    gpio_set_level(M1O1, M1O1_level);
    gpio_set_level(M1O2, M1O2_level);
    gpio_set_level(M2O1, M2O1_level);
    gpio_set_level(M2O2, M2O2_level);
    return ESP_OK;
}

void ultrasonic_test(void *pvParameters)
{
    ultrasonic_sensor_t sensor = {
        .trigger_pin = TRIGGER_GPIO,
        .echo_pin = ECHO_GPIO
    };

    ultrasonic_init(&sensor);

    while (true)
    {
        esp_err_t res = ultrasonic_measure(&sensor, MAX_DISTANCE_CM, &distance);
        if (res != ESP_OK)
        {
            printf("Error %d: ", res);
            switch (res)
            {
                case ESP_ERR_ULTRASONIC_PING:
                    printf("Cannot ping (device is in an invalid state)\n");
                    break;
                case ESP_ERR_ULTRASONIC_PING_TIMEOUT:
                    printf("Ping timeout (no device found)\n");
                    break;
                case ESP_ERR_ULTRASONIC_ECHO_TIMEOUT:
                    printf("Echo timeout (i.e. distance too big)\n");
                    break;
                default:
                    printf("%s\n", esp_err_to_name(res));
            }
        }
        else
            distance *= 100; // Convertir a centímetros

        printf("Distance: %0.04f cm\n", distance);

        set_direction();  // Actualizar la dirección basada en la nueva distancia

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
