#ifndef __USART_h__
#define __USART_h__

void USART_init_printf(void);

void USART_init_receive(void (*CallBack)(char *));
#endif