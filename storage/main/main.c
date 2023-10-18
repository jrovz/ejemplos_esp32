#include <stdio.h>
#include "freertos/freeRTOS.h"
#include "nvs_flash.h"
#include "nvs.h"

void app_main(void)
{
    printf("start!\n");

    // inicializar el NVS
    esp_err_t err = nvs_flash_init();    
    printf("NVS init!\n");
    printf((err != ESP_OK) ? "Failed" : "Done");

    // acceder a una partición de NVS
    nvs_handle_t my_storage;
    err = nvs_open("storage", NVS_READWRITE, &my_storage);
    printf("NVS open!.\n");
    printf((err != ESP_OK) ? "Failed" : "Done");

    // Escribir en NVS
    nvs_set_u32(my_storage, "number", 10);
    printf("NVS set\n");
    printf((err != ESP_OK) ? "Failed" : "Done");

    // Guardar en NVS
    nvs_commit(my_storage);
    printf("NVS commit.\n");
    printf((err != ESP_OK) ? "Failed" : "Done");


    // Leer NVS
    int32_t number;
    nvs_get_i32(my_storage, "number", &number);
    printf("NVS get!.\n");
    printf((err != ESP_OK) ? "Failed" : "Done");

    printf("el valor recuperado es: %ld\n", number);

    nvs_close(my_storage);
    printf("end!.\n");
}