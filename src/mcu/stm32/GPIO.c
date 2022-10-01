#include "stm32f1xx_hal.h"
#include "GPIO.h"

static GPIO_TypeDef * GetPort(PORTS PortNumber) {
    switch (PortNumber)
    {
    case PORT_A:
        return GPIOA;
    case PORT_B:
        return GPIOB;
    case PORT_C:
        return GPIOC;
    case PORT_D:
        return GPIOD;
    case PORT_E:
        return GPIOE;
    }
}

void GPIO_InitPin(PORTS PortNumber, PINS PinNumber, PinDirections PinDirection) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GetPort(PortNumber), PinNumber, GPIO_PIN_RESET);

    /*Configure GPIO pin : PD2 */
    GPIO_InitStruct.Pin = PinNumber;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GetPort(PortNumber), &GPIO_InitStruct);
}

void GPIO_WritePin(PORTS PortNumber, PINS PinNumber, PinValues PinValue) {
      HAL_GPIO_WritePin(GetPort(PortNumber), PinNumber, PinValue);
}

int GPIO_ReadPin(PORTS PortNumber, PINS PinNumber) {
    return HAL_GPIO_ReadPin(GetPort(PortNumber), PinNumber);
}


void GPIO_TogglePin(PORTS PortNumber, PINS PinNumber) {
    HAL_GPIO_TogglePin(GetPort(PortNumber), PinNumber);
}