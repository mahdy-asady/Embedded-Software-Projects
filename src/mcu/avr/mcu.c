#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include "GPIO.h"

void getLedInfo(PORTS *Port, PINS *Pin) {
    *Port = PORT_C;
    *Pin = PIN_07;
}

void delay_ms(double duration) {
    _delay_ms(duration);
}

void mcuInit(void) {
}
