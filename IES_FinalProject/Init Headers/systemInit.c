#include "systemInit.h"

void system_init(void)
{
    flame_Init();
    heat_init();
    I2C_init();
    ignitor_init();
    PilotValve_init();
    pot_Init();
    RGB_init();
    servoInit();
    therm_Init();
    UART_init();
}