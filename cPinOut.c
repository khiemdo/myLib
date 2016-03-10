#include "main.h"
FILENUM(33);

#include "cPinOut.h"
#include <string.h>
#include <stdlib.h>
#include "cAssert.h"

cPinOutStruct* PinOutConstructor() {
	cPinOutStruct* me = calloc(1, sizeof(cPinOutStruct));
	REQUIRE(me);
	return me;
}
cPatternedPinOutStruct* PatternedPinOutConstructor() {
	cPatternedPinOutStruct* me = calloc(1, sizeof(cPatternedPinOutStruct));
	REQUIRE(me);
	return me;
}
void PinOutInit(cPinOutStruct *me, int32_t type) {
	if (type == 0) {
		memset(me, 0, sizeof(cPinOutStruct));
	} else if (type == 1) {
		memset(me, 0, sizeof(cPatternedPinOutStruct));
	}
}
void OffPinOut(cPinOutStruct *me) {
	HAL_GPIO_WritePin(me->port, me->pin, 0);
}
void OnPinOut(cPinOutStruct *me) {
	HAL_GPIO_WritePin(me->port, me->pin, 1);
}
void TogglePinOut(cPinOutStruct *me){
	HAL_GPIO_TogglePin(me->port,me->pin);
}
void SetPinOut(cPinOutStruct *me, int setter) {
	HAL_GPIO_WritePin(me->port, me->pin, setter);
}

void SetPatternOutputPin(cPatternedPinOutStruct *me, int32_t timeOn,
		int32_t timeOff) {
	if (timeOn == -1 && timeOff == 0) {
		OnPinOut((cPinOutStruct*) me);
	} else if (timeOn == 0 && timeOff == -1) {
		OffPinOut((cPinOutStruct*) me);
	}
	me->timeToOff = timeOff;
	me->timeToOn = timeOn;
	me->lastTime = HAL_GetTick();
}
void OutputPinPatternLoop(cPatternedPinOutStruct *me) {
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
