#include "main.h"
FILENUM(20);

#include "crc.h"
#include "TestCRC.h"
#include "cAssert.h"
#include <stdint.h>
#include <string.h>

void TestCRCConfig(void) {
	crcInit();
}
void TestCRCRun(void) {
	uint8_t test[] = "123456789";
	uint16_t result = crcSlow(test, strlen((const char *) test));

	REQUIRE(result == CHECK_VALUE);
	result = crcFast(test, strlen((const char *) test));
	REQUIRE(result == CHECK_VALUE);

}
