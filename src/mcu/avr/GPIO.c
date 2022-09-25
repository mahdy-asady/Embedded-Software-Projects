#include <avr/io.h>
#include "GPIO.h"


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
    }
}

void GPIO_InitPin(PORTS PortNumber, PINS PinNumber, PinDirections PinDirection) {
    if(PinDirection == PinDirectionOutput)
        (*GetDDR(PortNumber)) |= (1 << PinNumber);
    else
        (*GetDDR(PortNumber)) &= ~(1 << PinNumber);
}

void GPIO_WritePin(PORTS PortNumber, PINS PinNumber, PinValues PinValue) {
    if(PinValue == PinHigh)
        (*GetPort(PortNumber)) |= 1 << PinNumber; 
    else 
        (*GetPort(PortNumber)) &= ~(1 << PinNumber); 
}

void GPIO_TogglePin(PORTS PortNumber, PINS PinNumber) {
    (*GetPort(PortNumber)) ^= (1 << PinNumber);
}