#include "main.h"
FILENUM(2);

#include "TcDebugUart.h"
#include "cDebugUart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "cAssert.h"

void TPrinf() {
	unsigned int currentTime = HAL_GetTick();
	UDebugPrintf("hello-%d\r\n",currentTime);
	UARTDebug_ControllerLoop(GetUartDebugPtr());
}

void TPrinfInBurst(){
	static uint32_t lastTime = 0;
	uint32_t currentTime = HAL_GetTick();
	uint16_t deltaTime = currentTime - lastTime;
	if(deltaTime>1000){
		UDebugPrintf("hello%d\r\n",HAL_GetTick());//fail the test of fast print
		DEBUG(LOG_ERROR,"hello%d\r\n",HAL_GetTick());	
		DEBUG(LOG_ERROR,"hello%d\r\n",HAL_GetTick());	
		DEBUG(LOG_ERROR,"hello%d\r\n",HAL_GetTick());	
		DEBUG(LOG_ERROR,"hello%d\r\n",HAL_GetTick());	
		lastTime = currentTime;
	}
	UARTDebug_ControllerLoop(GetUartDebugPtr());
}
void TPrinfFloat() {
	static float displayNum = 1000.0;
	displayNum /= 2;
	if (displayNum == 0) {
		displayNum = 1000.0;
	}
	UDebugPrintf("current Number = %.2f\t\n", displayNum);
}

void TSimplePrintf(){
	uint32_t currentTime = HAL_GetTick();
	char msg[100]={0};
	sprintf(msg,"hello-%d\r\n",(int)currentTime);
	UDebugSimplePrintf((int8_t*)msg, strlen(msg));//fail the test of fast print
}
void TSimplePrintfInBurst(){
	static uint32_t lastTime = 0;
	uint32_t currentTime = HAL_GetTick();
	uint16_t deltaTime = currentTime - lastTime;
	if(deltaTime>1000){
		char msg[100]={0};
		sprintf(msg,"hello%d\r\n",(int)HAL_GetTick());
		UDebugSimplePrintf((int8_t*)msg, strlen(msg));
		memset(msg,0,100);
		sprintf(msg,"DB:0:hello%d\r\n",(int)HAL_GetTick());
		UDebugSimplePrintf((int8_t*)msg, strlen(msg));
		memset(msg,0,100);
		sprintf(msg,"DB:0:hello%d\r\n",(int)HAL_GetTick());
		UDebugSimplePrintf((int8_t*)msg, strlen(msg));
		memset(msg,0,100);
		sprintf(msg,"DB:0:hello%d\r\n",(int)HAL_GetTick());
		UDebugSimplePrintf((int8_t*)msg, strlen(msg));
		memset(msg,0,100);
		sprintf(msg,"DB:0:hello%d\r\n",(int)HAL_GetTick());
		UDebugSimplePrintf((int8_t*)msg, strlen(msg));
		lastTime = currentTime;
	}
}
void TcUartMirroInputNOutput(void) {
	char ret = ReadDebugUart();
	if (ret != '\0')
		UDebugPrintf("%c", ret);
	UARTDebug_ControllerLoop(GetUartDebugPtr());
}
