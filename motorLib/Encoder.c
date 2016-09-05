#include "Encoder.h"
#include "cAssert.h"

void Initialize_cEncoder(cEncoder* me) {
	me->enableFlag = 0;
	me->prevEncoderCount = 0;
	me->currEncoderCount = 0;
	me->deltaEncoderCount = 0;
	me->accumEncoderCounts = 0;
	*(me->encoderAddr) = 0;
	me->encoderTIM = 0;
}
void CheckPointerValid_cEncoder(cEncoder* me) {
	REQUIRE(me);
}

void Disable_cEncoder(cEncoder * me) {
	TIM_CCxCmd(me->encoderTIM, TIM_Channel_1, TIM_CCx_Disable);
	TIM_CCxCmd(me->encoderTIM, TIM_Channel_2, TIM_CCx_Disable);
	TIM_Cmd(me->encoderTIM, DISABLE);
	me->enableFlag = 0;
}
void Enable_cEncoder(cEncoder * me) {
	TIM_CCxCmd(me->encoderTIM, TIM_Channel_1, TIM_CCx_Enable);
	TIM_CCxCmd(me->encoderTIM, TIM_Channel_2, TIM_CCx_Enable);
	TIM_Cmd(me->encoderTIM, ENABLE);
	me->enableFlag = 1;
}
int IsEnable_cEncoder(cEncoder * me) {
	return me->enableFlag;
}

/**
 * @brief
 * @param  None
 * @retval encoderCounter
 * @note   need to be called frequently
 */
s32 GetCounts_cEncoder(cEncoder * me) {
	me->currEncoderCount = (int32_t)((int16_t)(*(me->encoderAddr)));
	me->deltaEncoderCount = me->currEncoderCount - me->prevEncoderCount;
	me->prevEncoderCount = me->currEncoderCount;
	me->accumEncoderCounts += (int32_t)(me->deltaEncoderCount);
	return me->accumEncoderCounts;
}
void Reset_cEncoder(cEncoder * me) {
	Disable_cEncoder(me);
	me->prevEncoderCount = 0;
	me->accumEncoderCounts = 0;
	me->encoderTIM->ARR = 0;
	me->encoderTIM->CNT = 0;
	me->encoderTIM->ARR = ~0;
	Enable_cEncoder(me);
	GetCounts_cEncoder(me);
}

