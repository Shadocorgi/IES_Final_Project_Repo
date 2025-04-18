#include <msp430.h>
#include "heatInit.h"

void heat_init(void){
    P3DIR |= BIT0;  // Input BTN Px.y
    P3OUT |= BIT0;  // Init state of 0
    P3REN |= BIT0;  // Enable Pull-up Resistor
}
//Call Heat = P3.0