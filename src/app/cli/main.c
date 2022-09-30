#include <stdio.h>
#include "mcu.h"
#include "USART.h"

#include "CliInterface/CliInterface.h"
#include "CommandInterpreter/CommandInterpreter.h"

int main(void)
{
    mcuInit();
    USART_init_printf();
    voidFunctionPointer1ParamCharPointer CommandRunner = CommandsInit();
    voidFunctionPointer1ParamCharPointer UartReceiver = CliInterfaceInit(CommandRunner);
    USART_init_receive(UartReceiver);
    
    while(1);
}
