#include <msp430.h>
#include "flameInit.h"

void flame_init(void){
    P1DIR |= BIT3;  // Input BTN Px.y
    P1OUT |= BIT3;  // Init state of 0
    P1REN |= BIT3;  // Enable Pull-up Resistor
}
//Thermocouple = P1.3