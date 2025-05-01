#include <msp430.h>
#include "pilotInit.h"

void pilot_init(){
    P5DIR |= BIT4;  // Output Px.y
    P5OUT &= ~BIT4; // Init state of 0
}
//Pilot(solenoid) = P5.4