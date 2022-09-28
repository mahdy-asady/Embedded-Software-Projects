#ifndef __MCU_h__
#define __MCU_h__

#include "GPIO.h"

#ifdef STM32F107xC

#include "ErrorHandler.h"

#endif

void delay_ms(double duration);

void mcuInit(void);

void getLedInfo(PORTS *Port, PINS *Pin);

#endif
