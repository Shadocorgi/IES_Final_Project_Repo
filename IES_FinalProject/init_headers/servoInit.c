#include <msp430.h>
#include "servoInit.h"

void servo_init(){
    // Servo initialization
    P2DIR |= BIT1;   // P2.1 DIR = output
    P2OUT &= ~BIT1;  // P2.1 initial output = 0

    P2SEL1 |= BIT1;  // Select TB1.2 function
    P2SEL0 &= ~BIT1; // P2.1 Sel0 disabled

    // Disable high-impedance mode
    PM5CTL0 &= ~LOCKLPM5;
}
