#include <msp430.h>
#include "potInit.h"

void pot_init(){
    P1DIR |= BIT5;  // Input BTN Px.y
    P1OUT |= BIT5;  // Init state of 0
    P1REN |= BIT5;  // Enable Pull-up Resistor
}
