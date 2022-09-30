#ifndef __USART_h__
#define __USART_h__
#include "FunctionPointers.h"

void USART_init_printf(void);

void USART_init_receive(voidFunctionPointer1ParamCharPointer CallBack);
#endif