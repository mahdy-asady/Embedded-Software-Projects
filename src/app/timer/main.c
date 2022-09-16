#include <avr/io.h>
#include <stdio.h>
//#include<avr/interrupt.h>
#include "../../peripheral/USART.h"
#include "../../peripheral/TIMER.h"

void timer1_tick(void) {
    static unsigned int i = 0;
    printf("%u\n", i++);
}

int main(void)
{
    USART_init_printf();

    if(!EnableTimer1(timer1_tick, 1000))
        printf("Timer Error!\n");
    
    while(1);
}