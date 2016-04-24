#include "main.h"
FILENUM(1000001);
#include "TestcSPIPort.h"
#include "cSPIPort.h"
#include <string.h>
#include "cDebugUart.h"

SPI_HandleTypeDef hspiTest;
uint8_t aTxBuffer[] = "hello\r\n";
uint8_t aRxBuffer[16] = { 0 };
void TestSPI3Config(void) {
	SPI3PortConfig(&hspiTest);
}

void TestSimpleSPI3Write(void) {
	static uint32_t lastTime = 0;
	uint32_t currentTime = HAL_GetTick();
	int32_t deltaTime = currentTime - lastTime;
	if (deltaTime > 1000) {
		HAL_StatusTypeDef ret;
		while (HAL_SPI_GetState(&hspiTest) != HAL_SPI_STATE_READY) {
		}
		memset(aRxBuffer, 0, 8);
		uint32_t rxNumber = 0;
//		ret = HAL_SPI_Receive(&hspiTest, aRxBuffer, 2, 100);
		ret = HAL_SPI_Receive(&hspiTest, (uint8_t*)&aRxBuffer, 1, 100);
		memcpy(&rxNumber,aRxBuffer,sizeof(uint32_t));
		uint32_t encoder = rxNumber >> 22;
		if (ret == HAL_ERROR) {
			UDebugPrintf("SPI error:%d", (int32_t) ret);
		} else if (ret == HAL_TIMEOUT) {
			UDebugPrintf("no SPIMsg");
		}
		(void)encoder;
		lastTime = currentTime;
	}
}
