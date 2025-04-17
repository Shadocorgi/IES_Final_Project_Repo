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

*/
//***************************************************************************************

#include <driverlib.h>
#include "systemInit.h"

//void system_init(); // All function initializations
   // Set initial system status
    RGB_setColor(0, 0, 255); // Blue for idle system

int main(void) {
    RGB_setColor(0, 0, 255); // Blue for idle system
    system_init();
    while(1)
    {          
        
    }
}

//==================================================================================================

void RGB_setColor(char Red, char Green, char Blue){
    TB3CCR3 = Red << 2;
    TB3CCR2 = Green << 2;
    TB3CCR1 = Blue << 2;
}//done

//==================================================================================================

void power_on() {
    
} // power

// All of these functions are transferred to headers
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
// void RGB_init()        {}