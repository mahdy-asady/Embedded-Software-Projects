#include <avr/io.h>
#include "GPIO.h"
#include "debug.h"

static volatile uint8_t * GetPort(PORTS PortNumber) {
    switch (PortNumber)
    {
    case PORT_A:
        return &PORTA;
    case PORT_B:
        return &PORTB;
    case PORT_C:
        return &PORTC;
    case PORT_D:
        return &PORTD;
    default:
        log_error("Wrong Port specified!\n");
        return NULL;
    }
}

static volatile uint8_t * GetDDR(PORTS PortNumber) {
    switch (PortNumber)
    {
    case PORT_A:
        return &DDRA;
    case PORT_B:
        return &DDRB;
    case PORT_C:
        return &DDRC;
    case PORT_D:
        return &DDRD;
    default:
        log_error("Wrong Port specified!\n");
        return NULL;
    }
}

void GPIO_InitPin(PORTS PortNumber, PINS PinNumber, PinDirections PinDirection) {
    if(PinDirection == PinDirectionOutput)
        (*GetDDR(PortNumber)) |= PinNumber;
    else
        (*GetDDR(PortNumber)) &= ~PinNumber;
}

void GPIO_WritePin(PORTS PortNumber, PINS PinNumber, PinValues PinValue) {
    if(PinValue == PinHigh)
        (*GetPort(PortNumber)) |= PinNumber; 
    else 
        (*GetPort(PortNumber)) &= ~PinNumber;
}

void GPIO_TogglePin(PORTS PortNumber, PINS PinNumber) {
    (*GetPort(PortNumber)) ^= PinNumber;
}