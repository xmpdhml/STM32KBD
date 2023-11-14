#ifndef __KBD_H__
#define __KBD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "hal.h"

typedef enum {
    KBD_PORT_A = 0,
    KBD_PORT_B = 1,
    KBD_PORT_C = 2,
    KBD_PORT_D = 3,
    KBD_PORT_E = 4,
    KBD_PORT_F = 5,
    KBD_PORT_G = 6,
    KBD_PORT_H = 7,
    KBD_PORT_I = 8,
    KBD_PORT_J = 9,
    KBD_PORT_K = 10,
} KBD_PORT_t;

typedef enum {
    KBD_PIN_0 = 0,
    KBD_PIN_1 = 1,
    KBD_PIN_2 = 2,
    KBD_PIN_3 = 3,
    KBD_PIN_4 = 4,
    KBD_PIN_5 = 5,
    KBD_PIN_6 = 6,
    KBD_PIN_7 = 7,
    KBD_PIN_8 = 8,
    KBD_PIN_9 = 9,
    KBD_PIN_10 = 10,
    KBD_PIN_11 = 11,
    KBD_PIN_12 = 12,
    KBD_PIN_13 = 13,
    KBD_PIN_14 = 14,
    KBD_PIN_15 = 15
} KBD_PORT_PIN_t;

#define KBD_PIN(port, pin) ((port << 4) | pin)

#define DEF_PINS_FOR_PORT(x) \
    x##0 = KBD_PIN(KBD_PORT_##x, KBD_PIN_0), \
    x##1 = KBD_PIN(KBD_PORT_##x, KBD_PIN_1), \
    x##2 = KBD_PIN(KBD_PORT_##x, KBD_PIN_2), \
    x##3 = KBD_PIN(KBD_PORT_##x, KBD_PIN_3), \
    x##4 = KBD_PIN(KBD_PORT_##x, KBD_PIN_4), \
    x##5 = KBD_PIN(KBD_PORT_##x, KBD_PIN_5), \
    x##6 = KBD_PIN(KBD_PORT_##x, KBD_PIN_6), \
    x##7 = KBD_PIN(KBD_PORT_##x, KBD_PIN_7), \
    x##8 = KBD_PIN(KBD_PORT_##x, KBD_PIN_8), \
    x##9 = KBD_PIN(KBD_PORT_##x, KBD_PIN_9), \
    x##10 = KBD_PIN(KBD_PORT_##x, KBD_PIN_10), \
    x##11 = KBD_PIN(KBD_PORT_##x, KBD_PIN_11), \
    x##12 = KBD_PIN(KBD_PORT_##x, KBD_PIN_12), \
    x##13 = KBD_PIN(KBD_PORT_##x, KBD_PIN_13), \
    x##14 = KBD_PIN(KBD_PORT_##x, KBD_PIN_14), \
    x##15 = KBD_PIN(KBD_PORT_##x, KBD_PIN_15)

typedef enum {
DEF_PINS_FOR_PORT(A),
DEF_PINS_FOR_PORT(B),
DEF_PINS_FOR_PORT(C),
DEF_PINS_FOR_PORT(D),
DEF_PINS_FOR_PORT(E),
DEF_PINS_FOR_PORT(F),
DEF_PINS_FOR_PORT(G),
DEF_PINS_FOR_PORT(H),
DEF_PINS_FOR_PORT(I),
DEF_PINS_FOR_PORT(J),
DEF_PINS_FOR_PORT(K),
} KBD_PIN_t;

// Initialize the row pin as output open drain
void KBD_Init_Row(KBD_PIN_t pin);

// Initialize the column pin as input pullup
void KBD_Init_Col(KBD_PIN_t pin);

// Initialize the LED pin
//      positive:
//          1 pin->LED->GND init as output push pull
//          0 VCC->LED->pin init as output open drain
void KBD_Init_LED(KBD_PIN_t pin, bool positive);

void KBD_Select_Row(KBD_PIN_t pin);
void KBD_Unselect_Row(KBD_PIN_t pin);

int Read_Col(KBD_PIN_t pin);
uint32_t Read_Port(KBD_PORT_t port);

#ifdef __cplusplus
}
#endif

#endif /*__ KBD_H__ */
