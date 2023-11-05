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
        printf("before: MODER 0x%.8lx OTYPER 0x%.8lx OSPEEDR 0x%.8lx PUPDR 0x%.8lx IDR 0x%.8lx ODR 0x%.8lx BSRR 0x%.8lx LCKR 0x%.8lx AFR[0] 0x%.8lx AFR[1] 0x%.8lx\n",
            port->MODER,
            port->OTYPER,
            port->OSPEEDR,
            port->PUPDR,
            port->IDR,
            port->ODR,
            port->BSRR,
            port->LCKR,
            port->AFR[0],
            port->AFR[1]);
    }
#endif

    // Set the pin as output open drain
#if USE_BIT_BANDING
    // OSPEEDR
    uint32_t* temp = (uint32_t*)(__GPIO_BB_BASE_PORT(__PORT_OF(pin)) + 0x08 * 0x20 + __PIN_OF(pin) * 8);
    #if GPIO_OSPEEDR == 0
    *temp++ = 0;
    *temp = 0;
    #elif GPIO_OSPEEDR == 1
    *temp++ = 1;
    *temp = 0;
    #elif GPIO_OSPEEDR == 2
    *temp++ = 0;
    *temp = 1;
    #elif GPIO_OSPEEDR == 3
    *temp++ = 1;
    *temp = 1;
    #endif    
    printf("OSPEEDR 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x08));

    // OTYPER 1 (open drain)
    *(uint32_t*)(__GPIO_BB_BASE_PORT(__PORT_OF(pin)) + 0x04 * 0x20 + __PIN_OF(pin) * 4) = 1;
    printf("OTYPER 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x04));

    // PUPDR 00 (no pullup/pulldown)
    temp = (uint32_t*)(__GPIO_BB_BASE_PORT(__PORT_OF(pin)) + 0x0C * 0x20 + __PIN_OF(pin) * 8);
    *temp++ = 0;
    *temp = 0;
    printf("PUPDR 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x0C));

    // MODER: 01 (output)
    temp = (uint32_t*)(__GPIO_BB_BASE_PORT(__PORT_OF(pin)) + __PIN_OF(pin) * 8);
    *temp++ = 1;
    *temp = 0;
    printf("MODER 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x00));
#else
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
#endif

#if GPIO_DEBUG > 1
    {
        GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
        printf("after: MODER 0x%.8lx OTYPER 0x%.8lx OSPEEDR 0x%.8lx PUPDR 0x%.8lx IDR 0x%.8lx ODR 0x%.8lx BSRR 0x%.8lx LCKR 0x%.8lx AFR[0] 0x%.8lx AFR[1] 0x%.8lx\n",
            port->MODER,
            port->OTYPER,
            port->OSPEEDR,
            port->PUPDR,
            port->IDR,
            port->ODR,
            port->BSRR,
            port->LCKR,
            port->AFR[0],
            port->AFR[1]);
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

#if USE_BIT_BANDING
    // PUPDR 01 (pullup)
    uint32_t* temp = (uint32_t*)(__GPIO_BB_BASE_PORT(__PORT_OF(pin)) + 0x0C * 0x20 + __PIN_OF(pin) * 8 + 4);
    *temp-- = 0;
    *temp = 1;
    printf("PUPDR 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x0C));

    // MODER: 00 (input)
    temp = (uint32_t*)(__GPIO_BB_BASE_PORT(__PORT_OF(pin)) + __PIN_OF(pin) * 8);
    *temp++ = 0;
    *temp = 0;
    printf("MODER 0x%.8lx\n", *(uint32_t*)(__GPIO_BASE_PORT(__PORT_OF(pin)) + 0x00));
#else
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
#endif

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

void KBD_Select_Row(KBD_PIN_t pin) {
    // Set the pin to LOW
    printf("KBD_Select_Row: 0x%.2x\n", pin);
#if GPIO_DEBUG > 1
    {
        GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
        printf("before: IDR 0x%.8lx ODR 0x%.8lx\n", port->IDR, port->ODR);
    }
#endif

#if USE_BIT_BANDING
    {
        uint32_t* rs = (uint32_t*)(__GPIO_BB_BASE_PORT(__PORT_OF(pin)) + 0x18 * 0x20 + 0x10 + __PIN_OF(pin) * 4);
        printf("RS PIN: 0x%.8lx\n", (uint32_t)rs);
        *rs = 1;
    }
#else
    GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
    port->BSRR = (1 << (__PIN_OF(pin) + 16));
#endif

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

#if USE_BIT_BANDING
    {
        uint32_t* bs = (uint32_t*)(__GPIO_BB_BASE_PORT(__PORT_OF(pin)) + 0x18 * 0x20 + __PIN_OF(pin) * 4);
        printf("BS PIN: 0x%.8lx\n", (uint32_t)bs);
        *bs = 0;
    }
#else
    GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
    port->BSRR = (1 << (__PIN_OF(pin)));
#endif

#if GPIO_DEBUG > 1
    {
        GPIO_TypeDef* port = (GPIO_TypeDef*)__GPIO_BASE_PORT(__PORT_OF(pin));
        printf("after: IDR 0x%.8lx ODR 0x%.8lx\n", port->IDR, port->ODR);
    }
#endif

}

// Read the state of the column pin
int Read_Col(KBD_PIN_t pin) {
    return 0;
}

// Read the state of all pins in the port
uint32_t Read_Port(KBD_PORT_t port) {
    return 0;
}
