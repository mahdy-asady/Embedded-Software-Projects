#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "../../peripheral/USART.h"


int main(void)
{
    USART_init_printf();
    unsigned int i = 0;
    while(1) {
        printf("%u\n", i++);
        _delay_ms(100);
    }

    return 0;
}