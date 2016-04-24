#include "main.h"
FILENUM(503);
#include "cSPIAbsEnc.h"

cSPIAbsEncoderPort* cSPIAbsEncoderPortConstructor() {
	cSPIAbsEncoderPort* me = calloc(1, sizeof(cSPIAbsEncoderPort));
	REQUIRE(me);
	me->super.type = SPI_ABS_ENCODER;
	return me;
}
void UpdateEncoder_cSPIAbsEncoder(cSPIAbsEncoderPort* me) {
	SPI_HandleTypeDef* spiPtr = me->hspi;

	while (HAL_SPI_GetState(spiPtr) != HAL_SPI_STATE_READY) {
	}
	int32_t rxNumber;
	HAL_StatusTypeDef ret = HAL_SPI_Receive(spiPtr, (uint8_t*) &rxNumber, 1,
			100);
	REQUIRE(ret == HAL_OK);
	me->super.rawValue = (int32_t) ((rxNumber >> 5) & 0x3ff);
}
uint32_t GetEncoderValue_cSPIAbsEncoder(cSPIAbsEncoderPort* me) {
	return me->super.rawValue;
}
