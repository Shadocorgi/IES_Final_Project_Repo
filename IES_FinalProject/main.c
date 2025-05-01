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
#include "init_headers/systemInit.h"
//==================================================================================================
//NOTE: uint8_t is a datatype representing 8 digit binary numbers from 0-255, increases processing speed (supposedly)
//FUNCTIONS DECLARATIONS
//Color Definitions
const int L = 5;
#define BLUE 0, 0, L
#define RED L, 0, 0
#define GREEN 0, L, 0
#define YELLOW L, L, 0
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
void redLED_on();

//No Flame
void ignitor_off();
void redLED_off();

//==================================================================================================
int main(void) {
    // Initialization
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
	system_init();
	ignitor_off();
	int valvePosition = pot_read();
	
	
	/*
    RGB_setColor(BLUE);                   // STATE: Idle
	redLED_on();
   if(heat_call()){                       // Thermostat requests a light
		redLED_off();					  // no error
		RGB_setColor(YELLOW);             // HEAT REQUEST STATE
		pilotValve_on();                  // Open pilot gas valve
		//delay_ms(200);                  // DELAY - Wait for gas to release
		ignitor_on();                     // Ignite Pilot
		//delay_ms(500);                  // DELAY - Wait for ignition to stabilize
				
		if(flame_detect()){               // Ignited Pilot Success (hi)
			redLED_off();				  // no error
			RGB_setColor(GREEN);          // STATE: Heating
			pilotValve_off();             // Turn off pilot lighter
			mainValve_set(30);            // Open main valve	
		}
				
		else{							  // (lo)
			RGB_setColor(RED);            // STATE: Error (no flame)
			redLED_on();				  // error present
			pilotValve_off();             // Turn pilot gas off
			ignitor_off();                // Turn ignitor off
		}
	} 
	else {                                // No heat requested
			redLED_off();				  // no error
			RGB_setColor(BLUE);           // STATE: Idle
			mainValve_set(0);             // Close Main Valve
			pilotValve_off();             // Ensure pilot gas valve is closed
			ignitor_off();                // Ensure ignitor is off
	}
	//delay_ms(1000);                     // DELAY - Wait b4 next loop cycle
	return 0;
}
*/

//==================================================================================================
//Testing Area

	RGB_setColor(YELLOW);
	redLED_on();
}

//==================================================================================================
//define functions
bool heat_call(){return ~(P1IN & BIT6);}	// P1.6-Call Heat (Activate Button)
// Call for a light when there's no flame (uses thermistor)

bool flame_detect(){return (P1IN & BIT6);} 	// P1.6-Thermistor 
// TRUE if P1.6 returns a signal

int pot_read(){return (P1IN & BIT5);}		// P1.5-Potentiometer
// [ATTENTION-ATTENTION-ATTENTION-ATTENTION-ATTENTION-ATTENTION-ATTENTION-ATTENTION-ATTENTION]
// Read the altered values of the potentiometer
// Must be an ADC signal, is currently a digital signal. This must be changed.



void RGB_setColor(uint8_t Red, uint8_t Green, uint8_t Blue){ // [P6.0 - P6.2] Adjust RGB Values


    TB3CCR3 = Red;
    TB3CCR2 = Green;
    TB3CCR1 = Blue;
}
void ignitor_on(){P1OUT |= BIT3;} 		// P1.3-Thermocouple
void ignitor_off(){P1OUT &= ~BIT3;} 	// P1.3-Thermocouple
// Output/Shutoff signals to/from P1.3

void pilotValve_on(){P5OUT |= BIT4;}	// P5.4-Solenoid
void pilotValve_off(){P5OUT &= ~BIT4;}	// P5.4-Solenoid
// Output/Shutoff signals to/from P5.4

void redLED_on(){P5OUT |= BIT0;}		// P5.0-Red LED
void redLED_off(){P5OUT &= ~BIT0;}		// P5.0-Red LED
// Output/Shutoff signals to/from P5.0

void mainValve_set(int valveposition){ 	// P2.1-Servo
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
