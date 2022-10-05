#ifndef __COMMAND_INTERPRETER_h__
#define __COMMAND_INTERPRETER_h__
#include "FunctionPointers.h"

#define COMMANDS_MAX_TOKENS_LENGTH 100

typedef void (*voidFnPtr3ParamCharPArrIntCharP)(char [][COMMANDS_MAX_TOKENS_LENGTH], size_t, char*);

voidFnPtr1ParamCharP CommandsInit(void);

void CommandsRegister(char *CommandText, voidFnPtr3ParamCharPArrIntCharP CommandHook, char *HookParams);

void CommandsRun(char*);

#endif