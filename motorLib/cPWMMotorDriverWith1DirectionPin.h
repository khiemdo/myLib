#ifndef _cPWMMotorDriverWith1DirectionPin_h
#define _cPWMMotorDriverWith1DirectionPin_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "cAssert.h"
#include "stdlib.h"
#include "cMotorDriver.h"

typedef struct cPWMMotorChannel_t{
	cMotorDriver super;
	volatile uint32_t *pwmValue;
	uint32_t resetPin;
	GPIO_TypeDef* resetPort;
	uint32_t directionPin;
	GPIO_TypeDef* directionPort;
} cPWMMotorDriverWith1DirectionPin;

void MotorChannel0Config_cPWMMotorDriverWith1DirectionPin(cPWMMotorDriverWith1DirectionPin* me);
void MotorChannel1Config_cPWMMotorDriverWith1DirectionPin(cPWMMotorDriverWith1DirectionPin* me);
void SetPower_cPWMMotorDriverWith1DirectionPin(cPWMMotorDriverWith1DirectionPin* me, int32_t powerValue);
uint32_t GetPower_cPWMMotorDriverWith1DirectionPin(cPWMMotorDriverWith1DirectionPin* me);
void DisableMotor_cPWMMotorDriverWith1DirectionPin(cPWMMotorDriverWith1DirectionPin* me);
void EnableMotor_cPWMMotorDriverWith1DirectionPin(cPWMMotorDriverWith1DirectionPin* me);

#ifdef __cplusplus
}
#endif
#endif
