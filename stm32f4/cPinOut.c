#include "main.h"
FILENUM(33);

#include "cPinOut.h"
#include <string.h>
#include <stdlib.h>
#include "cAssert.h"

void PinOutInit(cPinOutStruct * const me, const int32_t type) {
	if (type == 0) {
		memset(me, 0, sizeof(cPinOutStruct));
	} else if (type == 1) {
		memset(me, 0, sizeof(cPatternedPinOutStruct));
	}
}
void OffPinOut(cPinOutStruct * const me) {
	HAL_GPIO_WritePin(me->port, me->pin, GPIO_PIN_RESET);
}
void OnPinOut(cPinOutStruct * const me) {
	HAL_GPIO_WritePin(me->port, me->pin, GPIO_PIN_SET);
}
void TogglePinOut(cPinOutStruct * const me){
	HAL_GPIO_TogglePin(me->port,me->pin);
}
void SetPinOut(cPinOutStruct *me, int setter) {
	HAL_GPIO_WritePin(me->port, me->pin, setter);
}

void SetPatternOutputPin(cPatternedPinOutStruct * const me, const int32_t timeOn,
		const int32_t timeOff, const uint32_t lastTime) {
	if (timeOn == -1 && timeOff == 0) {
		OnPinOut((cPinOutStruct*) me);
	} else if (timeOn == 0 && timeOff == -1) {
		OffPinOut((cPinOutStruct*) me);
	}
	me->timeToOff = timeOff;
	me->timeToOn = timeOn;
	me->lastTime = lastTime;
}
void OutputPinPatternLoop(cPatternedPinOutStruct * const me) {
	if (me->timeToOff < 0 || me->timeToOn < 0) {
		return;
	}
	unsigned int currentTime = HAL_GetTick();
	unsigned int deltaTime = abs(currentTime - me->lastTime);
	int statePin = me->super.port->ODR & me->super.pin;
	if (statePin == 0) { //currently is off
		if (deltaTime > me->timeToOff) {
			HAL_GPIO_WritePin(me->super.port, me->super.pin, 1);
			me->lastTime = currentTime;
		}
	} else if (statePin != 0) { //currently is on
		if (deltaTime > me->timeToOn) {
			HAL_GPIO_WritePin(me->super.port, me->super.pin, 0);
			me->lastTime = currentTime;
		}
	}
}
