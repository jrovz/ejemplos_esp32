/* En este codigo se utilizan las primeras funciones de freeRTOS
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/*Cuando se ejecuta la funcion, la referencia a la ejecución se guarda
en la variable taskHandle1 para poder ser manipulada depues, como
reanudarla
*/ 

TaskHandle_t taskHandle1 = NULL;
TaskHandle_t TaskHandle2 = NULL;

//Funcion void para la tarea "task1"
void task1(void *args) {
    int count = 0;
    while(1){
        count++;
        printf("task 1 count: %d\n", count);
        if(count >= 3){
            vTaskSuspend(TaskHandle2);
            printf("Task 2 suspend\n");
        }
        if(count >= 10){
            vTaskResume(TaskHandle2);
            printf("Task 2 Restarted\n");
        }
        if(count >= 12){
            vTaskDelete(TaskHandle2);
            printf("Task 2 Deleted\n");
        }
        if(count >= 15){
            printf("Task 2 Suspend\n");
            vTaskDelete(NULL);
        }
    }
}

void task2(void *args) {
    int count = 0;
    while(1){
        count++;
        printf("task 2 count: %d\n", count);
        if(count >= 15){
            vTaskDelete(NULL);
        }
    }
}

void app_main()
{
    /* se crea la funcion, se le asigna un nombre, luego 
    la cantidad de memoria, seguido de los parametros para inicializar
    la funcion, luego se le asigna un numero de prioridad
    */ 
    xTaskCreate(task1, "task1", 4096, NULL, 10, &taskHandle1);
    xTaskCreatePinnedToCore(task2, "task2", 4096, NULL,10, &TaskHandle2, 1);
}