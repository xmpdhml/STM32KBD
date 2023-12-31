list(APPEND STM32F401xB "STM32F401CB" "STM32F401RB" "STM32F401VB")
list(APPEND STM32F401xC "STM32F401CC" "STM32F401RC" "STM32F401VC")

list(APPEND STM32F401xBxC ${STM32F401xB} ${STM32F401xC})

list(APPEND SUPPORTED_MCU ${STM32F401xBxC})

if(MCU IN_LIST SUPPORTED_MCU)
    if(MCU IN_LIST STM32F401xBxC)
        set(MCUSTM "STM32F401xC")
        set(CMSIS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/stm32cube_mcu_package/STM32CubeF4/Drivers/CMSIS")
        set(DEVICE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/stm32cube_mcu_package/STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx")
        set(HAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/stm32cube_mcu_package/STM32CubeF4/Drivers/STM32F4xx_HAL_Driver")
        set(STARTUP_SOURCE "${DEVICE_PATH}/Source/Templates/gcc/startup_stm32f401xc.s")
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

# STM32F401xB/C features and peripheral counts
#+-----------------------------------+----------------------------------+--------------------------------+
#| Peripherals                       |            STM32F401xB           |           STM32F401xC          |
#+-----------------------------------+----------------------------------+--------------------------------+
#| Flash memory in Kbytes            |                128               |               256              |
#+----------------+------------------+----------------------------------+--------------------------------+
#| SRAM in Kbytes | System           |                                 64                                |
#+----------------+------------------+-------------------------------------------------------------------+
#| Timers         | General-purpose  |                                 7                                 |
#|                +------------------+-------------------------------------------------------------------+
#|                | Advanced-control |                                 1                                 |
#+----------------+------------------+---------------------+------------+--------------------+-----------+
#|                | SPI/I2S          |  3/2 (full duplex)  |  4/2 (full |  3/2 (full duplex) | 4/2 (full |
#|                |                  |                     |   duplex)  |                    |  duplex)  |
#|                +------------------+---------------------+------------+--------------------+-----------+
#| Communication  | I2C              |                                 3                                 |
#|                +------------------+-------------------------------------------------------------------+
#| interfaces     | USART            |                                 3                                 |
#|                +------------------+-----------+----------------------+-----------+--------------------+
#|                | SDIO             |     -     |           1          |     -     |          1         |
#+----------------+------------------+-----------+----------------------+-----------+--------------------+
#| USB OTG FS                        |                                 1                                 |
#+-----------------------------------+-----------+---------+------------+-----------+--------+-----------+
#| GPIOs                             |     36    |    50   |     81     |     36    |   50   |     81    |
#+-----------------------------------+-----------+---------+------------+-----------+--------+-----------+
#| 12bit ADC                         |                                 1                                 |
#|                                   +-----------+----------------------+-----------+--------------------+
#| Number of Channels                |     10    |          16          |     10    |         16         |
#+-----------------------------------+-----------+----------------------+-----------+--------------------+
#| Max CPU frequency                 |                               84 MHz                              |
#+-----------------------------------+-------------------------------------------------------------------+
#| Operating voltage                 |                            1.7 to 3.6 V                           |
#+-----------------------------------+-------------------------------------------------------------------+
#| Operating                         | Ambient temperatures: –40 to +85 °C/–40 to +105 °C/–40 to +125 °C |
#|                                   +-------------------------------------------------------------------+
#| temperatures                      |               Junction temperature: –40 to + 130 °C               |
#+-----------------------------------+-----------+---------+------------+-----------+--------+-----------+
#| Package                           |  WLCSP49  |  LQFP64 |  UFBGA100  |  WLCSP49  | LQFP64 |  UFBGA100 |
#|                                   |  UFQFPN48 |         |   LQFP100  |  UFQFPN48 |        |  LQFP100  |
#+-----------------------------------+-----------+---------+------------+-----------+--------+-----------+
