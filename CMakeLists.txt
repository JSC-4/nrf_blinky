cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain-nrf5.cmake)

# set the project name and version
project(nrf_example VERSION 1.0 LANGUAGES C ASM)

set(PROJ_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/app/extern)
set(CMAKE_BINARY_DIR _build)

# Location of application specific code
add_subdirectory(app)