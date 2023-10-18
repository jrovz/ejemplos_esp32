#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "freertos/timers.h"
#include "driver/ledc.h"

// se define el puerto que se usara (02)
#define led1 2
static const char *tag = "main";

uint8_t led_level = 0;

// se inicializan las funciones que inician el led y
// la que lo hace parpadear
TimerHandle_t xTimers;
int interval = 500;
int timerId = 1;

esp_err_t init_led(void);
esp_err_t blink_led(void);
esp_err_t set_timer(void); // inicializar el timer
esp_err_t set_pwm(void); // inicializar PMM

void vTimerCallback(TimerHandle_t pxTimer)
{
    ESP_LOGI(tag, "Event was called from timer");
    blink_led();
}

void app_main(void)
{
    init_led();
    set_timer();
}

// funcion para inicializar el puerto 2
esp_err_t init_led(void)
{
    gpio_reset_pin(led1);
    gpio_set_direction(led1, GPIO_MODE_DEF_OUTPUT);
    return ESP_OK;
}

// funcion para intermitencia entre on/off del GPIO 02
esp_err_t blink_led(void)
{
    led_level = !led_level;
    gpio_set_level(led1, led_level);
    return ESP_OK;
}

esp_err_t set_timer(void)
{
    ESP_LOGI(tag, "timer init configuration.");
    xTimers = xTimerCreate("Timer",                   // Just a text name, not used by the kernel.
                           (pdMS_TO_TICKS(interval)), // The timer period in ticks.
                           pdTRUE,                    // The timers will auto-reload themselves when they expire.
                           (void *)timerId,           // Assign each timer a unique id equal to its array index.
                           vTimerCallback             // Each timer calls the same callback when it expires.
    );

    if (xTimers == NULL)
    {
        // The timer was not created.
        ESP_LOGE(tag, "The timer was no created.");
    }
    else
    {

        if (xTimerStart(xTimers, 0) != pdPASS)
        {
            ESP_LOGE(tag, " The timer could not be set into the active state");
        }
    }
    return ESP_OK;
}


esp_err_t set_pwm(void)
{
    
}