# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "B:/ESP32/esp-idf/components/bootloader/subproject"
  "C:/Users/jrove/OneDrive/Escritorio/ejemplos_esp32/Task_blink/build/bootloader"
  "C:/Users/jrove/OneDrive/Escritorio/ejemplos_esp32/Task_blink/build/bootloader-prefix"
  "C:/Users/jrove/OneDrive/Escritorio/ejemplos_esp32/Task_blink/build/bootloader-prefix/tmp"
  "C:/Users/jrove/OneDrive/Escritorio/ejemplos_esp32/Task_blink/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/jrove/OneDrive/Escritorio/ejemplos_esp32/Task_blink/build/bootloader-prefix/src"
  "C:/Users/jrove/OneDrive/Escritorio/ejemplos_esp32/Task_blink/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/jrove/OneDrive/Escritorio/ejemplos_esp32/Task_blink/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/jrove/OneDrive/Escritorio/ejemplos_esp32/Task_blink/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
