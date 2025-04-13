// Final Project Code for IES
#include <driverlib.h>


void system_init(); // All function initializations


int main(void) {
    RGB_setColor(0, 0, 255); // Blue for idle system
    system_init();
    while(1)
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