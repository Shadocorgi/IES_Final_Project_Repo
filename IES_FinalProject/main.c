// Final Project Code for IES
// By: Jordan Reyes & Chelsea Small

/*************************************************************************************** 
[COMPONENT PINS]
- RGB LED
	- Red: P6.0
	- Green: P6.1
	- Blue: P6.2
- Red LED - P5.0

- Pilot/Solenoid - 5.4 
- Call Heat - P3.0
- Servo Motor - P2.1

- Thermistor - P1.6
- Potentiometer - P1.5
- Thermocouple - P1.3

*///***************************************************************************************

#include <driverlib.h>
#include <msp430.h>
#include "systemInit.h"

//declare functions
// void delay_cycles(); is implemented from msp430.h
void RGB_setColor();

void igniterOn();
void igniterOff();

void heatCall();
void PilotValve_off();
void MainValve_set(int valveposition);


int main(void) {
    // Initialization
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
    system_init();    
    RGBsetColor(0, 0, 255); // Blue for idle system
    
    //Main Code
    while(1)
    {
        
    }
}

//==================================================================================================
//define functions

void RGBsetColor(char Red, char Green, char Blue){
    TB3CCR3 = Red << 2;
    TB3CCR2 = Green << 2;
    TB3CCR1 = Blue << 2;
}//done

void igniterOn(){}
void igniterOff(){}

void heatCall(){}
void PilotValve_off(){}
void MainValve_set(int valveposition){}

//==================================================================================================

// All of these functions are transferred to headers
// void RGB_init()        {} 
// void UART_init()       {}  
// void therm_Init()      {}
// void pot_Init()        {}
// void flame_Init()      {}
// void heat_init()       {}
// void RGB_init()        {}
// void ignitor_init()    {}
// void PilotValve_init() {}
// void MainValve_init()  {}
// void I2C_init()        {}
