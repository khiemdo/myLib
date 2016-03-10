/****************************************************************/
/** @file:      cUartPort.h
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		Dec 27, 2015
 *  @version:	1.0
 *  @brief:     configure the uart harware
 *
 *  @note:
 *
 ****************************************************************/

#ifndef _cUartPort_h
#define _cUartPort_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void Uart3PortConfig(UART_HandleTypeDef* huart);
void Uart6PortConfig(UART_HandleTypeDef* huart);
void Uart1PortConfig(UART_HandleTypeDef* huart);
void Uart2PortConfig(UART_HandleTypeDef* huart);

#ifdef __cplusplus
}
#endif
#endif
