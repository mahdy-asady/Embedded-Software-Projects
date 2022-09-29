#include <stdio.h>
#include "CliInterface.h"

static void (*fnCommandCallBack)(char *);
static char Command[100] = {0};
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


CharReceivingHook CliInterfaceInit(void (*CallBack)(char *)) {
    fnCommandCallBack = CallBack;
    return &ReceiveCharacter;
}