/****************************************************************/
/** @file       cUartPort
 *  @author		DO HOANG DUY KHIEM
 *  @date		Nov 29, 2015
 *  @version	1.0
 *  @brief      configure the uartHardware
 *
 *  @note
 *
 ****************************************************************/
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
	__GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void Uart6GPIOInit(void) {
	__GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
void Uart1GPIOInit(void) {
	__GPIOA_CLK_ENABLE()
	;
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void Uart2GPIOInit(void) {
	__GPIOA_CLK_ENABLE()
	;
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
/****************************************************************/
/** @brief: just configure DMA of uart
 *  @details: used in Uart3Debug_Init
 ****************************************************************/
void Uart3DMAInit(UART_HandleTypeDef* huart) {
	__DMA1_CLK_ENABLE();

	huart->hdmatx = (DMA_HandleTypeDef*) calloc(1, sizeof(DMA_HandleTypeDef));
	REQUIRE(huart->hdmatx!=0);
	huart->hdmatx->Instance = DMA1_Stream3;
	huart->hdmatx->Init.Channel = DMA_CHANNEL_4;
	huart->hdmatx->Init.Direction = DMA_MEMORY_TO_PERIPH;
	huart->hdmatx->Init.PeriphInc = DMA_PINC_DISABLE;
	huart->hdmatx->Init.MemInc = DMA_MINC_ENABLE;
	huart->hdmatx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	huart->hdmatx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	huart->hdmatx->Init.Mode = DMA_NORMAL;
	huart->hdmatx->Init.Priority = DMA_PRIORITY_LOW;
	huart->hdmatx->Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	huart->hdmatx->Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	huart->hdmatx->Init.MemBurst = DMA_MBURST_SINGLE;
	huart->hdmatx->Init.PeriphBurst = DMA_PBURST_SINGLE;
	HAL_DMA_Init(huart->hdmatx);
	huart->hdmatx->Parent = huart;

	HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
}
void Uart6DMAInit(UART_HandleTypeDef* huart) {
	__DMA2_CLK_ENABLE();

	huart->hdmatx = (DMA_HandleTypeDef*) calloc(1, sizeof(DMA_HandleTypeDef));
	REQUIRE(huart->hdmatx!=0);
	huart->hdmatx->Instance = DMA2_Stream6;
	huart->hdmatx->Init.Channel = DMA_CHANNEL_5;
	huart->hdmatx->Init.Direction = DMA_MEMORY_TO_PERIPH;
	huart->hdmatx->Init.PeriphInc = DMA_PINC_DISABLE;
	huart->hdmatx->Init.MemInc = DMA_MINC_ENABLE;
	huart->hdmatx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	huart->hdmatx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	huart->hdmatx->Init.Mode = DMA_NORMAL;
	huart->hdmatx->Init.Priority = DMA_PRIORITY_LOW;
	huart->hdmatx->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	huart->hdmatx->Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	huart->hdmatx->Init.MemBurst = DMA_MBURST_SINGLE;
	huart->hdmatx->Init.PeriphBurst = DMA_PBURST_SINGLE;
	HAL_DMA_Init(huart->hdmatx);
	huart->hdmatx->Parent = huart;

	HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);
}
void Uart1DMAInit(UART_HandleTypeDef* huart) {
	__DMA2_CLK_ENABLE()
	;

	huart->hdmatx = (DMA_HandleTypeDef*) calloc(1, sizeof(DMA_HandleTypeDef));
	REQUIRE(huart->hdmatx!=0);
	huart->hdmatx->Instance = DMA2_Stream7;
	huart->hdmatx->Init.Channel = DMA_CHANNEL_4;
	huart->hdmatx->Init.Direction = DMA_MEMORY_TO_PERIPH;
	huart->hdmatx->Init.PeriphInc = DMA_PINC_DISABLE;
	huart->hdmatx->Init.MemInc = DMA_MINC_ENABLE;
	huart->hdmatx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	huart->hdmatx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	huart->hdmatx->Init.Mode = DMA_NORMAL;
	huart->hdmatx->Init.Priority = DMA_PRIORITY_LOW;
	huart->hdmatx->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	huart->hdmatx->Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	huart->hdmatx->Init.MemBurst = DMA_MBURST_SINGLE;
	huart->hdmatx->Init.PeriphBurst = DMA_PBURST_SINGLE;
	HAL_DMA_Init(huart->hdmatx);
	huart->hdmatx->Parent = huart;

	HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
}
void Uart2DMAInit(UART_HandleTypeDef* huart) {
	__DMA1_CLK_ENABLE()
	;

	huart->hdmatx = (DMA_HandleTypeDef*) calloc(1, sizeof(DMA_HandleTypeDef));
	REQUIRE(huart->hdmatx!=0);
	huart->hdmatx->Instance = DMA1_Stream6;
	huart->hdmatx->Init.Channel = DMA_CHANNEL_4;
	huart->hdmatx->Init.Direction = DMA_MEMORY_TO_PERIPH;
	huart->hdmatx->Init.PeriphInc = DMA_PINC_DISABLE;
	huart->hdmatx->Init.MemInc = DMA_MINC_ENABLE;
	huart->hdmatx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	huart->hdmatx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	huart->hdmatx->Init.Mode = DMA_NORMAL;
	huart->hdmatx->Init.Priority = DMA_PRIORITY_LOW;
	huart->hdmatx->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	huart->hdmatx->Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	huart->hdmatx->Init.MemBurst = DMA_MBURST_SINGLE;
	huart->hdmatx->Init.PeriphBurst = DMA_PBURST_SINGLE;
	HAL_DMA_Init(huart->hdmatx);
	huart->hdmatx->Parent = huart;

	HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}

void Uart3NVICInit(UART_HandleTypeDef* huart){
		HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART3_IRQn);
}
void Uart6NVICInit(UART_HandleTypeDef* huart){
		HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART6_IRQn);
}
void Uart1NVICInit(UART_HandleTypeDef* huart) {
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
}
void Uart2NVICInit(UART_HandleTypeDef* huart) {
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}
/****************************************************************/
/** @brief: just to config UART registers of Uart
 *  @details: used in Uart3Debug_Init
 ****************************************************************/
