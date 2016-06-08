 #include "main.h"
FILENUM(11);

#include "cUartPort.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "cAssert.h"

/****************************************************************/
/** @brief: just configure gpio of uart
 *  @details: used in Uart3Debug_Init
 ****************************************************************/
void Uart3GPIOInit(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	__GPIOB_CLK_ENABLE()
	;
	/**USART3 GPIO Configuration
	 PB10     ------> USART3_TX
	 PB11     ------> USART3_RX
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void Uart2GPIOInit(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	__GPIOA_CLK_ENABLE()
	;
	/**USART3 GPIO Configuration
	 Pa2     ------> USART3_TX
	 Pa3     ------> USART3_RX
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/****************************************************************/
/** @brief: just configure DMA of uart
 *  @details: used in Uart3Debug_Init
 ****************************************************************/
void Uart3DMAInit(UART_HandleTypeDef * huart) {
	__HAL_RCC_DMA1_CLK_ENABLE()
	;

    huart->hdmatx = (DMA_HandleTypeDef *)calloc(1, sizeof(DMA_HandleTypeDef));
    REQUIRE(huart->hdmatx != 0);
    huart->hdmatx->Instance = DMA1_Channel2;
    huart->hdmatx->Init.Direction = DMA_MEMORY_TO_PERIPH;
    huart->hdmatx->Init.PeriphInc = DMA_PINC_DISABLE;
    huart->hdmatx->Init.MemInc = DMA_MINC_ENABLE;
    huart->hdmatx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    huart->hdmatx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    huart->hdmatx->Init.Mode = DMA_NORMAL;
    huart->hdmatx->Init.Priority = DMA_PRIORITY_LOW;
    HAL_DMA_Init(huart->hdmatx);
    huart->hdmatx->Parent = huart;

	HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
} /* Uart3DMAInit */

void Uart2DMAInit(UART_HandleTypeDef* huart) {
	__HAL_RCC_DMA1_CLK_ENABLE()
	;

    huart->hdmatx = (DMA_HandleTypeDef *)calloc(1, sizeof(DMA_HandleTypeDef));
    REQUIRE(huart->hdmatx != 0);
    huart->hdmatx->Instance = DMA1_Channel7;
    huart->hdmatx->Init.Direction = DMA_MEMORY_TO_PERIPH;
    huart->hdmatx->Init.PeriphInc = DMA_PINC_DISABLE;
    huart->hdmatx->Init.MemInc = DMA_MINC_ENABLE;
    huart->hdmatx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    huart->hdmatx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    huart->hdmatx->Init.Mode = DMA_NORMAL;
    huart->hdmatx->Init.Priority = DMA_PRIORITY_LOW;
    HAL_DMA_Init(huart->hdmatx);
    huart->hdmatx->Parent = huart;

	HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
}

void Uart3NVICInit(UART_HandleTypeDef * huart){
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
}

void Uart2NVICInit(UART_HandleTypeDef* huart) {
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}

/****************************************************************/
/** @brief: just to config UART registers of Uart
 *  @details: used in Uart3Debug_Init
 ****************************************************************/
void Uart3UARTInit(UART_HandleTypeDef * huart) {
    __USART3_CLK_ENABLE();
    huart->Instance = USART3;
    huart->Init.BaudRate = 115200;
    huart->Init.WordLength = UART_WORDLENGTH_8B;
    huart->Init.StopBits = UART_STOPBITS_1;
    huart->Init.Parity = UART_PARITY_NONE;
    huart->Init.Mode = UART_MODE_TX_RX;
    huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart->Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(huart);
    __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
}

void Uart2UARTInit(UART_HandleTypeDef* huart) {
	__USART2_CLK_ENABLE()
	;
	huart->Instance = USART2;
	huart->Init.BaudRate = 115200;
	huart->Init.WordLength = UART_WORDLENGTH_8B;
	huart->Init.StopBits = UART_STOPBITS_1;
	huart->Init.Parity = UART_PARITY_NONE;
	huart->Init.Mode = UART_MODE_TX_RX;
	huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart->Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(huart);
	__HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
	__HAL_UART_ENABLE_IT(huart, UART_IT_TC);
}

/****************************************************************/
/** @brief: call dma,gpio,uart config
 *  @details: after call Uart3PortConfig, all the hardware configuration should be set up properly
 ****************************************************************/
void Uart3PortConfig(UART_HandleTypeDef * huart) {
    Uart3GPIOInit();
    Uart3NVICInit(huart);
    Uart3DMAInit(huart);
    Uart3UARTInit(huart);
    huart->Instance = USART3;
    HAL_UART_Receive_IT(huart, (uint8_t *)(huart->pRxBuffPtr), 1);
}

void Uart2PortConfig(UART_HandleTypeDef* huart) {
	huart->Instance = USART2;
	Uart2GPIOInit();
	Uart2NVICInit(huart);
	Uart2DMAInit(huart);
	Uart2UARTInit(huart);

	HAL_UART_Receive_IT(huart, (uint8_t*) (huart->pRxBuffPtr), 1);
}
