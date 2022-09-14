#include<avr/interrupt.h>

static void (*fnCallBack)(void);
static unsigned int TickCopmrator = 0;


ISR(TIMER1_COMPA_vect) {
    static unsigned int TickCounter = 0;

    TCNT1 = 0;
    if(TickCounter++ == TickCopmrator) {
        TickCounter = 0;
        (*fnCallBack)();
    }
}

void EnableTimer1(void (*CallBack)(void), unsigned int IntervalInMSec) {
    TickCopmrator = IntervalInMSec;
    fnCallBack = CallBack;

    //create 1miliseconds friction of time comprator value
    OCR1A = F_CPU / 1000 / 256;

    TCCR1B = 0 << CS10 | 0 << CS11 | 1 << CS12; //use 256 prescaler
    TIMSK |= 1 << OCIE1A; //enable compare interrupt

    sei();
}