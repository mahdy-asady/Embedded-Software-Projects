#include<avr/interrupt.h>

static void (*fnCallBack)(void);


ISR(TIMER1_COMPA_vect) {
    TCNT1 = 0;
    (*fnCallBack)();
}

int EnableTimer1(void (*CallBack)(void), unsigned int IntervalInMSec) {
    int InstructionsInMiliSecond = F_CPU / 1000 / 256;
    int MaxInterval = 0xFFFF / InstructionsInMiliSecond;
    if(IntervalInMSec > MaxInterval) return 0;

    fnCallBack = CallBack;

    //create 1 miliseconds friction of time comparator value
    OCR1A = IntervalInMSec * InstructionsInMiliSecond;

    TCCR1B = 0 << CS10 | 0 << CS11 | 1 << CS12; //use 256 prescaler
    TIMSK |= 1 << OCIE1A; //enable compare interrupt

    sei();
    return 1;
}

void DisableTimer1(void) {
    TIMSK &= ~(1 << OCIE1A); //disable compare interrupt
}