#include <msp430.h>
#include "servoInit.h"

void servo_init(){
    // Servo initialization
    P2DIR |= BIT1;   // P2.1 DIR = output
    P2OUT &= ~BIT1;  // P2.1 initial output = 0
}