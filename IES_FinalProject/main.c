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
    RGBsetColor(BLUE);                    // STATE: Idle
   if(heat_call()){                       // Thermostat requests a light
		RGB_setColor(YELLOW);             // HEAT REQUEST STATE
		PilotValve_On();                  // Open pilot gas valve
		//delay_ms(200);                  // DELAY - Wait for gas to release
		ignitor_on();                     // Ignite Pilot
		//delay_ms(500);                  // DELAY - Wait for ignition to stabilize
				
		if(flame_Detect()){               // Ignited Pilot Success (hi)
			RGB_setColor(GREEN);          // STATE: Heating
			PilotValve_off();             // Turn off pilot lighter
			MainValve_set(30);            // Open main valve	
		}
				
		else{							  // (lo)
			RGB_setColor(RED);            // STATE: Error (no flame)
			PilotValve_off();             // Turn pilot gas off
			ignitor_off();                // Turn ignitor off
		}
	} 
	else {                                // No heat requested
			RGB_setColor(BLUE);           // STATE: Idle
			MainValve_set(0);             // Close Main Valve
			PilotValve_off();             // Ensure pilot gas valve is closed
			ignitor_off();                // Ensure ignitor is off
	}
	//delay_ms(1000);                     // DELAY - Wait b4 next loop cycle
	return 0;
}

//==================================================================================================
//define functions

void RGBsetColor(char Red, char Green, char Blue){
    TB3CCR3 = Red << 2;
    TB3CCR2 = Green << 2;
    TB3CCR1 = Blue << 2;
}//done

bool heat_Call(){ 				// P3.0-Call Heat (Activate Button)
    return ~(P1IN & BIT6); 		// Call for a light when there's no flame
}
bool flame_detect(){ 			// P1.6-Thermistor 
    return (P1IN & BIT6);		// TRUE if P1.6 returns a signal
}
int pot_Read(){ 				// P1.5-Potentiometer
    return (P1OUT & BIT5);		// Read the altered values of the potentiometer
}
void ignitorOn(){ 				// P1.3-Thermocouple
    P1OUT |= BIT3;				// Output a signal at P1.3
}
void ignitorOff(){			    // P1.3-Thermocouple
    P1OUT &= ~BIT3;				// Shut off signals outputting from P1.3
}
void PilotValve_On(){ 			// P5.4-Solenoid
    P5OUT |= BIT4;				// Output a signal at P5.4
}
void PilotValve_off(){ 			// P5.4-Solenoid
    P5OUT &= ~BIT4;				// Shut off signals outputting from P5.4
}
void MainValve_set(int valveposition){ // P2.1-Servo
    // Configure Timer B1
    TB1CCR0 = 330;                             // PWM Period/2 (sets ~50Hz at 32kHz ACLK)
    TB1CCTL2 = OUTMOD_7;                       // TB1.2 reset/set output mode
    TB1CCR2 = valveposition;                   // PWM duty cycle (~7.5% for servo center)
    TB1CTL = TBSSEL__ACLK | MC_3;              // ACLK, up-down mode
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