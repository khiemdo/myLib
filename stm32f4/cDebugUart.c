#include "main.h"
FILENUM(1);

#include "cDebugUart.h"
#include "cUartPort.h"
#include "cRingBuffer.h"
#include "cAssert.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#define TX_BUFFER_SIZE 256
#define RX_BUFFER_SIZE 32

UART_HandleTypeDef huartDebugPort;
DMA_HandleTypeDef hdmatx;
DMA_HandleTypeDef hdmarx;
int8_t txMsgBuffer[TX_BUFFER_SIZE];
int8_t rxMsgBuffer[RX_BUFFER_SIZE];
RingBuffer rxDebugDataRingBuffer;
RingBuffer txDebugDataRingBuffer;
RingBuffer txDebugLengthRingBuffer;
int8_t rxDebugDataRingBufferBuff[RX_BUFFER_SIZE];
int8_t txDebugDataRingBufferBuff[RX_BUFFER_SIZE];
int8_t txDebugLengthRingBufferPtrBuff[RX_BUFFER_SIZE];
volatile int32_t mutex_HAL_UARTDebug_TxCpltCallback = 0;

/****************************************************************/
/** @brief: config uartDebug. here it uses uartPort3
 ****************************************************************/
void UartDebugConfig0(void) {

	UART_HandleTypeDef * huart = &huartDebugPort;
	REQUIRE(huart);
	memset(huart,sizeof(UART_HandleTypeDef),0);

	RingBuffer * rxDebugDataRingBufferPtr = &rxDebugDataRingBuffer;
	RingBuffer * txDebugDataRingBufferPtr = &txDebugDataRingBuffer;
	RingBuffer * txDebugLengthRingBufferPtr = &txDebugLengthRingBuffer;

	RingBufferConfig(rxDebugDataRingBufferPtr, rxDebugDataRingBufferBuff, RX_BUFFER_SIZE, sizeof(int8_t));
	RingBufferConfig(txDebugDataRingBufferPtr, txDebugDataRingBufferBuff, TX_BUFFER_SIZE, sizeof(int8_t));
	RingBufferConfig(txDebugLengthRingBufferPtr, txDebugLengthRingBufferPtrBuff, TX_BUFFER_SIZE, sizeof(int8_t));
;
#if DEBUGUART_ID == 6
	Uart6PortConfig(huart);
#elif DEBUGUART_ID == 1
	Uart1PortConfig(huart);
#elif DEBUGUART_ID == 3
	Uart3PortConfig(huart, &hdmatx, &hdmarx);
#elif DEBUGUART_ID == 2
	Uart2PortConfig(huart);
#endif
	huart->pRxBuffPtr = (uint8_t *) rxMsgBuffer;
	huart->pTxBuffPtr = (uint8_t *) txMsgBuffer;
	HAL_UART_Receive_IT(huart, (uint8_t *) (huart->pRxBuffPtr), 1);

}
/****************************************************************/
/** @brief: get the huart ptr
 ****************************************************************/
UART_HandleTypeDef * GetUartDebugPtr(void) {
	return &huartDebugPort;
}
/****************************************************************/
/** @brief: check inside the Ring buffer txDebugLengthRingBuffer contain any package
 ****************************************************************/
int32_t CheckHasMsg() {
	return GetNumberByteUsedOfRBuffer(&txDebugDataRingBuffer) > 0;
}
int32_t IsDebugUartWritable(){
	return GetNumberByteLeftOfRBuffer(&txDebugDataRingBuffer);
}
int32_t IsDebugUartAvailableToWrite(){
	return GetNumberByteLeftOfRBuffer(&txDebugDataRingBuffer) != 0;
}
/****************************************************************/
/** @brief: save a msg into buffer using PushRingBuffer
 ****************************************************************/
void PushAMsgToTxRbuff(int8_t * buff, int32_t length) {
	PushRingBuffer(&txDebugDataRingBuffer, &length);
	while (length--) {
		//if has space in ring buffer
		REQUIRE(GetNumberByteLeftOfRBuffer(&txDebugDataRingBuffer) != 0);
		PushRingBuffer(&txDebugDataRingBuffer, buff);
		buff++;
	}
}
/****************************************************************/
/** @brief: pop a msg into buffer using PushRingBuffer
 ****************************************************************/
