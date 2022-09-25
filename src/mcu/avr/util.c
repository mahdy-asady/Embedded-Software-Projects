#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

void delay_ms(double duration) {
    _delay_ms(duration);
}