set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
#set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)


# GPIO OUTPUT SPEED default 1
if(GPIO_OSPEEDR)
    add_definitions(-DGPIO_OSPEEDR=${GPIO_OSPEEDR})
else()
    add_definitions(-DGPIO_OSPEEDR=1)
endif()
