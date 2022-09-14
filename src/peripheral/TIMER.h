#ifndef __TIMER_h__
#define __TIMER_h__

/*
    Creates a timer hook based on requested time in mili Seconds
*/
void EnableTimer1(void (*CallBack)(void), unsigned int IntervalInMSec);

#endif