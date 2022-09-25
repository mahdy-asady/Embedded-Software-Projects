#include "ErrorHandler.h"

#include "GPIO.h"

void GPIO_InitPin(PORTS PortNumber, PINS PinNumber, PinDirections PinDirection) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);

    /*Configure GPIO pin : PD2 */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void GPIO_WritePin(PORTS PortNumber, PINS PinNumber, PinValues PinValue) {
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, PinValue);
}


void GPIO_TogglePin(PORTS PortNumber, PINS PinNumber) {
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_2);
}