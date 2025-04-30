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
- Call Heat - P1.6 (uses thermistor)
- Servo Motor - P2.1

- Thermistor - P1.6
- Potentiometer - P1.5
- Thermocouple - P1.3

*/
//***************************************************************************************
#include <driverlib.h>
#include <msp430.h>
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
void RGB_setColor(uint8_t red, uint8_t green, uint8_t blue);
bool heat_call();        // Thermostat requests heat
void pilotValve_on();    // Open Gas Valve
void ignitor_on();       // Ignite Pilot
bool flame_detect();     // TRUE=flame present, FALSE=no flame

//Flame Present
void pilotValve_off();
int pot_read();
void mainValve_set(int valvePosition);

//No Flame
void ignitor_off();

//==================================================================================================
int main(void) {
    // Initialization
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
	system_init();
	ignitor_off();
	int valvePosition = pot_read();
	
	
	    
    RGB_setColor(BLUE);                    // STATE: Idle
   if(heat_call()){                       // Thermostat requests a light
		RGB_setColor(YELLOW);             // HEAT REQUEST STATE
		pilotValve_on();                  // Open pilot gas valve
		//delay_ms(200);                  // DELAY - Wait for gas to release
		ignitor_on();                     // Ignite Pilot
		//delay_ms(500);                  // DELAY - Wait for ignition to stabilize
				
		if(flame_detect()){               // Ignited Pilot Success (hi)
			RGB_setColor(GREEN);          // STATE: Heating
			pilotValve_off();             // Turn off pilot lighter
			mainValve_set(30);            // Open main valve	
		}
				
		else{							  // (lo)
			RGB_setColor(RED);            // STATE: Error (no flame)
			pilotValve_off();             // Turn pilot gas off
			ignitor_off();                // Turn ignitor off
		}
	} 
	else {                                // No heat requested
			RGB_setColor(BLUE);           // STATE: Idle
			mainValve_set(0);             // Close Main Valve
			pilotValve_off();             // Ensure pilot gas valve is closed
			ignitor_off();                // Ensure ignitor is off
	}
	//delay_ms(1000);                     // DELAY - Wait b4 next loop cycle
	return 0;
}

//==================================================================================================
//Testing Area
/*
	RGBsetColor(BLUE);

}
*/
//==================================================================================================
//define functions
bool heat_call(){ 				// P1.6-Call Heat (Activate Button)
    return ~(P1IN & BIT6); 		// Call for a light when there's no flame (uses thermistor)
}
bool flame_detect(){ 			// P1.6-Thermistor 
    return (P1IN & BIT6);		// TRUE if P1.6 returns a signal
}
int pot_read(){ 				// P1.5-Potentiometer
    return (P1IN & BIT5);		// Read the altered values of the potentiometer
}



void RGB_setColor(uint8_t Red, uint8_t Green, uint8_t Blue){
    TB3CCR3 = Red << 2;
    TB3CCR2 = Green << 2;
    TB3CCR1 = Blue << 2;
}
void ignitor_on(){ 				// P1.3-Thermocouple
    P1OUT |= BIT3;				// Output a signal at P1.3
}
void ignitor_off(){			    // P1.3-Thermocouple
    P1OUT &= ~BIT3;				// Shut off signals outputting from P1.3
}
void pilotValve_on(){ 			// P5.4-Solenoid
    P5OUT |= BIT4;				// Output a signal at P5.4
}
void pilotValve_off(){ 			// P5.4-Solenoid
    P5OUT &= ~BIT4;				// Shut off signals outputting from P5.4
}
void mainValve_set(int valveposition){ // P2.1-Servo
    // Configure Timer B1
    TB1CCR0 = 330;                             // PWM Period/2 (sets ~50Hz at 32kHz ACLK)
    TB1CCTL2 = OUTMOD_7;                       // TB1.2 reset/set output mode
    TB1CCR2 = valveposition;                   // PWM duty cycle (~7.5% for servo center)
    TB1CTL = TBSSEL__ACLK | MC_3;              // ACLK, up-down mode
}

//==================================================================================================

// All of these initialization functions were transferred to headers
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