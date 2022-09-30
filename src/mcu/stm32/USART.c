#include "ErrorHandler.h"
#include "retarget.h"
#include "FunctionPointers.h"

UART_HandleTypeDef huart1;
static uint8_t ReceivedChar;
static voidFnPtr1ParamCharP fnCallBack;

static void MX_USART1_UART_Init(void)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = BAUD;    //comming from compiler directive
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
}

void USART_init_printf(void) {
    MX_USART1_UART_Init();
    RetargetInit(&huart1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
    HAL_UART_Receive_IT(&huart1, &ReceivedChar, 1);
    if(ReceivedChar == '\r')
        ReceivedChar = '\n';
    (*fnCallBack)((char*)&ReceivedChar);
}

void USART_init_receive(voidFnPtr1ParamCharP CallBack) {
    fnCallBack = CallBack;
    HAL_UART_Receive_IT (&huart1, &ReceivedChar, 1);
}