int32_t PopAMsgFromTxBuff(int8_t * buff) {
	int32_t length = 0;

	PopRingBuffer(&txDebugDataRingBuffer, &length);
	int8_t * buffPtr = buff;
	int32_t index = length;
	while (index--) {
		PopRingBuffer(&txDebugDataRingBuffer, buffPtr);
		buffPtr++;
	}
	return length;
}
/****************************************************************/
/** @brief: check UartDMA
 * @return: true-> uartDMA s ready to send
 ****************************************************************/
int32_t IsUartDMAReady(UART_HandleTypeDef * huart) {
	int32_t state = HAL_UART_GetState(huart);
	return (state == HAL_UART_STATE_READY || state == HAL_UART_STATE_BUSY_RX);
}
/****************************************************************/
/** @brief: send msg to serial
 ****************************************************************/
int32_t UDebugPrintf(char * data, ...) {
	UART_HandleTypeDef * huart = GetUartDebugPtr();
	int32_t ret = -1;
	va_list args;

	va_start(args, data);
	REQUIRE(strlen((const char*)txMsgBuffer) < TX_BUFFER_SIZE);
	int32_t lengthOfMsg = vsnprintf((char*) txMsgBuffer, TX_BUFFER_SIZE,
			(const char*) data, args);
	va_end(args);
	if (IsUartDMAReady(huart)) {
		int32_t txRBuffState = CheckHasMsg();
		if (txRBuffState == false) {
			int res = HAL_UART_Transmit_DMA(huart, (uint8_t *) txMsgBuffer,
					lengthOfMsg);
			(void) res;
			ret = 0;
		} else if (txRBuffState == true) {
			PushAMsgToTxRbuff(txMsgBuffer, lengthOfMsg);
			ret = 1;
		}
	} else {
		PushAMsgToTxRbuff(txMsgBuffer, lengthOfMsg);
		ret = 2;
	}
	return ret;
} /* UDebugPrintf */

int32_t UDebugSendRaw(char * data, int32_t lengthOfMsg) {
	UART_HandleTypeDef * huart = GetUartDebugPtr();
	int32_t ret = -1;

	if (IsUartDMAReady(huart)) {
		int32_t txRBuffState = CheckHasMsg();
		if (txRBuffState == false) {
			HAL_UART_Transmit_DMA(huart, (uint8_t *) data, lengthOfMsg);
			ret = 0;
		} else if (txRBuffState == true) {
			PushAMsgToTxRbuff((int8_t*) data, lengthOfMsg);
			ret = 1;
		}
	} else {
		PushAMsgToTxRbuff((int8_t*) data, lengthOfMsg);
		ret = 2;
	}
	return ret;
}

void HAL_UARTDebug_TxCpltCallback(UART_HandleTypeDef * huart) {
	if (mutex_HAL_UARTDebug_TxCpltCallback == 0) {
		mutex_HAL_UARTDebug_TxCpltCallback = 1;
		if (CheckHasMsg()) {
			int32_t lengthOfMsg = PopAMsgFromTxBuff(txMsgBuffer);
			HAL_UART_Transmit_DMA(huart, (uint8_t *) txMsgBuffer, lengthOfMsg);
		}
		mutex_HAL_UARTDebug_TxCpltCallback = 0;
	} else if (mutex_HAL_UARTDebug_TxCpltCallback == 1) {
		int i = 0;
		i++;
	}

}
void UARTDebug_TBuffControllerLoop(UART_HandleTypeDef * huart) {
	if (IsUartDMAReady(huart)) {
		HAL_UARTDebug_TxCpltCallback(huart);
	}
}

int IsDebugUartAvailableToRead() {
	return GetNumberByteUsedOfRBuffer(&rxDebugDataRingBuffer) != 0;
}
int IsDebugUartReadable(){
	return GetNumberByteUsedOfRBuffer(&rxDebugDataRingBuffer);
}
int8_t ReadDebugUart(void) {
	int8_t ret = '\0';

	int32_t counts = GetNumberByteUsedOfRBuffer(&rxDebugDataRingBuffer);

	if (counts != 0) {
		PopRingBuffer(&rxDebugDataRingBuffer, &ret);
	}

	return ret;
}
void HAL_UARTDebug_RxCpltCallback(UART_HandleTypeDef * huart) {
	PushRingBuffer(&rxDebugDataRingBuffer, (--(huart->pRxBuffPtr)));
	HAL_UART_Receive_IT(huart, (uint8_t *) (huart->pRxBuffPtr), 1);
}
