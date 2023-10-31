list(APPEND STM32F401xB "STM32F401CB" "STM32F401RB" "STM32F401VB")
list(APPEND STM32F401xC "STM32F401CC" "STM32F401RC" "STM32F401VC")

list(APPEND STM32F401xBxC ${STM32F401xB} ${STM32F401xC})

list(APPEND SUPPORTED_MCU ${STM32F401xBxC})

if(MCU IN_LIST SUPPORTED_MCU)
    if(MCU IN_LIST STM32F401xBxC)
        set(MCUSTM "STM32F401xC")
        set(STARTUP_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/stm32cube_mcu_package/STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f401xc.s")
        if(MCU STREQUAL "STM32F401RC")
            set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/linker_scripts/STM32F401RCTx_FLASH.ld")
        else()
            message(FATAL_ERROR "MCU ${MCU} is not supported")
        endif()
    elseif (MCU STREQUAL "STM32F401xE")
        message(FATAL_ERROR "MCU ${MCU} is not supported")
    endif()
else()
    message(FATAL_ERROR "MCU ${MCU} is not supported")
endif()


# if(MCU STREQUAL STM32F401xC OR MCU STREQUAL STM32F401xE)
#     set(STARTUP_FILE ${CMAKE_SOURCE_DIR}/startup/startup_stm32f401xe.s)
# endif()
