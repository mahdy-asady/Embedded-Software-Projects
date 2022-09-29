#include <stdio.h>
#include "CliInterface.h"

static void (*fnCommandCallBack)(uint8_t *);
static uint8_t Command[100] = {0};
static int index = 0;

void ReceiveCharacter(uint8_t *Char) {
    printf("%s", Char);
    
    if(*Char == '\n') {
        Command[index] = '\0';
        (*fnCommandCallBack)(Command);
        index = 0;
    }
    else 
        Command[index++] = *Char;
}


CharReceivingHook CliInterfaceInit(void (*CallBack)(uint8_t *)) {
    fnCommandCallBack = CallBack;
    return &ReceiveCharacter;
}