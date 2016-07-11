#include "main.h"
FILENUM(4);

#include "TestcFrameMsgGetter.h"
#include "cFrameMsgGetter.h"
#include "cDebugUart.h"
#include "cAssert.h"
#include <stdint.h>
#include <string.h>

char msgStr[10];
char outframe[10];
cFrameMsgGetter framegetter_TestcFrameMsgGetter;

void TestcFrameMsgGetterConfig() {
	FrameMsgGetterInitialize(&framegetter_TestcFrameMsgGetter, 10,
			(int8_t*) msgStr, (int8_t*) outframe);
}
void TestcFrameMsgGetter() {
	char ch = 0;
	ReadDebugUart(&ch);
	int32_t msgLength = FrameMsgGetter(&framegetter_TestcFrameMsgGetter,
			(char) ch, (int8_t*)outframe);

	if (msgLength != 0) {
		UDebugPrintf("get cmd: %s\r\n", msgStr);
	}
}
