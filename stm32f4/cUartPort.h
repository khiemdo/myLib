#ifndef	_cUartPort_h
#define _cUartPort_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void Uart3PortConfig(UART_HandleTypeDef* huart,DMA_HandleTypeDef* hdmatx,DMA_HandleTypeDef* hdmarx);
void Uart6PortConfig(UART_HandleTypeDef* huart,DMA_HandleTypeDef* hdmatx,DMA_HandleTypeDef* hdmarx);
void Uart1PortConfig(UART_HandleTypeDef* huart,DMA_HandleTypeDef* hdmatx,DMA_HandleTypeDef* hdmarx);
void Uart2PortConfig(UART_HandleTypeDef* huart,DMA_HandleTypeDef* hdmatx,DMA_HandleTypeDef* hdmarx);

#ifdef __cplusplus
}
#endif
#endif
