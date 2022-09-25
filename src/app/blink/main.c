#include "GPIO.h"
#include "SystemClock.h"

#ifdef atmega16a
#include <util/delay.h>                // for _delay_ms()
#endif


/* Includes ------------------------------------------------------------------*/
#ifdef STM32F107xC
#include "ErrorHandler.h"


/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
#endif

int main(void)
{
    #ifdef STM32F107xC

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  #endif
  SystemClock_Config();

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
  #ifdef atmega16a
    int duration = 500;
  #elif defined STM32F107xC
    int duration = 2000000;
  #endif
  
  
  while (1)
  {
    #ifdef atmega16a
        _delay_ms(duration);
    #elif defined STM32F107xC
        for(int i = 0; i< duration; i++);
    #endif
    
    GPIO_TogglePin(GPIO_Port, GPIO_Pin);
  }
}










#ifdef STM32F107xC

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

#endif