cmake_minimum_required(VERSION 3.10)

project(STM32KBD C ASM)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

#settings
include(config.cmake)

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(generic)
include(check_mcu)
include(setup_path)

#Uncomment for hardware floating point
set(FPU_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16")
add_definitions( -D${MCUSTM} -DUSE_HAL_DRIVER )

#Uncomment for software floating point
#set(FPU_FLAGS "-mfloat-abi=soft")

set(COMMON_FLAGS "-mcpu=cortex-m4 ${FPU_FLAGS} -mthumb")
set(C_FLAGS "-ffunction-sections -fdata-sections -g -Og -Wall -gdwarf-2")

set(CMAKE_C_FLAGS "${COMMON_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} ${C_FLAGS}")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} ${C_FLAGS} -x assembler-with-cpp")

file(GLOB ASM_SOURCES ${STARTUP_SOURCE})

if(GENERATE_LST_FILES)
  set(CMAKE_C_COMPILE_OBJECT "${CMAKE_C_COMPILE_OBJECT} -Wa,-a,-ad,-alms=<OBJECT>.lst")
endif()

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${ASM_SOURCES} ${LINKER_SCRIPT})
target_link_libraries(${PROJECT_NAME}.elf c m nosys)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${SIZE} ${PROJECT_NAME}.elf
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -O binary -S $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
