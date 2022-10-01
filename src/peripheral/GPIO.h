#ifndef _GPIO_H_
#define _GPIO_H_

typedef enum {
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E
} PORTS;

typedef enum {
    PIN_00 = 0x0001,
    PIN_01 = 0x0002,
    PIN_02 = 0x0004,
    PIN_03 = 0x0008,
    PIN_04 = 0x0010,
    PIN_05 = 0x0020,
    PIN_06 = 0x0040,
    PIN_07 = 0x0080,
    PIN_08 = 0x0100,
    PIN_09 = 0x0200,
    PIN_10 = 0x0400,
    PIN_11 = 0x0800,
    PIN_12 = 0x1000,
    PIN_13 = 0x2000,
    PIN_14 = 0x4000,
    PIN_15 = 0x8000
} PINS;

typedef enum {PinLow, PinHigh} PinValues;

typedef enum {PinDirectionInput, PinDirectionOutput} PinDirections;

void GPIO_InitPin(PORTS PortNumber, PINS PinNumber, PinDirections PinDirection);

void GPIO_WritePin(PORTS PortNumber, PINS PinNumber, PinValues PinValue);

int GPIO_ReadPin(PORTS PortNumber, PINS PinNumber);

void GPIO_TogglePin(PORTS PortNumber, PINS PinNumber);

#endif