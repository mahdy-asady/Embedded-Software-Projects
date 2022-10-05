#include <stdio.h>
#include "GPIO.h"
#include "CommandInterpreter/CommandInterpreter.h"
#include "banned.h"

void PinSetOutput(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char* HookParams);
void PinSetInput (char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char* HookParams);
void PinOn       (char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char* HookParams);
void PinOff      (char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char* HookParams);
void PinToggle   (char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char* HookParams);
void PinGetValue (char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char* HookParams);
void ShowHelp    (char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char* HookParams);

void GPIOModuleInit(void) {
    CommandsRegister("gpio.output", &PinSetOutput, "");
    CommandsRegister("gpio.input", &PinSetInput, "");
    CommandsRegister("gpio.on", &PinOn, "");
    CommandsRegister("gpio.off", &PinOff, "");
    CommandsRegister("gpio.toggle", &PinToggle, "");
    CommandsRegister("gpio.value", &PinGetValue, "");

    CommandsRegister("help.gpio", &ShowHelp, "");
}


void PinSetOutput(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams) {
    PORTS PortNumber = **CommandParams - 'a';
    PINS PinNumber = 1 << (**(CommandParams + 1) - '0');
    GPIO_InitPin(PortNumber, PinNumber, PinDirectionOutput);
    printf("Pin Set to Output\n");
}

void PinSetInput(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams) {
    PORTS PortNumber = **CommandParams - 'a';
    PINS PinNumber = 1 << (**(CommandParams + 1) - '0');
    GPIO_InitPin(PortNumber, PinNumber, PinDirectionInput);
    printf("Pin Set to Input\n");
}

void PinOn(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams) {
    PORTS PortNumber = **CommandParams - 'a';
    PINS PinNumber = 1 << (**(CommandParams + 1) - '0');
    GPIO_WritePin(PortNumber, PinNumber, 1);
    printf("Pin Set to High\n");
}

void PinOff(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams) {
    PORTS PortNumber = **CommandParams - 'a';
    PINS PinNumber = 1 << (**(CommandParams + 1) - '0');
    GPIO_WritePin(PortNumber, PinNumber, 0);
    printf("Pin Set to LOW\n");
}

void PinToggle(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams) {
    PORTS PortNumber = **CommandParams - 'a';
    PINS PinNumber = 1 << (**(CommandParams + 1) - '0');
    GPIO_TogglePin(PortNumber, PinNumber);
    printf("Pin Toggled.\n");
}

void PinGetValue(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char *HookParams) {
    PORTS PortNumber = **CommandParams - 'a';
    PINS PinNumber = 1 << (**(CommandParams + 1) - '0');
    int Value = GPIO_ReadPin(PortNumber, PinNumber);
    printf("Pin Value is: %s\n", Value? "HIGH" : "LOW");
}

void ShowHelp(char CommandParams[][COMMANDS_MAX_TOKENS_LENGTH], size_t ParamsCount, char* HookParams) {
    printf("GPIO Usage:\n\tgpio.[Action].[PortNumber].[PinNumber]\nAll Parameters are mandatory!\n\n");
}