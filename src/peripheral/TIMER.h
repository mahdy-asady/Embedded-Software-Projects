#ifndef __TIMER_h__
#define __TIMER_h__

/*
    Creates a timer hook based on requested time in mili Seconds
    Return:
        - true: timer set successfully
        - false: Error in Setting timer, mostly because the range user specified exceeded the acceptable range
*/
int EnableTimer1(void (*CallBack)(void), unsigned int IntervalInMSec);

void DisableTimer1(void);

#endif