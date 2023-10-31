cmake_minimum_required(VERSION 3.10)

project(STM32KBD C ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

#settings
include(config.cmake)

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(generic)
include(check_mcu)

#Uncomment for hardware floating point
set(FPU_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16")
add_definitions( -DSTM32F401xC -DUSE_HAL_DRIVER )

#Uncomment for software floating point
#set(FPU_FLAGS "-mfloat-abi=soft")

set(COMMON_FLAGS "-mcpu=cortex-m4 ${FPU_FLAGS} -mthumb")
set(C_FLAGS "-ffunction-sections -fdata-sections -g -Og -Wall")

set(CMAKE_C_FLAGS "${COMMON_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} ${C_FLAGS}")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} ${C_FLAGS} -x assembler-with-cpp")

#add_definitions(-D__weak=__attribute__\(\(weak\)\) -D__packed=__attribute__\(\(__packed__\)\) -DUSE_HAL_DRIVER -$STM32F401xx)

file(GLOB ASM_SOURCES ${STARTUP_SOURCE})
#set_property(SOURCE ${ASM_SOURCES} APPEND PROPERTY COMPILE_OPTIONS "-x" "assembler-with-cpp")
file(GLOB HEADERS "Core/Inc/*.h")
file(GLOB SOURCES "code/src/*.c")


#print out ASM_SOURCES
message(STATUS "ASM_SOURCES: ${ASM_SOURCES}")



include_directories(Core/Inc
    Drivers/STM32F4xx_HAL_Driver/Inc
    Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    Drivers/CMSIS/Include)

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${ASM_SOURCES} ${LINKER_SCRIPT})
target_link_libraries(${PROJECT_NAME}.elf m)

set(CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT} ${COMMON_FLAGS} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map,--cref -Wl,--gc-sections -lc -lnosys -specs=nano.specs")

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${SIZE} ${PROJECT_NAME}.elf
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -O binary -S $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")

