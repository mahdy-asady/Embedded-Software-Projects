#include <stdio.h>
#include "util.h"
#include "USART.h"
#include "TIMER.h"


#ifdef STM32F107xC
#include "ErrorHandler.h"
#endif



void timer1_tick(void);

int main(void)
{
    InitHardWare();
    USART_init_printf();

    if(!EnableTimer1(timer1_tick, 1000))
        printf("Timer Error!\n");
    
    while(1);
}

void timer1_tick(void) {
    static unsigned int i = 0;
    printf("%u\n", i++);
}
