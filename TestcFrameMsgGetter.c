#include "main.h"
FILENUM(4);

#include "TestcFrameMsgGetter.h"
#include "cFrameMsgGetter.h"
#include "cDebugUart.h"
#include "cAssert.h"
#include <stdint.h>
#include <string.h>

char msgStr[10];

void TestcFrameMsgGetterConfig() {
	FrameMsgGetterInitialize();
}
void TestcFrameMsgGetter() {
	int8_t ch = ReadDebugUart();
	int32_t msgLength = FrameMsgGetter((char)ch, msgStr);

	if (msgLength != 0) {
		UDebugPrintf("get cmd: %s\r\n", msgStr);
	}
}
