#ifndef _cSPIAbsEncoderPort_h
#define _cSPIAbsEncoderPort_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "cEncoderPort.h"

typedef struct {
	cEncoderPort super;
	SPI_HandleTypeDef* hspi;
} cSPIAbsEncoderPort;

cSPIAbsEncoderPort* cSPIAbsEncoderPortConstructor();
uint32_t GetEncoderValue_cSPIAbsEncoder(cSPIAbsEncoderPort* me);
void UpdateEncoder_cSPIAbsEncoder(cSPIAbsEncoderPort* me);

#ifdef __cplusplus
}
#endif
#endif
