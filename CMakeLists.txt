cmake_minimum_required(VERSION 3.13)
set(NAME VFD_DSIPLAY) # <-- Name your project/executable here!

include(pico_sdk_import.cmake)

project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${NAME}
    main.cpp
)

# Add pico_stdlib library, add more if used
target_link_libraries(${NAME} pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(${NAME} 1)
pico_enable_stdio_uart(${NAME} 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(${NAME})