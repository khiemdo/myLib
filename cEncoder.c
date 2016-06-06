#include "cEncoder.h"
#include "string.h"
#include "cAssert.h"

void EncStructInit_cIncEncoder(cIncEncoder* me) {
	memset(me, 0, sizeof(cIncEncoder));
}

void cEncoderTim3Config(cIncEncoder* me, TIM_HandleTypeDef* htim) {
	me->timHandle = htim;
	me->encoderTIM = TIM3;
	me->encoderAddr = &(TIM3->CNT);

	TIM_Encoder_InitTypeDef sConfig;
	TIM_MasterConfigTypeDef sMasterConfig;
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_TIM3_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	htim->Instance = TIM3;
	htim->Init.Prescaler = 0;
	htim->Init.CounterMode = TIM_COUNTERMODE_UP;
	htim->Init.Period = ~0;
	htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim->Init.RepetitionCounter = 0;
	sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC1Filter = 0;
	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC2Filter = 0;
	if (HAL_TIM_Encoder_Init(htim, &sConfig) != HAL_OK) {
		REQUIRE(0);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig) != HAL_OK) {
		REQUIRE(0);
	}

	SetEnableFlag_cIncEncoder(me,SET);
}
void cEncoderTim3Deconfig(cIncEncoder* me) {
	__HAL_RCC_TIM3_CLK_DISABLE();
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_6 | GPIO_PIN_7);
}

void cEncoderTim1Config(cIncEncoder* me, TIM_HandleTypeDef* htim) {
	me->timHandle = htim;
	me->encoderTIM = TIM1;
	me->encoderAddr = &TIM1->CNT;

	TIM_Encoder_InitTypeDef sConfig;
	TIM_MasterConfigTypeDef sMasterConfig;
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_TIM1_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	htim->Instance = TIM1;
	htim->Init.Prescaler = 0;
	htim->Init.CounterMode = TIM_COUNTERMODE_UP;
	htim->Init.Period = 0;
	htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim->Init.RepetitionCounter = 0;
	sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC1Filter = 0;
	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC2Filter = 0;
	if (HAL_TIM_Encoder_Init(htim, &sConfig) != HAL_OK) {
		REQUIRE(0);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig) != HAL_OK) {
		REQUIRE(0);
	}

	SetEnableFlag_cIncEncoder(me,SET);
}
void cEncoderTim1Deconfig(cIncEncoder* me) {
	__HAL_RCC_TIM1_CLK_DISABLE();
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8 | GPIO_PIN_9);
}

void cEncoderTim4Config(cIncEncoder* me, TIM_HandleTypeDef* htim) {
	me->timHandle = htim;
	me->encoderTIM = TIM4;
	me->encoderAddr = &TIM4->CNT;

	TIM_Encoder_InitTypeDef sConfig;
	TIM_MasterConfigTypeDef sMasterConfig;
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_TIM4_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	htim->Instance = TIM4;
	htim->Init.Prescaler = 0;
	htim->Init.CounterMode = TIM_COUNTERMODE_UP;
	htim->Init.Period = 0;
	htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim->Init.RepetitionCounter = 0;
	sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC1Filter = 0;
	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC2Filter = 0;
	if (HAL_TIM_Encoder_Init(htim, &sConfig) != HAL_OK) {
		REQUIRE(0);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig) != HAL_OK) {
		REQUIRE(0);
	}

	SetEnableFlag_cIncEncoder(me,SET);

}
void cEncoderTim4Deconfig(cIncEncoder* me) {
	__HAL_RCC_TIM4_CLK_DISABLE();
	HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6 | GPIO_PIN_7);
}
void SetEnableFlag_cIncEncoder(cIncEncoder * me, int flag) {
	if (flag > 0)
		HAL_TIM_Encoder_Start(me->timHandle, TIM_CHANNEL_ALL);
	else
		HAL_TIM_Encoder_Stop(me->timHandle, TIM_CHANNEL_ALL);
	me->enableFlag = flag;
}
int IsEncoderEnable_cIncEncoder(cIncEncoder * me) {
	return me->enableFlag;
}

//to avoid overflow
void SetCounts_cIncEncoder(cIncEncoder * me, int encoderCounter) {
	SetEnableFlag_cIncEncoder(me,RESET);
	me->counts32b = encoderCounter;
	me->counts16b = 0;
	me->lastCounts16b = 0;
	me->deltaCounts16b = 0;
	me->encoderTIM->CNT = 0;
	me->encoderTIM->ARR = 0;
	SetEnableFlag_cIncEncoder(me,SET);
}
void ResetCounts_cIncEncoder(cIncEncoder * me) {
	SetEnableFlag_cIncEncoder(me,RESET);
	me->lastCounts16b = 0;
	me->counts16b = 0;
	me->deltaCounts16b = 0;
	me->counts32b = 0;
	me->encoderTIM->CNT = 0;
	me->encoderTIM->ARR = 0;
	SetEnableFlag_cIncEncoder(me,SET);
}

//Port, need to be called frequently
//ret:encoderCounter
int GetCounts_cIncEncoder(cIncEncoder * me) {
	me->counts16b = (int16_t)(*(me->encoderAddr));
	me->deltaCounts16b = me->counts16b - me->lastCounts16b;
	me->lastCounts16b = me->counts16b;
	me->counts32b += (int32_t) me->deltaCounts16b;
	return me->counts32b;
}

