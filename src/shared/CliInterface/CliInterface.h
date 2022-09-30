#ifndef __CLIINTERFACE_h__
#define __CLIINTERFACE_h__
#include <stdint.h>
#include "FunctionPointers.h"

//this function recieves a pointer to the function CallBack. so when command got ready it will be called!
// also returns a pointer to a function that is responsible for getting characters and process them!
voidFunctionPointer1ParamCharPointer CliInterfaceInit(voidFunctionPointer1ParamCharPointer CallBack);

#endif