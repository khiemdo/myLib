#include "main.h"
FILENUM(506);

#include "cAbsEncoder.h"
#include "cAssert.h"
#include "stdlib.h"
#include "cDebugUart.h"
#include "cSPIAbsEnc.h"
#include "MazherteqBSP.h"

#define ENC_RAW_START_LMT_TEST	930
#define ENC_RAW_END_LMT_TEST		230
#define ENC_RAW_MAX_TEST			1023
#define ENC_RAW_MIN_TEST			0
#define ENC_OFFSET_TEST			0

cAbsEncoder* testAbsEnc;


void TestcAbsEncConfig0() {
	cAbsEncoder* me;
	testAbsEnc = cAbsEncoderConstructor();
	me = testAbsEnc;

	me->encRawEndLmt = ENC_RAW_END_LMT_TEST;
	me->encRawStartLmt = ENC_RAW_START_LMT_TEST;
	me->encRawMax = ENC_RAW_MAX_TEST;
	me->encRawMin = ENC_RAW_MIN_TEST;
	me->encOffset = ENC_OFFSET_TEST;
	ValidateAbsEncParameters(me);

	me->encoderPort = (cEncoderPort*) cSPIAbsEncoderPortConstructor();
	me->encoderPort->id = 1;
	me->encoderPort->getEncoderValue =
			(GetEncoderValue_cEncoderPortCast) GetEncoderValue_cSPIAbsEncoder;
	me->encoderPort->updateEncoder = (UpdateEncoder_cEncoderPortCast) UpdateEncoder_cSPIAbsEncoder;
	SPI_HandleTypeDef * hspi = calloc(1, sizeof(SPI_HandleTypeDef));
	REQUIRE(hspi != 0);
	SPI3PortConfig_MBSP(hspi);
	((cSPIAbsEncoderPort*) me->encoderPort)->hspi = hspi;

}

void TestcAbsEnc_DisplayProcessedValue() {
	static unsigned int lastTime = 0;
	unsigned int currentTime = HAL_GetTick();
	int deltaTime = currentTime - lastTime;
	if (deltaTime > 1000) {
		UDebugPrintf("absEnc:%d\r\n", GetEncValue_cAbsEncoder(testAbsEnc));
		lastTime = currentTime;
	}
}
