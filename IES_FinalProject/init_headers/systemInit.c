#include <msp430.h>
#include "systemInit.h"

void system_init()
{
    heat_init();
    ignitor_init();
    pilot_init();
    pot_init();
    RGB_init();
    servo_init();
    therm_init();
    LED_init();
}
