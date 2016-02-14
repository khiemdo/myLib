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

#define TX_BUFFER_SIZE 				512
#define TXLENGTH_BUFFER_SIZE 	32
#define RX_BUFFER_SIZE 				32

UART_HandleTypeDef * huartDebugPort;
int8_t txDMABuffer[TX_BUFFER_SIZE];
int8_t txMsg[TX_BUFFER_SIZE];
int8_t rxDMABuffer[RX_BUFFER_SIZE];
RingBuffer * rxDebugDataRingBuffer;
RingBuffer * txDebugDataRingBuffer;
RingBuffer * txDebugLengthRingBuffer;
volatile int32_t mutex_HAL_UARTDebug_TxCpltCallback = 0;
volatile int32_t rearmUartReceiveIT = 0;//0=dont need,1=wait for mainloop to rearm
/****************************************************************/
/** @brief: config uartDebug. here it uses uartPort3
 ****************************************************************/
void UartDebugConfig0(void) {
	UART_HandleTypeDef* huart = calloc(1, sizeof(UART_HandleTypeDef));
	REQUIRE(huart!=0);
	huartDebugPort = huart;//huartDebugPort must be defined as early as possible bf enable interrupt
	huart->pRxBuffPtr = (unsigned char*) rxDMABuffer;
	huart->pTxBuffPtr = (unsigned char*) txDMABuffer;
	
	rxDebugDataRingBuffer = RingBufferConstructor();
	REQUIRE(rxDebugDataRingBuffer != 0);
	RingBufferConfig(rxDebugDataRingBuffer, RX_BUFFER_SIZE, sizeof(int8_t));
	txDebugDataRingBuffer = RingBufferConstructor();
	REQUIRE(txDebugDataRingBuffer != 0);
	RingBufferConfig(txDebugDataRingBuffer, TX_BUFFER_SIZE, sizeof(int8_t));
	txDebugLengthRingBuffer = RingBufferConstructor();
	REQUIRE(txDebugLengthRingBuffer != 0);
	RingBufferConfig(txDebugLengthRingBuffer, 35, sizeof(int8_t));
	
#if DEBUGUART_ID == 6
	Uart6PortConfig(huart);
#elif DEBUGUART_ID == 1
	Uart1PortConfig(huart);
#elif DEBUGUART_ID == 3
	Uart3PortConfig(huart);
#elif DEBUGUART_ID == 2
	Uart2PortConfig(huart);
#endif

	HAL_UART_Receive_IT(huart, (uint8_t*) (huart->pRxBuffPtr), 1);

}
/****************************************************************/
/** @brief: get the huart ptr
 ****************************************************************/
UART_HandleTypeDef* GetUartDebugPtr(void) {
	return huartDebugPort;
}
/****************************************************************/
/** @brief: check inside the Ring buffer txDebugLengthRingBuffer contain any package
 ****************************************************************/
int CheckHasMsg() {
	return GetNumberByteUsedOfRBuffer(txDebugLengthRingBuffer) > 0;
}
/****************************************************************/
/** @brief: save a msg into buffer using PushRingBuffer
 ****************************************************************/
void PushAMsgToTxRbuff(int8_t* buff, int32_t length) {
	REQUIRE(GetNumberByteLeftOfRBuffer(txDebugLengthRingBuffer)>0);
	PushRingBuffer(txDebugLengthRingBuffer, &length);
	while (length--) {
		//if has space in ring buffer
		REQUIRE(GetNumberByteLeftOfRBuffer(txDebugDataRingBuffer) > 0);		
		PushRingBuffer(txDebugDataRingBuffer, buff);
		buff++;
	}
}
/****************************************************************/
/** @brief: pop a msg into buffer using PushRingBuffer
 ****************************************************************/
int32_t PopAMsgFromTxBuff(int8_t* buff) {
	int length = 0;
	PopRingBuffer(txDebugLengthRingBuffer, &length);
	int8_t* buffPtr = buff;
	int index = length;
	while (index--) {
		PopRingBuffer(txDebugDataRingBuffer, buffPtr);
		buffPtr++;
	}
	return length;
}

/****************************************************************/
/** @brief: send msg to serial
 ****************************************************************/
