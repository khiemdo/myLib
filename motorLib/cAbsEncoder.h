#ifndef _cAbsEncoder_h
#define _cAbsEncoder_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "cEncoderPort.h"

typedef struct {
	SPI_HandleTypeDef* thisHspi;
} cAbsEncoderPort;

typedef struct {
	cEncoderPort * encoderPort;
	int linearizeFlag;
	int32_t rawValue; //from encoder port
	int32_t encRawMax;
	int32_t encRawMin;
	int32_t encRawStartLmt;
	int32_t encRawEndLmt;
	int32_t encOffset;
	int32_t linearizedEncValue;
	int32_t encFinalValue;
	int32_t lastEncFinalValue;
} cAbsEncoder;

cAbsEncoder* cAbsEncoderConstructor();
void ValidateAbsEncParameters(cAbsEncoder* me);
int32_t GetEncValue_cAbsEncoder(cAbsEncoder* me);

#ifdef __cplusplus
}
#endif
#endif
