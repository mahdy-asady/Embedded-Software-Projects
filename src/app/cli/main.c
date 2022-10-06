#include <stdio.h>
#include "mcu.h"
#include "USART.h"
#include "debug.h"

#include "CliInterface/CliInterface.h"
#include "CommandInterpreter/CommandInterpreter.h"
#include "GPIOModule.h"
#include "TimerModule.h"

int main(void)
{
    mcuInit();
    USART_init_printf();
    voidFnPtr1ParamCharP CommandRunner = CommandsInit();
    /*  Calling Modules  */
    GPIOModuleInit();
    TimerModuleInit();
    /*  End Calling Modules */
    voidFnPtr1ParamCharP UartReceiver = CliInterfaceInit(CommandRunner);
    USART_init_receive(UartReceiver);
    
    while(1);
}
