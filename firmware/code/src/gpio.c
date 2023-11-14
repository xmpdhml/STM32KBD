#include "gpio.h"
#include "mem_addresses.h"

#include <stdio.h>

#define GPIO_DEBUG 0

#if !defined(GPIO_DEBUG) || GPIO_DEBUG == 0
#define printf(...)
#endif

#define __PORT_OF(pin) (pin / 16)
#define __PIN_OF(pin) (pin % 16)

// Initialize the row pin
void KBD_Init_Row(KBD_PIN_t pin) {
    printf("KBD_Init_Row: 0x%.2x\n", pin);

#if GPIO_DEBUG > 1
    {
        GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
        printf("before: MODER 0x%.8lx OTYPER 0x%.8lx OSPEEDR 0x%.8lx PUPDR 0x%.8lx\n",
            port->MODER,
            port->OTYPER,
            port->OSPEEDR,
            port->PUPDR);
    }
#endif

    // Set the pin as output open drain
    uint32_t temp;
    GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));

    // OSPEEDR
    temp = port->OSPEEDR;
    temp &= ~(GPIO_OSPEEDR << (__PIN_OF(pin) * 2));
    temp |= (GPIO_OSPEEDR << (__PIN_OF(pin) * 2));
    port->OSPEEDR = temp;
    printf("OSPEEDR 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x08));

    // OTYPER 1 (open drain)
    port->OTYPER |= (1 << __PIN_OF(pin));
    printf("OTYPER 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x04));

    // PUPDR 00 (no pullup/pulldown)
    port->PUPDR &= ~(3 << (__PIN_OF(pin) * 2));
    printf("PUPDR 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x0C));

    // MODER: 01 (output)
    temp = port->MODER;
    temp &= ~(1 << (__PIN_OF(pin) * 2));
    temp |= (1 << (__PIN_OF(pin) * 2));
    port->MODER = temp;
    printf("MODER 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x00));

#if GPIO_DEBUG > 1
    {
        GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
        printf("after: MODER 0x%.8lx OTYPER 0x%.8lx OSPEEDR 0x%.8lx PUPDR 0x%.8lx\n",
            port->MODER,
            port->OTYPER,
            port->OSPEEDR,
            port->PUPDR);
    }
#endif

}

// Initialize the column pin
void KBD_Init_Col(KBD_PIN_t pin) {
    // Set the pin as input pullup
    printf("KBD_Init_Col: 0x%.2x\n", pin);

#if GPIO_DEBUG > 1
    {
        GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
        printf("before: MODER 0x%.8lx OTYPER 0x%.8lx OSPEEDR 0x%.8lx PUPDR 0x%.8lx\n",
            port->MODER,
            port->OTYPER,
            port->OSPEEDR,
            port->PUPDR);
    }
#endif

    uint32_t temp;
    GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));

    // PUPDR 01 (pullup)
    temp = port->PUPDR;
    temp &= ~(3 << (__PIN_OF(pin) * 2));
    temp |= (1 << (__PIN_OF(pin) * 2));
    port->PUPDR = temp;
    printf("PUPDR 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x0C));

    // MODER: 00 (input)
    temp = port->MODER;
    temp &= ~(3 << (__PIN_OF(pin) * 2));
    port->MODER = temp;
    printf("MODER 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x00));

#if GPIO_DEBUG > 1
    {
        GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
        printf("after: MODER 0x%.8lx OTYPER 0x%.8lx OSPEEDR 0x%.8lx PUPDR 0x%.8lx\n",
            port->MODER,
            port->OTYPER,
            port->OSPEEDR,
            port->PUPDR);
    }
#endif

}

void KBD_Init_LED(KBD_PIN_t pin, bool positive)
{
    printf("KBD_Init_LED: 0x%.2x\n", pin);
    GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));

#if GPIO_DEBUG > 1
    {
        GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
        printf("before: MODER 0x%.8lx OTYPER 0x%.8lx OSPEEDR 0x%.8lx PUPDR 0x%.8lx\n",
            port->MODER,
            port->OTYPER,
            port->OSPEEDR,
            port->PUPDR);
    }
#endif

    if (positive)
    {
        // Set the pin as output push pull
        uint32_t temp;

        // OSPEEDR
        temp = port->OSPEEDR;
        temp &= ~(GPIO_OSPEEDR << (__PIN_OF(pin) * 2));
        temp |= (GPIO_OSPEEDR << (__PIN_OF(pin) * 2));
        port->OSPEEDR = temp;
        printf("OSPEEDR 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x08));

        // OTYPER 0 (push pull)
        port->OTYPER &= ~(1 << __PIN_OF(pin));
        printf("OTYPER 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x04));

        // PUPDR 00 (no pullup/pulldown)
        port->PUPDR &= ~(3 << (__PIN_OF(pin) * 2));
        printf("PUPDR 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x0C));

        // MODER: 01 (output)
        temp = port->MODER;
        temp &= ~(1 << (__PIN_OF(pin) * 2));
        temp |= (1 << (__PIN_OF(pin) * 2));
        port->MODER = temp;
        printf("MODER 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x00));
    }
    else
    {

    }
    
}

void KBD_Select_Row(KBD_PIN_t pin) {
    // Set the pin to LOW
    printf("KBD_Select_Row: 0x%.2x\n", pin);
#if GPIO_DEBUG > 1
    {
        GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
        printf("before: IDR 0x%.8lx ODR 0x%.8lx\n", port->IDR, port->ODR);
    }
#endif

    GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
    port->BSRR = (1 << (__PIN_OF(pin) + 16));

#if GPIO_DEBUG > 1
    {
        GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
        printf("after: IDR 0x%.8lx ODR 0x%.8lx\n", port->IDR, port->ODR);
    }
#endif

}

void KBD_Unselect_Row(KBD_PIN_t pin) {
    // Set the pin to HIGH (open drain)
    printf("KBD_Unselect_Row: 0x%.2x\n", pin);
#if GPIO_DEBUG > 1
    {
        GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
        printf("before: IDR 0x%.8lx ODR 0x%.8lx\n", port->IDR, port->ODR);
    }
#endif

    GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
    port->BSRR = (1 << (__PIN_OF(pin)));

#if GPIO_DEBUG > 1
    {
        GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
        printf("after: IDR 0x%.8lx ODR 0x%.8lx\n", port->IDR, port->ODR);
    }
#endif

}

// Read the state of the column pin
int Read_Col(KBD_PIN_t pin) {
    return ((GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin)))->IDR & (1 << __PIN_OF(pin)) >> __PIN_OF(pin);
}

// Read the state of all pins in the port
uint32_t Read_Port(KBD_PORT_t port) {
    return ((GPIO_TypeDef*)__GPIO_BASE_PORT(port))->IDR;
}

