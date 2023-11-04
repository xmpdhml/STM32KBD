#include "gpio.h"


// Initialize the row pin
void KBD_Init_Row(KBD_PIN_t pin) {
    // Set the pin as output open drain
    
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
