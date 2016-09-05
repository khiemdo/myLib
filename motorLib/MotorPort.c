#include "MotorPort.h"
#include "cAssert.h"

#define DHR12R1_OFFSET             ((uint32_t)0x00000008)
#define DHR12R2_OFFSET             ((uint32_t)0x00000014)

void Initialize_cMotorPort(cMotorPort * me) {
	int i = 0;
	me->isEnable = DISABLE;
	i = 1;
	do {
		me->motorControlPin[i] = 0;
		me->motorControlPort[i] = 0;
	} while (i-- != 0);

	me->motorTIM = 0;
	me->motorDAC = 0;
}
void CheckPointerValid_cMotorPort(cMotorPort* me) {
	REQUIRE(me);
}

inline void EnableMotorInterface0(cMotorPort * me) {
//	DAC_DMACmd(DAC_Channel_2, ENABLE);
	me->isEnable = 1;
}
inline void DisableMotorInterface0(cMotorPort * me) {
//	DAC_DMACmd(DAC_Channel_2, DISABLE);
	me->isEnable = 0;
}

/************************************************************************************/
/******************************** MOTOR ROTATE *****************************************/

/* input:
 * 		setSpeed Value: [-1000,1000];*/
inline void SetRotateDACInterface0(cMotorPort * me, int setSpeed) {
	setSpeed = 4 * setSpeed;
	if (setSpeed > 0) {
		HAL_GPIO_WritePin(me->motorControlPort[0], me->motorControlPin[0], SET);
		HAL_GPIO_WritePin(me->motorControlPort[1], me->motorControlPin[1], !SET);
		*me->motorDAC = (uint16_t)(setSpeed);
	} else if (setSpeed == 0) {
		HAL_GPIO_WritePin(me->motorControlPort[0], me->motorControlPin[0], !SET);
		HAL_GPIO_WritePin(me->motorControlPort[1], me->motorControlPin[1], !SET);
		*me->motorDAC = (uint16_t) 0;
	} else {
		HAL_GPIO_WritePin(me->motorControlPort[0], me->motorControlPin[0], !SET);
		HAL_GPIO_WritePin(me->motorControlPort[1], me->motorControlPin[1], SET);
		*me->motorDAC = (uint16_t)(-setSpeed);
	}
}
inline void SetRotateDAC(cMotorPort * me, int setSpeed) {
	SetRotateDACInterface0(me, setSpeed);
}
inline void SetRotatePWM(cMotorPort * me, int setSpeed) {
	if (setSpeed > 0) {
		HAL_GPIO_WritePin(me->motorControlPort[0], me->motorControlPin[0], SET);
		HAL_GPIO_WritePin(me->motorControlPort[1], me->motorControlPin[1], !SET);
		*me->motorTIM = (uint32_t) setSpeed;
	} else if (setSpeed == 0) {
		HAL_GPIO_WritePin(me->motorControlPort[0], me->motorControlPin[0], !SET);
		HAL_GPIO_WritePin(me->motorControlPort[1], me->motorControlPin[1], !SET);
		*me->motorTIM = (uint32_t) 0;
	} else {
		HAL_GPIO_WritePin(me->motorControlPort[0], me->motorControlPin[0], !SET);
		HAL_GPIO_WritePin(me->motorControlPort[1], me->motorControlPin[1], SET);
		*me->motorTIM = (uint32_t) (-setSpeed);
	}
}

inline void SetSoftStopInterface0(cMotorPort * me) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, !SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, !SET);
	SetRotate_MotorPort(me, 0);
}
inline void SetSoftStopInterface1(cMotorPort * me) {
	SetRotate_MotorPort(me, 0);
}

int IsMotorPortEnable_MotorPort(cMotorPort * me) {
	return me->isEnable;
}
void EnablePort_MotorPort(cMotorPort * me) {
	SetSoftStopInterface0(me);
	me->isEnable = 1;
}
void DisablePort_MotorPort(cMotorPort * me) {
	SetSoftStopInterface0(me);
	me->isEnable = 0;
}
void SetSoftStop_MotorPort(cMotorPort * me) {
	SetSoftStopInterface0(me);
}
/*
 * @para iValue:from -1000 to 1000
 */
void SetRotate_MotorPort(cMotorPort * me, int iValue) {
	if (me->motorTIM != 0) {
		SetRotatePWM(me, iValue);
	} else if (me->motorDAC != 0) {
		SetRotateDAC(me, iValue);
	}
}
