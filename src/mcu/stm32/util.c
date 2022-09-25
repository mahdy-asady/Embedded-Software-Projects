#include "ErrorHandler.h"

void delay_ms(double duration) {
    HAL_Delay(duration);
}


void InitHardWare(void) {
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    SystemClock_Config();
}
