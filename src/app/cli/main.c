#include <stdio.h>
#include "mcu.h"
#include "USART.h"

#include "CliInterface/CliInterface.h"
#include "CommandInterpreter/CommandInterpreter.h"

int main(void)
{
    mcuInit();
    USART_init_printf();
    USART_init_receive(CliInterfaceInit(&RunCommand));
    
    while(1);
}
