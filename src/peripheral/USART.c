#include <avr/io.h>
#include <stdio.h>

static int uart_putchar(char c, FILE *stream);


static int uart_putchar(char c, FILE *stream)
{
    if (c == '\n')
        uart_putchar('\r', stream);
    loop_until_bit_is_set(UCSRA, UDRE);
    UDR = c;
    return 0;
}


static void USART_init(void) {
    #include <util/setbaud.h>

    UBRRH = (unsigned char) (UBRR_VALUE >> 8);
    UBRRL = (unsigned char) UBRR_VALUE;
    #if USE_2X
        UCSRA |= (1 << U2X);
    #else
        UCSRA &= ~(1 << U2X);
    #endif
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0); 
}

static void use_USART_as_stdout(void) {
    static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &mystdout;
}



void USART_init_printf(void) {
    USART_init();
    use_USART_as_stdout();
}