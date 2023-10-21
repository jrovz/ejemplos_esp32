# Control de Motores DC con ESP-IDF

Este proyecto demuestra cómo controlar dos motores DC de forma independiente utilizando el marco de desarrollo ESP-IDF. La librería `dcmotor` permite configurar los pines GPIO, controlar la velocidad y frenar los motores de manera sencilla.

## Requisitos

- Placa de desarrollo ESP32.
- Framework de desarrollo ESP-IDF instalado y configurado.
- Dos motores DC.


## Configuración

Asegúrate de configurar los pines GPIO en el archivo `main.c` de acuerdo con tu hardware. Puedes encontrar más información en la librería `dcmotor.h`.

2

## Uso
1. Clona este repositorio en tu entorno de desarrollo ESP-IDF.

2. Configura los pines GPIO según tu hardware.

3. Compila y carga el proyecto en tu placa ESP32.

4. Los motores funcionarán de acuerdo con las configuraciones definidas en `main.c`.

## Contribuciones
Si deseas contribuir a este proyecto, siéntete libre de hacerlo. Puedes crear una bifurcación (fork) y enviar solicitudes de extracción (pull requests) con mejoras, correcciones o nuevas características.
