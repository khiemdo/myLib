#include "main.h"
FILENUM(50001);
#include "cPWMMotorDriverWith1DirectionPin.h"
#include "cAssert.h"

/*project-based implmentation*/
extern void PWMDriveWith1DirectionPinConfig0_MBSP(cPWMMotorDriverWith1DirectionPin* me);
extern void PWMDriveWith1DirectionPinConfig1_MBSP(cPWMMotorDriverWith1DirectionPin* me);

void MotorChannel0Config_cPWMMotorDriverWith1DirectionPin(cPWMMotorDriverWith1DirectionPin* me){
	me->super.id = 0;
	me->super.type = PWMDRIVER_WITH_1DIRECTIONPINS;
	PWMDriveWith1DirectionPinConfig0_MBSP(me);
}
void MotorChannel1Config_cPWMMotorDriverWith1DirectionPin(cPWMMotorDriverWith1DirectionPin* me){
	me->super.id = 0;
	me->super.type = PWMDRIVER_WITH_1DIRECTIONPINS;
	PWMDriveWith1DirectionPinConfig1_MBSP(me);
}

void SetPower_cPWMMotorDriverWith1DirectionPin(cPWMMotorDriverWith1DirectionPin* me, int32_t powerValue) {
	cPWMMotorDriverWith1DirectionPin* ptr = (cPWMMotorDriverWith1DirectionPin*)me;
	if (powerValue > 0) {
		HAL_GPIO_WritePin(ptr->directionPort, ptr->directionPin, GPIO_PIN_SET);
		*ptr->pwmValue = powerValue;
	} else if (powerValue < 0) {
		HAL_GPIO_WritePin(ptr->directionPort, ptr->directionPin, GPIO_PIN_RESET);
		*ptr->pwmValue = -powerValue;
	} else {
		HAL_GPIO_WritePin(ptr->directionPort, ptr->directionPin, GPIO_PIN_SET);
		*ptr->pwmValue = 0;
	}
}
uint32_t GetPower_cPWMMotorDriverWith1DirectionPin(cPWMMotorDriverWith1DirectionPin* me){
	return *me->pwmValue;
}
void DisableMotor_cPWMMotorDriverWith1DirectionPin(cPWMMotorDriverWith1DirectionPin* me) {
	HAL_GPIO_WritePin(me->resetPort, me->resetPin, GPIO_PIN_RESET);
}
void EnableMotor_cPWMMotorDriverWith1DirectionPin(cPWMMotorDriverWith1DirectionPin* me) {
	HAL_GPIO_WritePin(me->resetPort, me->resetPin, GPIO_PIN_SET);
}


