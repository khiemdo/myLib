/* Khiem
 * Dec 2, 2014
 * project: for servo motor
 * description: configure encoder 0, encoder 1
 *		enc0: b4,b5,tim3
 *		enc1: b6,b7,tim4
 */

#ifndef _encoder_h
#define _encoder_h
#ifdef __cplusplus
extern "C" {
#endif

#include "deviceConfig.h"
#include "stdint.h"

typedef struct {
	int32_t id;
	uint32_t enableFlag;
	uint32_t prevEncoderCount;
	uint32_t currEncoderCount;
	uint32_t deltaEncoderCount;
	int32_t accumEncoderCounts;
	uint32_t lastTimeUpdate;
	uint32_t durationUpdate;
	uint32_t* volatile encoderAddr;
	TIM_TypeDef * encoderTIM;
} cEncoder;

void EncTIM3Config(cEncoder* me);
void EncTIM4Config(cEncoder* me);
void EncTIM5Config(cEncoder* me);

void Initialize_cEncoder(cEncoder* me);
void CheckPointerValid_cEncoder(cEncoder* me);
void Disable_cEncoder(cEncoder * me);
void Enable_cEncoder(cEncoder * me);
int IsEnable_cEncoder(cEncoder * me);

void SetCounts_cEncoder(cEncoder * me, int32_t encoderCounter);
int32_t GetCounts_cEncoder(cEncoder * me);
void Reset_cEncoder(cEncoder * me);

#ifdef __cplusplus
}
#endif
#endif
