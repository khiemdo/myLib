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
	uint32_t lastTime;//in msec
} cPatternedPinOutStruct;

cPinOutStruct* PinOutConstructor();
cPatternedPinOutStruct* PatternedPinOutConstructor();
void PinOutInit(cPinOutStruct *me, int32_t type);
void SetPinOut(cPinOutStruct *me, int setter);
void OffPinOut(cPinOutStruct *me);
void OnPinOut(cPinOutStruct *me);
void TogglePinOut(cPinOutStruct *me);
void SetPatternOutputPin(cPatternedPinOutStruct *me, int32_t timeOn, int32_t timeOff);
void OutputPinPatternLoop(cPatternedPinOutStruct *me);

#endif
