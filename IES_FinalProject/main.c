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

void system_init(); // All function initializations

int main(void) {
    RGB_setColor(0, 0, 255); // Blue for idle system
    system_init();
    while(1) // while loop
    {       

    }
}

void system_init(){
    power_on();
    UART_init();
    therm_Init();

    pot_Init();
    flame_Init();//thermocouple
    heat_init(); //thermostat ("Call for heat")

    RGB_init();
    ignitor_init();
    PilotValve_init();

    MainValve_init();
    I2C_init(); //If using any I2C peripherals
    //-----------------------------------------\\
   // Set initial system status
    RGB_setColor(0, 0, 255); // Blue for idle system
}

void RGB_init(){
    P6DIR |= BIT0 | BIT1 | BIT2;              // P6.0-P6.2 output
    P6SEL0 |= BIT0 | BIT1 | BIT2;
    P6SEL1 &= ~(BIT0 | BIT1 | BIT2);          // P6.0-P6.2 options select
}

void setRGBLED(char Red, char Green, char Blue){
    TB3CCR3 = Red << 2;
    TB3CCR2 = Green << 2;
    TB3CCR1 = Blue << 2;
}