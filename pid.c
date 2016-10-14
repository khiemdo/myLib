#include "main.h"
#include "pid.h"
#include <stdlib.h>
#include "cAssert.h"
#include "string.h"
#include "generalUtility.h"

void Initialize_cPIDStruct(cPIDStruct* me) {
	memset(me, 0, sizeof(cPIDStruct));
	me->pMax = 1000;
	me->iMax = 1000;
	me->iStateMax = 1000;
	me->dMax = 1000;
	me->oMax = 1000;
}
void CheckPointerValid_cPIDStruct(cPIDStruct* me) {
	REQUIRE(me);
}
void SetTunings_cPIDStruct(cPIDStruct* me, float p, float i, float d) {
	me->pGain = p;
	me->iGain = i;
	me->dGain = d;
}
void SetLimits_cPIDStruct(cPIDStruct* me, float pMax, float iMax, float dMax,
		float oMax) {
	me->pMax = pMax;
	me->iMax = iMax;
	me->dMax = dMax;
	me->oMax = oMax;
}
void SetSamplingTime_cPIDStruct(cPIDStruct* me, uint32_t newSampleTime) {
	if (newSampleTime > 0) {
		float ratio = newSampleTime / me->sampleTime;
		me->iGain *= ratio;
		me->dGain /= ratio;
		me->sampleTime = newSampleTime;
	}
}
void ResetPID_cPIDStruct(cPIDStruct* me, float currentPos, float output) {
	me->dTerm_1 = currentPos;
	me->iTerm_1 = output;
	LimitToRange_Utility(me->iTerm_1, -me->iMax, me->iMax);
}
void Configure_cPIDStruct(cPIDStruct* me, float p, float i, float d, float f,
		float pMax, float iMax, float iStateMax, float dMax, float oMax,
		float delKp, float Kz) {
	me->pMax = pMax;
	me->iMax = iMax;
	me->iStateMax = iStateMax;
	me->dMax = dMax;
	me->oMax = oMax;
	me->pGain = p;
	me->iGain = i;
	me->dGain = d;
	me->fGain = f;
}

//http://www.mstarlabs.com/apeng/techniques/pidsoftw.html
float Update_cPIDStruct(cPIDStruct *me, float setpoint, float position) {
	float p = me->pGain;
	float i = me->iGain;
	float d = me->dGain;
	float f = (me->fGain) ? me->fGain : 1.0f;
	float error = setpoint - position;

	// calculate the proportional term
	me->pTerm_1 = p * error;
	if (me->pTerm_1 > me->pMax) {
		me->pTerm_1 = me->pMax;
	} else if (me->pTerm_1 < -me->pMax) {
		me->pTerm_1 = -me->pMax;
	}

	// calculate the integral state with appropriate limiting
	me->iState += error;
	//this integrator Rate Limiting to avoid windup
	if (me->iState > me->iStateMax)
		me->iState = me->iStateMax;
	else if (me->iState < -me->iStateMax)
		me->iState = -me->iStateMax;
	//this integrator latching to avoid windup
	me->iTerm_1 = i * me->iState;
	if (me->iTerm_1 > me->iMax) {
		me->iTerm_1 = me->iMax;
		me->iState -= error;
	} else if (me->iTerm_1 < -me->iMax) {
		me->iTerm_1 = -me->iMax;
		me->iState -= error;
	}

	// derivative
	if (me->dGain) {
		error = -position;
		me->dTerm_1 = (d * f) * (error - me->dState);
		me->dState += f * (error - me->dState);
		if (me->dTerm_1 > me->dMax) {
			me->dTerm_1 = me->dMax;
		} else if (me->dTerm_1 < -me->dMax) {
			me->dTerm_1 = -me->dMax;
		}
	} else {
		me->dTerm_1 = 0.0f;
	}

	me->co_1 = me->pTerm_1 + me->iTerm_1 + me->dTerm_1;

	if (me->co_1 > me->oMax) {
		me->co_1 = me->oMax;
	} else if (me->co_1 < -me->oMax) {
		me->co_1 = -me->oMax;
	}
	return me->co_1;
}
float Update_cPIDStruct2(cPIDStruct *me, float setpoint, float position) {
	float p = me->pGain;
	float i = me->iGain;
	float d = me->dGain;
	float f = (me->fGain) ? me->fGain : 1.0f;
	float error = setpoint - position;

	// calculate the proportional term
	me->pTerm_1 = p * error;
	LimitToRange_Utility(me->pTerm_1, -me->pMax, me->pMax);

	// integration
	if (i) {
		me->iTerm_1 += i * error;
		LimitToRange_Utility(me->iTerm_1, -me->iMax, me->iMax);
	} else {
		me->iTerm_1 = 0;
	}
	// derivative
	if (d) {
		error = -position;
		me->dTerm_1 = (d) * (position - me->dState);
		me->dState = position;
		LimitToRange_Utility(me->dTerm_1, -me->dMax, me->dMax);
	} else {
		me->dTerm_1 = 0.0f;
	}
	me->co_1 = me->pTerm_1 + me->iTerm_1 + me->dTerm_1;
	LimitToRange_Utility(me->co_1, -me->oMax, me->oMax);
	return me->co_1;
}
