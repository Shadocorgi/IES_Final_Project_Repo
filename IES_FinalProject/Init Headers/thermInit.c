#include <msp430.h>
#include "thermInit.h"

void therm_init(){
    P1DIR |= BIT6;  // Input BTN Px.y
    P1OUT |= BIT6;  // Init state of 0
    P1REN |= BIT6;  // Enable Pull-up Resistor
}
//Thermistor = P1.6