#include "GPIO.h"
#include "util.h"

/* Includes ------------------------------------------------------------------*/
#ifdef STM32F107xC
#include "ErrorHandler.h"


/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
#endif

int main(void)
{
  InitHardWare();

  PORTS GPIO_Port;
  PINS GPIO_Pin;

  #ifdef atmega16a
    GPIO_Port = PORT_C;
    GPIO_Pin = PIN_07;
  #elif defined STM32F107xC
    GPIO_Port = PORT_D;
    GPIO_Pin = PIN_02;
  #endif
  GPIO_InitPin(GPIO_Port, GPIO_Pin, PinDirectionOutput);
  GPIO_WritePin(GPIO_Port, GPIO_Pin, PinHigh);
  
  while (1)
  {
    delay_ms(500);
    GPIO_TogglePin(GPIO_Port, GPIO_Pin);
  }
}
