#ifndef _cEncoderPort_h
#define _cEncoderPort_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "cAssert.h"
#include "stdlib.h"

typedef enum {
	UNDEFINED_EncoderType, SPI_ABS_ENCODER, PWM_ABS_ENCODER, INCREMENTAL_ENCODER
} EncoderType;

typedef uint32_t (*GetEncoderValue_cEncoderPortCast)(void*);
typedef void (*UpdateEncoder_cEncoderPortCast)(void*);

typedef struct cEncoderPort_t {
	int id;
	int type;
	int32_t rawValue;
	GetEncoderValue_cEncoderPortCast getEncoderValue;
	UpdateEncoder_cEncoderPortCast updateEncoder;
} cEncoderPort;

cEncoderPort* cEncoderPortConstructor();

//int32_t GetEncoderValue(cEncoderPort* me);
//void UpdateEncoder(cEncoderPort* me);
#ifdef __cplusplus
}
#endif
#endif
