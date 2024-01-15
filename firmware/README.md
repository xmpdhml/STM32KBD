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

## Debugging

### Debugging with OpenOCD on Windows and WSL

If you are working on Windows but developing the fireware in WSL, like I do, you can use OpenOCD to debug the firmware but you need to install the Windows version of OpenOCD, because the Linux version will not be able to access the STLink USB device.

Download the latest Windows version of OpenOCD from [here](https://github.com/openocd-org/openocd/releases).

Start OpenOCD with the following command:

`openocd -f interface\stlink.cfg -f target\stm32f4x.cfg -c "bindto 0.0.0.0"`

This would allow it to be accessed from WSL.

You also need to install gbe-multiarch, which is a GDB client that can be used to debug ARM targets from x86_64.

If you use VSCode as I do, you can install a plugin "GDB Debugger - Beyond" and then add a debugging configuration as below:
```json
{
    "type": "by-gdb",
    "request": "launch",
    "debuggerPath": "gdb-multiarch",
    "name": "Launch(remote)",
    "program": "${workspaceRoot}/firmware/build/STM32KBD.elf",
    "cwd": "${workspaceRoot}/firmware",
    "stopAtEntry": true,
    "remote": {
        "enabled": true,
        "address": "<host IP>:3333",
        "mode": "extended-remote",
        "execfile": "${workspaceRoot}/firmware/build/STM32KBD.elf"
    }
}
```