#include <stdio.h>
#include "CommandInterpreter/CommandInterpreter.h"

void PinSetOutput(char** CommandParams, char* HookParams);
void PinSetInput(char** CommandParams, char* HookParams);
void PinOn(char** CommandParams, char* HookParams);
void PinOff(char** CommandParams, char* HookParams);
void PinToggle(char** CommandParams, char* HookParams);
void PinGetValue(char** CommandParams, char* HookParams);

void GPIOModuleInit(void) {
    CommandsRegister("gpio.output", &PinSetOutput, "");
    CommandsRegister("gpio.input", &PinSetInput, "");
    CommandsRegister("gpio.on", &PinOn, "");
    CommandsRegister("gpio.off", &PinOff, "");
    CommandsRegister("gpio.toggle", &PinToggle, "");
    CommandsRegister("gpio.value", &PinGetValue, "");
}


void PinSetOutput(char** CommandParams, char* HookParams) {
    printf("Set Pin Output: %s\n", *CommandParams);
}

void PinSetInput(char** CommandParams, char* HookParams) {
    printf("Set Pin Input: %s\n", *CommandParams);
}

void PinOn(char** CommandParams, char* HookParams) {
    printf("Set Pin HIGH: %s\n", *CommandParams);
}

void PinOff(char** CommandParams, char* HookParams) {
    printf("Set Pin LOW: %s\n", *CommandParams);
}

void PinToggle(char** CommandParams, char* HookParams) {
    printf("Toggle Pin: %s\n", *CommandParams);
}

void PinGetValue(char** CommandParams, char* HookParams) {
    printf("Get Pin Value: %s\n", *CommandParams);
}