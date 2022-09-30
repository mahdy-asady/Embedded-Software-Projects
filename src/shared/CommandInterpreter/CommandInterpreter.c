#include <stdio.h>
#include "FunctionPointers.h"

void CommandsRun(char *Command) {
    printf("Command: %s\n", Command);
}

voidFunctionPointer1ParamCharPointer CommandsInit(void) {
    return &CommandsRun;
}