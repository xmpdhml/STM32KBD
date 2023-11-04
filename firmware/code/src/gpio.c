#include "gpio.h"
#include "mem_addresses.h"

#include <stdio.h>

#define GPIO_DEBUG

#ifndef GPIO_DEBUG
#define printf(...)
#endif

#define __PORT_OF(pin) (pin / 16)
#define __PIN_OF(pin) (pin % 16)

// Initialize the row pin
void KBD_Init_Row(KBD_PIN_t pin) {
    printf("KBD_Init_Row: %.2x\n", pin);
    // Set the pin as output open drain
#ifdef USE_BIT_BANDING
    // OSPEEDR
    *(uint16_t*)(__GPIO_BB_BASE_PORT(__PORT_OF(pin)) + 0x08 * 0x20 + __PIN_OF(pin) * 2) = 
    #if GPIO_OSPEEDR == 0
        0x0000
    #elif GPIO_OSPEEDR == 1
        0x0100
    #elif GPIO_OSPEEDR == 2
        0x0001
    #elif GPIO_OSPEEDR == 3
        0x0101
    #endif
    ;
    printf("OSPEEDR %.8lx", __GPIO_BASE_PORT(__PORT_OF(pin)) + 0x08);

    // OTYPER 1 (open drain)
    *(uint8_t*)(__GPIO_BB_BASE_PORT(__PORT_OF(pin)) + 0x04 * 0x20 + __PIN_OF(pin)) = 0x01;
    printf("OTYPER %.8lx", __GPIO_BASE_PORT(__PORT_OF(pin)) + 0x04);

    // PUPDR 00 (no pullup/pulldown)
    *(uint16_t*)(__GPIO_BB_BASE_PORT(__PORT_OF(pin)) + 0x0C * 0x20 + __PIN_OF(pin) * 2) = 0;
    printf("PUPDR %.8lx", __GPIO_BASE_PORT(__PORT_OF(pin)) + 0x0C);

    // MODER: 01 (output)
    *(uint16_t*)(__GPIO_BB_BASE_PORT(__PORT_OF(pin)) + __PIN_OF(pin) * 2) = 0x0100;
    printf("MODER %.8lx", __GPIO_BASE_PORT(__PORT_OF(pin)) + 0x00);
#else
    // OSPEEDR
    __disable_irq();
    temp = *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x08);
    temp &= ~(GPIO_OSPEEDR << (__PIN_OF(pin) * 2));
    temp |= (GPIO_OSPEEDR << (__PIN_OF(pin) * 2));
    *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x08) = temp;
    __enable_irq();
    printf("OSPEEDR %.8lx", __GPIO_BASE_PORT(__PORT_OF(pin)) + 0x08);

    // OTYPER 1 (open drain)
    *(volatile uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x04) |= (1 << __PIN_OF(pin));
    printf("OTYPER %.8lx", __GPIO_BASE_PORT(__PORT_OF(pin)) + 0x04);

    // PUPDR 00 (no pullup/pulldown)
    *(volatile uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x0C) &= ~(3 << (__PIN_OF(pin) * 2));
    printf("PUPDR %.8lx", __GPIO_BASE_PORT(__PORT_OF(pin)) + 0x0C);

#endif
}

// Initialize the column pin
void KBD_Init_Col(KBD_PIN_t pin) {
    // Set the pin as input pullup
    
}

void KBD_Select_Row(KBD_PIN_t pin) {
    // Set the pin to LOW
    
}

void KBD_Unselect_Row(KBD_PIN_t pin) {
    // Set the pin to HIGH (open drain)
}

// Read the state of the column pin
int Read_Col(KBD_PIN_t pin) {
    return 0;
}

// Read the state of all pins in the port
uint32_t Read_Port(KBD_PORT_t port) {
    return 0;
}
