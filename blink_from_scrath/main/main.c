/*
    Este codigo hace parpadear el led que esta conectado al puerto
    GPIO 02 de la tarjeta ESP32 wroom32
    primero se importan las librerias que se usaran en el codigo
    se estara empleando el sistema operativo freeRTOS y una funcion
    del mismo llamada task.h
*/
#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

//se define el puerto que se usara (02)
#define led1 2
static const char* tag = "MyModule";

uint8_t led_level =0;
uint8_t count = 0;


// se inicializan las funciones que inician el led y
// la que lo hace parpadear
esp_err_t init_led(void);
esp_err_t blink_led(void);

void app_main(void)
{
   init_led();

   while(1)
   {
        vTaskDelay(200 / portTICK_PERIOD_MS); // 200ms de periodo
        blink_led(); //llama la funcion de parpadeo
        count +=1;
        if (count >30)
        {
            count = 0;
        }
        
        if(count < 10)
        {
            ESP_LOGI(tag,"value: %u.",count);
        }
        if (count >= 10 && count < 20)
        {
            ESP_LOGW(tag,"value: %u.",count);
        }
        if (count >= 20)
        {
            ESP_LOGE(tag,"value: %u.",count);
        }
        
        //printf("led level: %u\n", led_level); //imprime la salida del puerto 2
   } 
}

// funcion para inicializar el puerto 2
esp_err_t init_led(void)
{
    gpio_reset_pin(led1);
    gpio_set_direction(led1, GPIO_MODE_DEF_OUTPUT);
    return ESP_OK;
}

//funcion para intermitencia entre on/off del GPIO 02
esp_err_t blink_led(void)
{
    led_level = !led_level;
    gpio_set_level(led1,led_level);
    return ESP_OK;
}
