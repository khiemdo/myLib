/****************************************************************/
/** @file:      cDebugUart
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		Nov 29, 2015
 *  @version:	1.0
 *  @brief:     UARTDebug Interface, it includes.
 *              _UartDebugConfigX
 *              _UartPrintf
 *              _ReadDebugUart
 *  @note:       this driver dont use DMA for rx.
 *      DMA comes only handy when the communication has some certain protocol like canbux
 *
 ****************************************************************/
#ifndef _cDebugUart_h
#define _cDebugUart_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"


#if DEBUGUART_ID == 6
	#define DEBUGUART_ADDR	USART6
#elif DEBUGUART_ID == 1
	#define DEBUGUART_ADDR	USART1
#elif DEBUGUART_ID == 3
	#define DEBUGUART_ADDR	USART3
#elif DEBUGUART_ID == 2
	#define DEBUGUART_ADDR	USART2
#endif

void UartDebugConfig0(void);
UART_HandleTypeDef * GetUartDebugPtr(void);
int32_t IsDebugUartWritable();
int32_t IsDebugUartAvailableToWrite();
int32_t UDebugPrintf(char * data, ...);
int32_t UDebugSendRaw(char * data, int32_t lengthOfMsg);
int IsDebugUartAvailableToRead();
int IsDebugUartReadable();
int8_t ReadDebugUart(void);
void HAL_UARTDebug_RxCpltCallback(UART_HandleTypeDef * huart);
void HAL_UARTDebug_TxCpltCallback(UART_HandleTypeDef * huart);
void UARTDebug_TBuffControllerLoop(UART_HandleTypeDef * huart);

#ifdef __cplusplus
}
#endif
#endif