void Uart3UARTInit(UART_HandleTypeDef* huart) {
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
void Uart6UARTInit(UART_HandleTypeDef* huart) {
	__USART6_CLK_ENABLE();
	huart->Instance = USART6;
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
void Uart1UARTInit(UART_HandleTypeDef* huart) {
	__USART1_CLK_ENABLE()
	;
	huart->Instance = USART1;
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
}
/****************************************************************/
/** @brief: call dma,gpio,uart config
 *  @details: after call Uart3PortConfig, all the hardware configuration should be set up properly
 ****************************************************************/
void Uart3PortConfig(UART_HandleTypeDef* huart) {
	Uart3GPIOInit();
	Uart3NVICInit(huart);
	Uart3DMAInit(huart);
	Uart3UARTInit(huart);
	huart->Instance = USART3;
}
void Uart6PortConfig(UART_HandleTypeDef* huart) {
	Uart6GPIOInit();
	Uart6NVICInit(huart);
	Uart6DMAInit(huart);
	Uart6UARTInit(huart);
	huart->Instance = USART6;
}
void Uart1PortConfig(UART_HandleTypeDef* huart) {
	Uart1GPIOInit();
	Uart1NVICInit(huart);
	Uart1DMAInit(huart);
	Uart1UARTInit(huart);
	huart->Instance = USART1;
}
void Uart2PortConfig(UART_HandleTypeDef* huart) {
	huart->Instance = USART2;
	Uart2GPIOInit();
	Uart2NVICInit(huart);
	Uart2DMAInit(huart);
	Uart2UARTInit(huart);
}
