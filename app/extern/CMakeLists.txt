set(LIB_NAME "nrf5_sdk")

# Source files common to all targets
set(SRC_FILES
  ${SDK_ROOT}/modules/nrfx/mdk/gcc_startup_nrf52840.S
  ${SDK_ROOT}/components/libraries/log/src/nrf_log_frontend.c
  ${SDK_ROOT}/components/libraries/log/src/nrf_log_str_formatter.c
  ${SDK_ROOT}/components/boards/boards.c
  ${SDK_ROOT}/components/libraries/util/app_error.c
  ${SDK_ROOT}/components/libraries/util/app_error_handler_gcc.c
  ${SDK_ROOT}/components/libraries/util/app_error_weak.c
  ${SDK_ROOT}/components/libraries/util/app_util_platform.c
  ${SDK_ROOT}/components/libraries/util/nrf_assert.c
  ${SDK_ROOT}/components/libraries/atomic/nrf_atomic.c
  ${SDK_ROOT}/components/libraries/balloc/nrf_balloc.c
  ${SDK_ROOT}/external/fprintf/nrf_fprintf.c
  ${SDK_ROOT}/external/fprintf/nrf_fprintf_format.c
  ${SDK_ROOT}/components/libraries/memobj/nrf_memobj.c
  ${SDK_ROOT}/components/libraries/ringbuf/nrf_ringbuf.c
  ${SDK_ROOT}/components/libraries/strerror/nrf_strerror.c
  ${SDK_ROOT}/modules/nrfx/soc/nrfx_atomic.c
  ${SDK_ROOT}/modules/nrfx/mdk/system_nrf52840.c 
)

# Include folders common to all targets
set(INC_FOLDERS
  ${SDK_ROOT}/components
  ${SDK_ROOT}/modules/nrfx/mdk
  ${SDK_ROOT}/components/libraries/strerror
  ${SDK_ROOT}/components/toolchain/cmsis/include
  ${SDK_ROOT}/components/libraries/util
  ${SDK_ROOT}/components/libraries/balloc
  ${SDK_ROOT}/components/libraries/ringbuf
  ${SDK_ROOT}/modules/nrfx/hal
  ${SDK_ROOT}/components/libraries/bsp
  ${SDK_ROOT}/components/libraries/log
  ${SDK_ROOT}/modules/nrfx
  ${SDK_ROOT}/components/libraries/experimental_section_vars
  ${SDK_ROOT}/components/libraries/delay
  ${SDK_ROOT}/integration/nrfx
  ${SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd
  ${SDK_ROOT}/components/libraries/atomic
  ${SDK_ROOT}/components/boards
  ${SDK_ROOT}/components/libraries/memobj
  ${SDK_ROOT}/external/fprintf
  ${SDK_ROOT}/components/libraries/log/src
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(${LIB_NAME} OBJECT ${SRC_FILES})

target_compile_definitions(${LIB_NAME} PUBLIC
  BOARD_PCA10056
  BSP_DEFINES_ONLY
  CONFIG_GPIO_AS_PINRESET
  FLOAT_ABI_HARD
  NRF52840_XXAA
  __HEAP_SIZE=8192
  __STACK_SIZE=8192
)

target_compile_options(${LIB_NAME} PUBLIC
  -O3
  -g3
  -mcpu=cortex-m4
  -mthumb -mabi=aapcs
  -Wall -Werror -Wno-array-bounds
  -mfloat-abi=hard -mfpu=fpv4-sp-d16
  # keep every function in a separate section, this allows linker to discard unused ones
  -ffunction-sections -fdata-sections -fno-strict-aliasing
  -fno-builtin -fshort-enums
)

target_link_options(${LIB_NAME} PUBLIC
  -O3
  -g3
  -mthumb -mabi=aapcs
  -L${SDK_ROOT}/modules/nrfx/mdk
  -T${CMAKE_CURRENT_SOURCE_DIR}/ld/blinky_gcc_nrf52.ld
  -mcpu=cortex-m4
  -mfloat-abi=hard -mfpu=fpv4-sp-d16
  # let linker dump unused sections
  -Wl,--gc-sections
  # use newlib in nano version
  --specs=nano.specs    
)

# Add standard libraries at the very end of the linker input, after all objects
# that may need symbols provided by these libraries.
target_link_libraries(${LIB_NAME} PUBLIC -lc -lnosys -lm)
target_include_directories(${LIB_NAME} PUBLIC ${INC_FOLDERS})


