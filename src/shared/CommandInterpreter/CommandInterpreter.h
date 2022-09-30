#ifndef __COMMAND_INTERPRETER_h__
#define __COMMAND_INTERPRETER_h__
#include "FunctionPointers.h"

voidFnPtr1ParamCharP CommandsInit(void);

void CommandsRegister(char *CommandText, voidFnPtr2ParamCharPPCharP CommandHook, char *HookParams);

#endif