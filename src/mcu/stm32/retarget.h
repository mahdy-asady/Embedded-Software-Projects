#ifndef _RETARGET_H__
#define _RETARGET_H__

#include "stm32f1xx_hal.h"
#include <sys/stat.h>

#ifdef HAL_UART_MODULE_ENABLED
void RetargetInit(UART_HandleTypeDef *huart);
#endif
int _isatty(int fd);
int _write(int fd, char* ptr, int len);
int _close(int fd);
int _lseek(int fd, int ptr, int dir);
int _read(int fd, char* ptr, int len);
int _fstat(int fd, struct stat* st);

#endif //#ifndef _RETARGET_H__