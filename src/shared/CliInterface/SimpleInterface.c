#include <stdio.h>
#include "CliInterface.h"

static void (*fnCommandCallBack)(char *);
static char Command[100] = {0};
static int StringPosition = 0;


void PrintLogo(void);
void ReceiveCharacter(uint8_t*);

CharReceivingHook CliInterfaceInit(void (*CallBack)(char *)) {
    fnCommandCallBack = CallBack;
    return &ReceiveCharacter;
}

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

void PrintLogo(void) {
    printf("\n\n");
    printf( " __  __  ____   __  _____     __    __   __   __ __  ____  _____     __   __    __    ____  _____   \n"
            "|  \\/  ||_  _| '_ ||_  _ \\   '  `  '_ | '  ` |  |  ||    ||_  _ \\   '  ` |  |  |  |  |  _ ||_  _ \\  \n"
            " |    |   ||  /. \\|  ||_) | / .. \\/. \\|/ .. \\ | \\|| |/||\\|  ||_) | / .. \\ ||    ||    || \\|  ||_) | \n"
            " ||\\/||   ||  ||     | _ /  ||  ||||   ||  || || ||   ||    | _ /  ||  || ||    ||    | |    | _ /  \n"
            " ||  ||  _||_ \\`_.\\ _|| \\ \\ \\ `' /\\`_.\\\\ `' / ||\\ |   ||   _|| \\ \\ \\ `' / ||_/| ||_/| ||_/| _|| \\ \\ \n"
            "|______||____| .__'|___||__| .__.  .__' .__. |__|__| |__| |___||__| .__. |____||____||____||___||__|\n"
            "                                        __  __    ____ \n"
            "                                       '  ||  |  |_  _|\n"
            "                                      /.'\\| ||     ||  \n"
            "                                      ||    ||     ||  \n"
            "                                      \\`..\\ ||_/| _||_ \n"
            "                                       .__'|____||____|\n");
    printf("\n\nFor help type ?\n\n");
}