/****************************************************************/
/** @file:      cGpioOutput.h
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		Jan 18, 2016
 *  @version:	2.0
 *  @brief:		generalize output n patternOutput
 *  @note:
 *
 ****************************************************************/

#ifndef _cGpioOutput_h
#define _cGpioOutput_h

#include "main.h"

typedef struct OutputPinStruct {
	int32_t id;
	GPIO_TypeDef *port;
	uint32_t pin;
	int32_t type;
} cPinOutStruct;

typedef struct PatternedOutputPinStruct {
	cPinOutStruct super;
	int32_t timeToOn;
	int32_t timeToOff;
	uint32_t lastTime; //in msec
} cPatternedPinOutStruct;

void PinOutInit(cPinOutStruct * const me, const int32_t type);
void SetPinOut(cPinOutStruct * const me, const int setter);
void OffPinOut(cPinOutStruct * const me);
void OnPinOut(cPinOutStruct *const me);
void TogglePinOut(cPinOutStruct * const me);
void SetPatternOutputPin(cPatternedPinOutStruct * const me,
		const int32_t timeOn, const int32_t timeOff, const uint32_t lastTime);
void OutputPinPatternLoop(cPatternedPinOutStruct * const me);

#endif
