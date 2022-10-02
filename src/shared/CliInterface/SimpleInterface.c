#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "FunctionPointers.h"
#include "banned.h"

static voidFnPtr1ParamCharP fnCommandCallBack;
static char Command[100] = {0};
static int StringPosition = 0;


void PrintLogo(void);
void ReceiveCharacter(char*);
void InlineTrim(char *String);

voidFnPtr1ParamCharP CliInterfaceInit(voidFnPtr1ParamCharP CallBack) {
    PrintLogo();

    fnCommandCallBack = CallBack;
    return &ReceiveCharacter;
}

void ReceiveCharacter(char *Char) {

    printf("%s", Char);
    
    if(*Char == '\n') {
        Command[StringPosition] = '\0';
        InlineTrim(Command);
        if(strcmp(Command, "") != 0)
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


void InlineTrim(char *String)
{
    char *Start = String;
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*Start)) Start++;

    if(*Start == 0) {  // All spaces?
        String[0] = 0;
        return;
    }

    // Trim trailing space
    end = Start + strlen(Start) - 1;
    while(end > Start && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    // Move Start string to start of String
    while(*Start != 0)
        *String++ = *Start++;
    *String = 0;
}