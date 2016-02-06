#include "main.h"
FILENUM(2);

#include "TcDebugUart.h"
#include "cDebugUart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void TPrinf() {
    static uint32_t lastTime = 0;
    uint32_t currentTime = HAL_GetTick();
    uint32_t deltaTime = currentTime - lastTime;

    if (deltaTime > 1) {
        UDebugPrintf((int8_t*)"helloKhiem1helloKhiem2helloKhiem3\r\n");
        lastTime = currentTime;
    }
    UARTDebug_TBuffControllerLoop(GetUartDebugPtr());
}

void TPrinfFloat() {
    static float displayNum = 1000.0;

    displayNum /= 2;
    if (displayNum == 0) {
        displayNum = 1000.0;
    }
    UDebugPrintf((int8_t*)"current Number = %.2f", displayNum);
}

void TPrinfRbuffAssync() {
    static uint32_t lastTime = 0;
    uint32_t currentTime = HAL_GetTick();
    uint32_t deltaTime = currentTime - lastTime;

    const int32_t countCONST = 7;
    static int32_t count = 7;

    static int32_t oneSecEvent = 0;

    if (deltaTime > 1000) {
        oneSecEvent = 1;
        lastTime = currentTime;
    }

    if (oneSecEvent == 1) {
        UDebugPrintf((int8_t*)"helloKhiem1helloKhiem2helloKhiem3\r\n");
        count--;
        if (count == 0) {
            count = countCONST;
            oneSecEvent = 0;
        }
    }

    UARTDebug_TBuffControllerLoop(GetUartDebugPtr());
} /* TPrinfRbuffAssync */
void TcUartMirroInputNOutput(void) {
    int8_t ret = ReadDebugUart();

    if (ret != '\0')
        UDebugPrintf((int8_t*)"%c", ret);
}
