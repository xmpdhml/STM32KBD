# STM32KBD Firmware

## Building

`git clone --recurse-submodules`<br />
`cd firmware`<br />
`mkdir build`<br />
`cd build`<br />
`cmake ..`<br />
`make`<br />

## Flashing

Use STM32CubeProgrammer to flash the .elf or .hex file which are located in the build directory.
