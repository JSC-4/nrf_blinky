set(EXE_NAME blinky)

add_subdirectory(extern)

add_executable(${EXE_NAME} main.c)
target_link_libraries(${EXE_NAME} PRIVATE "nrf5_sdk")

# Generate .map, .hex and .bin files during and after
# compiling for flashing and debugging purposes
target_link_options(${EXE_NAME} PRIVATE
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/extern/ld
)

add_custom_command(
    TARGET ${EXE_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE_UTIL} ARGS ${EXE_NAME}
    COMMENT "Size of ${EXE_NAME}.out"
)

# Create hex file
add_custom_command(TARGET ${EXE_NAME}
        POST_BUILD
        COMMAND arm-none-eabi-objcopy -O ihex ${EXE_NAME} ${EXE_NAME}.hex
        COMMAND arm-none-eabi-objcopy -O binary ${EXE_NAME} ${EXE_NAME}.bin)