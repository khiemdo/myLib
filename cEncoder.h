/* Khiem
 * Dec 2, 2014
 * project: for servo motor
 * description: configure encoder 0, encoder 1
 *		enc0: b4,b5,tim3
 *		enc1: b6,b7,tim4
 */

#ifndef _cEncoder_h
#define _cEncoder_h
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "deviceConfig.h"

typedef struct {
	int32_t enableFlag;
	int16_t lastCounts16b;
	int16_t counts16b;
	int16_t deltaCounts16b;
	int32_t counts32b;
	volatile uint32_t* encoderAddr;
	volatile TIM_TypeDef * encoderTIM;
	TIM_HandleTypeDef* timHandle;
} cIncEncoder;

void cEncoderTim3Config(cIncEncoder* me, TIM_HandleTypeDef* htim);
void cEncoderTim3Deconfig(cIncEncoder* me);
void cEncoderTim1Config(cIncEncoder* me, TIM_HandleTypeDef* htim);
void cEncoderTim1Deconfig(cIncEncoder* me);
void cEncoderTim4Config(cIncEncoder* me, TIM_HandleTypeDef* htim);
void cEncoderTim4Deconfig(cIncEncoder* me);

void EncStructInit_cIncEncoder(cIncEncoder* me);
void SetEnableFlag_cIncEncoder(cIncEncoder * me, int flag);
int IsEncoderEnable_cIncEncoder(cIncEncoder * me);

void SetCounts_cIncEncoder(cIncEncoder * me, int encoderCounter);
int GetCounts_cIncEncoder(cIncEncoder * me);
void ResetCounts_cIncEncoder(cIncEncoder * me);
#ifdef __cplusplus
}
#endif
#endif
