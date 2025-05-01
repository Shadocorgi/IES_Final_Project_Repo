#include <msp430.h>
#include "RGBInit.h"

void RGB_init(){
    P6DIR |= BIT0 | BIT1 | BIT2;              // P6.0-P6.2 output
    P6SEL0 |= BIT0 | BIT1 | BIT2;
    P6SEL1 &= ~(BIT0 | BIT1 | BIT2);          // P6.0-P6.2 options select

    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;
	TB3CCR0 = 255;

    TB3CCTL1 = OUTMOD_7;
    TB3CCTL2 = OUTMOD_7;
    TB3CCTL3 = OUTMOD_7;
}//done
