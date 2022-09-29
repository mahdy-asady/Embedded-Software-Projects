#include <stdio.h>
#include "CliInterface.h"

static void (*fnCommandCallBack)(uint8_t *);
static uint8_t Command[100] = {0};
static int StringPosition = 0;

void ReceiveCharacter(uint8_t *Char) {
    
    printf("%s", Char);
    
    if(*Char == '\n') {
        Command[StringPosition] = '\0';
        (*fnCommandCallBack)(Command);
        StringPosition = 0;
    }
    else {
        if(*Char == 127) //backspace
            StringPosition--;
        else
            Command[StringPosition++] = *Char;
    }
}


CharReceivingHook CliInterfaceInit(void (*CallBack)(uint8_t *)) {
    fnCommandCallBack = CallBack;
    return &ReceiveCharacter;
}