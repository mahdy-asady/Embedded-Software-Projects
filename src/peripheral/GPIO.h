#ifndef _GPIO_H_
#define _GPIO_H_

typedef enum {
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D
} PORTS;

typedef enum {
    PIN_00,
    PIN_01,
    PIN_02,
    PIN_03,
    PIN_04,
    PIN_05,
    PIN_06,
    PIN_07,
    PIN_08,
    PIN_09,
    PIN_10,
    PIN_11,
    PIN_12,
    PIN_13,
    PIN_14,
    PIN_15
} PINS;

typedef enum {PinLow, PinHigh} PinValues;

typedef enum {PinDirectionInput, PinDirectionOutput} PinDirections;

void GPIO_InitPin(PORTS PortNumber, PINS PinNumber, PinDirections PinDirection);

void GPIO_WritePin(PORTS PortNumber, PINS PinNumber, PinValues PinValue);

void GPIO_TogglePin(PORTS PortNumber, PINS PinNumber);

#endif