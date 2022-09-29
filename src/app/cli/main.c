#include <stdio.h>
#include "mcu.h"
#include "USART.h"

void ReceiveUartCharacter(uint8_t*);

char *Command;

int main(void)
{
    mcuInit();
    USART_init_printf();
    USART_init_receive(&ReceiveUartCharacter);
    while(1);
}

// Receive User entered commands
void ReceiveUartCharacter(uint8_t *Char) {

    printf("%s", Char);
}