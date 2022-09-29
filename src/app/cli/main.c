#include <stdio.h>
#include "mcu.h"
#include "USART.h"

#include "CliInterface/CliInterface.h"


void ReceiveCommand(char*);
void PrintLogo(void);

char *Command;

int main(void)
{
    mcuInit();
    USART_init_printf();
    USART_init_receive(CliInterfaceInit(&ReceiveCommand));
    PrintLogo();
    






    
    while(1);
}

// Receive User entered commands
void ReceiveCommand(char *Char) {

    printf("%s\n", Char);
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
    printf("\n\n");
}