int32_t UDebugPrintf(char* data, ...) {
	UART_HandleTypeDef * huart = GetUartDebugPtr();
	int32_t ret = -1;
	va_list args;

	va_start(args, data);
	REQUIRE(strlen((const char*)data) < TX_BUFFER_SIZE);
	int32_t lengthOfMsg = vsnprintf((char*) txMsg, TX_BUFFER_SIZE,
			(const char*) data, args);
	va_end(args);
	
	if (huart->hdmatx->State == HAL_DMA_STATE_READY) {
		int32_t txRBuffState = CheckHasMsg();
		if (txRBuffState == false) {
			memcpy(txDMABuffer,txMsg,sizeof(txMsg));
			HAL_StatusTypeDef ret1 = HAL_UART_Transmit_DMA(huart, (uint8_t *) txDMABuffer, lengthOfMsg);
			
			if(ret1 == HAL_BUSY || ret1 == HAL_ERROR){
				PushAMsgToTxRbuff(txMsg,lengthOfMsg);
			} else{
				ret = 0;
			}				
		} else if (txRBuffState == true) {
			PushAMsgToTxRbuff(txMsg, lengthOfMsg);
			ret = 1;
		}
	} else {
		PushAMsgToTxRbuff(txMsg, lengthOfMsg);
		ret = 2;
	}
	return ret;
}

int32_t UDebugSendRaw(int8_t * data, int32_t lengthOfMsg) {
	UART_HandleTypeDef * huart = GetUartDebugPtr();
	int32_t ret = -1;

	if (huart->hdmatx->State == HAL_DMA_STATE_READY) {
		int32_t txRBuffState = CheckHasMsg();
		if (txRBuffState == false) {
			memcpy(txDMABuffer,data,sizeof(data));
			HAL_StatusTypeDef ret1 = HAL_UART_Transmit_DMA(huart, (uint8_t *) txDMABuffer, lengthOfMsg);	
			if(ret1 == HAL_BUSY || ret1 == HAL_ERROR){
				PushAMsgToTxRbuff(txMsg,lengthOfMsg);
			} else{
				ret = 0;
			}		
		} else if (txRBuffState == true) {
			PushAMsgToTxRbuff(data, lengthOfMsg);
			ret = 1;
		}
	} else {
		PushAMsgToTxRbuff(data, lengthOfMsg);
		ret = 2;
	}
	return ret;
}
int32_t UDebugSimplePrintf(int8_t * data, int32_t lengthOfMsg) {
	return HAL_UART_Transmit(huartDebugPort,(uint8_t*) data, lengthOfMsg,100);
}

void HAL_UARTDebug_TxCpltCallback(UART_HandleTypeDef * huart) {		
		if(huart->hdmatx->State == HAL_DMA_STATE_READY_MEM0){
			huart->hdmatx->State = HAL_DMA_STATE_READY;
		}
		if (CheckHasMsg()) {
			int32_t lengthOfMsg = PopAMsgFromTxBuff(txMsg);
			memcpy(txDMABuffer,txMsg,sizeof(txMsg));
			HAL_StatusTypeDef ret = HAL_UART_Transmit_DMA(huart, (uint8_t *) txDMABuffer, lengthOfMsg);
			if(ret == HAL_BUSY || ret == HAL_ERROR){
				PushAMsgToTxRbuff(txDMABuffer,lengthOfMsg);
			}
		}
}

void UARTDebug_ControllerLoop(UART_HandleTypeDef *huart) {
	if (huart->hdmatx->State == HAL_DMA_STATE_READY) {
		if (mutex_HAL_UARTDebug_TxCpltCallback == 0) {	
			mutex_HAL_UARTDebug_TxCpltCallback = 1;
			if (CheckHasMsg()) {
				int32_t lengthOfMsg = PopAMsgFromTxBuff(txMsg);
				memcpy(txDMABuffer,txMsg,sizeof(txMsg));
				HAL_StatusTypeDef ret = HAL_UART_Transmit_DMA(huart, (uint8_t *) txDMABuffer, lengthOfMsg);
				if(ret == HAL_BUSY || ret == HAL_ERROR){
					PushAMsgToTxRbuff(txMsg,lengthOfMsg);
				}				
			}			
			mutex_HAL_UARTDebug_TxCpltCallback = 0;
		}		
	}
	if(rearmUartReceiveIT==1){
		HAL_StatusTypeDef ret = HAL_UART_Receive_IT(huart, (uint8_t*) (huart->pRxBuffPtr), 1);
		if(ret == HAL_OK){
			rearmUartReceiveIT = 0;
		}
	}
}

int8_t ReadDebugUart(void) {
	int8_t ret = '\0';

	int32_t counts = GetNumberByteUsedOfRBuffer(rxDebugDataRingBuffer);

	if (counts != 0) {
		PopRingBuffer(rxDebugDataRingBuffer, &ret);
	}

	return ret;
}

void HAL_UARTDebug_RxCpltCallback(UART_HandleTypeDef *huart) {
	PushRingBuffer(rxDebugDataRingBuffer, (--(huart->pRxBuffPtr)));
	//rearm
	HAL_StatusTypeDef ret = HAL_UART_Receive_IT(huart, (uint8_t*) (huart->pRxBuffPtr), 1);
	if(ret != HAL_OK){
		rearmUartReceiveIT = 1;
	}
}

