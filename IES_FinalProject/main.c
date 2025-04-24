// Final Project Code for IES
// By: Jordan Reyes & Chelsea Small

//*************************************************************************************** 
/*
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
#include <msp430.h>
#include "Init Headers/flameInit.h"
#include "systemInit.h"
//==================================================================================================
//NOTE: uint8_t is a datatype representing 8 digit binary numbers from 0-255, increases processing speed (supposedly)
//FUNCTIONS DECLARATIONS
//Color Definitions
#define BLUE 0, 0, 255
#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define YELLOW 255, 255, 0
//STARTUP
void RGB_setColor(uint8_t red, uint8_t green, uint8_t blue, );
void heat_call();        // Thermostat requests heat
void PilotValve_on();    // Open Gas Valve
void ignitor_on();       // Ignite Pilot
bool flame_detect();     // TRUE=flame present, FALSE=no flame

//Flame Present
void PilotValve_off();
int pot_Read();
int valvePosition = pot_Read();
void MainValve_set(int valvePosition);

//No Flame
ignitor_off();

//==================================================================================================
int main(void) {
    // Initialization
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
    system_init();    
    RGBsetColor(BLUE);                       // STATE: Idle
   if(heat_call()){                               // Thermostat requests heat
				RGB_setColor(YELLOW);             // HEAT REQUEST STATE
				PilotValve_On();                  // Open pilot gas valve
				//delay_ms(200);                  // DELAY - Wait for gas to release
				ignitor_on();                     // Ignite Pilot
				//delay_ms(500);                  // DELAY - Wait for ignition to stabilize
				
				if(flame_Detect()){               // Ignited Pilot Success
					RGB_setColor(GREEN);          // STATE: Heating
					PilotValve_off();             // Turn off pilot lighter
					MainValve_set(valvePosition); // Open main valve	
				}
				
			else{
				RGB_setColor(RED);                // STATE: Error (no flame)
				PilotValve_off();                 // Turn pilot gas off
				ignitor_off();                    // Turn ignitor off
			}
		} else {                                  // No heat requested
			RGB_setColor(BLUE);                   // STATE: Idle
			MainValve_set(0);                     // Close Main Valve
			PilotValve_off();                     // Ensure pilot gas valve is closed
			ignitor_off();                        // Ensure ignitor is off
		}
		//delay_ms(1000);                         // DELAY - Wait b4 next loop cycle
	}
	return 0;
}

//==================================================================================================
//define functions

void RGBsetColor(char Red, char Green, char Blue){
    TB3CCR3 = Red << 2;
    TB3CCR2 = Green << 2;
    TB3CCR1 = Blue << 2;
}//done

void heatCall(){ // P3.0-Call Heat
    return 0;
}
bool flame_detect(){ // P1.6-Thermistor 
    return 0;
}
void ignitorOn(){ // P1.3-Thermocouple
    
}
void ignitorOff(){ // P1.3-Thermocouple
    return 0;
}
void PilotValve_On(){ // P5.4-Solenoid
    return 0;
}
void PilotValve_off(){ // P5.4-Solenoid
    return 0;
}
int pot_Read(){ // P1.5-Potentiometer
    return 0;
}
void MainValve_set(int valveposition){ // P2.1-Servo
    return 0;
}

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
