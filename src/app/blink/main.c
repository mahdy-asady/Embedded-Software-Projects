#include "GPIO.h"
#include "mcu.h"
#include "GPIO.h"

PORTS GPIO_Port;
PINS GPIO_Pin;

int main(void)
{
  mcuInit();
  getLedInfo(&GPIO_Port, &GPIO_Pin);
  GPIO_InitPin(GPIO_Port, GPIO_Pin, PinDirectionOutput);
  GPIO_WritePin(GPIO_Port, GPIO_Pin, PinHigh);
  
  while (1)
  {
    delay_ms(500);
    GPIO_TogglePin(GPIO_Port, GPIO_Pin);
  }
}
