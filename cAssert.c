#include "cAssert.h"
#include "cUart.h"

void my_assert_failed(uint8_t * file, uint32_t line, uint32_t fileIndex,
		int8_t * expression) {
	UartPrint("Wrong parameters value: file %s on line %d\r\n", (char*) file,
			(int) line);
}

void DebugLogHandle(char * msg, ...) {
	UartPrint(msg);
}
