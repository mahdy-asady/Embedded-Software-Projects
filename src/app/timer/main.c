#include <stdio.h>
#include "mcu.h"
#include "USART.h"
#include "TIMER.h"

void timer1_tick(void);

int main(void)
{
    mcuInit();
    USART_init_printf();

    if(!EnableTimer1(timer1_tick, 1000))
        printf("Timer Error!\n");
    
    while(1);
}

void timer1_tick(void) {
    static unsigned int i = 0;
    printf("%u\n", i++);
}
