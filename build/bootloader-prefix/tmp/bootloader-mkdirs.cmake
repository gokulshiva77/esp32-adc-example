# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/gokul/esp/v5.4.1/esp-idf/components/bootloader/subproject"
  "/home/gokul/Documents/ESP32/ADCData/AdcEg/build/bootloader"
  "/home/gokul/Documents/ESP32/ADCData/AdcEg/build/bootloader-prefix"
  "/home/gokul/Documents/ESP32/ADCData/AdcEg/build/bootloader-prefix/tmp"
  "/home/gokul/Documents/ESP32/ADCData/AdcEg/build/bootloader-prefix/src/bootloader-stamp"
  "/home/gokul/Documents/ESP32/ADCData/AdcEg/build/bootloader-prefix/src"
  "/home/gokul/Documents/ESP32/ADCData/AdcEg/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/gokul/Documents/ESP32/ADCData/AdcEg/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/gokul/Documents/ESP32/ADCData/AdcEg/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
