#ifndef __COMMAND_INTERPRETER_h__
#define __COMMAND_INTERPRETER_h__
#include "FunctionPointers.h"

voidFunctionPointer1ParamCharPointer CommandsInit(void);

void CommandsRegister(char *CommandText, voidFunctionPointer2ParamCharPointer CommandHook, char *HookParams);

#endif