# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_PATH "xxx/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(schnorr_curve25519_mcu C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(schnorr_curve25519_mcu schnorr_curve25519_mcu.c )

pico_set_program_name(schnorr_curve25519_mcu "schnorr_curve25519_mcu")
pico_set_program_version(schnorr_curve25519_mcu "0.1")

pico_enable_stdio_uart(schnorr_curve25519_mcu 1)
pico_enable_stdio_usb(schnorr_curve25519_mcu 1)

# Add the standard library to the build
target_link_libraries(schnorr_curve25519_mcu
        pico_stdlib)

# Add the hardware library, for the random nr generator
target_link_libraries(schnorr_curve25519_mcu hardware_adc)

# Add the standard include files to the build
target_include_directories(schnorr_curve25519_mcu PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(schnorr_curve25519_mcu 
        )

pico_add_extra_outputs(schnorr_curve25519_mcu)

