#include "main.h"
FILENUM(14);

#include "TestcUartProtocolASCII.h"
#include "cUartProtocolASCII.h"
#include "cFrameMsgGetter.h"
#include "cDebugUart.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

void TestcUartProtocolAsciiConfig(){
    FrameMsgGetterInitialize();
}
void TestcUartProtocolAscii(){
    int8_t msgStr[10];
    int8_t ch = ReadDebugUart();
    int32_t msgLength = FrameMsgGetter(ch, msgStr);

    if (msgLength != 0) {
        int32_t msgType = SerialMsgHandleController(msgStr, msgLength);
        UDebugPrintf("msgType:%d\r\n", msgType);
    }
}

void TestSendSerialVersioncUartProtocolAscii(){
    SendSerialVersion();
}
