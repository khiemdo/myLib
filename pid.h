#ifndef pid_h
#define pid_h

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
/* Khiem
 * Jul 29, 2015
 * project: motor library
 * description:
 * 		ref: http://www.mstarlabs.com/apeng/techniques/pidsoftw.html
 */

typedef struct {
	int32_t id;
	int isEnable;
	uint32_t sampleTime;
	//pid state
	float setPoint; // Last setpoint
	float dState, iState;
	float pTerm_1, iTerm_1, dTerm_1;
	float co_1;
	//PID para
	float iGain; // integral gain
	float pGain; // proportional gain
	float dGain; // derivative gain
	float fGain; // low pass filter factor (1 - pole) for derivative gain
	float pMax, iMax, dMax, oMax;
	float iStateMax;
	float delKp; //handle Unbalanced Output Drive
	float Kz; //feed forward compensation
} cPIDStruct;

void SetTunings_cPIDStruct(cPIDStruct* me, float p, float i, float d);
void SetLimits_cPIDStruct(cPIDStruct* me, float pMax, float iMax, float dMax,
		float oMax);
void SetSamplingTime_cPIDStruct(cPIDStruct* me, uint32_t newSampleTime) ;
void ResetPID_cPIDStruct(cPIDStruct* me, float currentPos, float output);

void Initialize_cPIDStruct(cPIDStruct* me);
void CheckPointerValid_cPIDStruct(cPIDStruct* me);
void Configure_cPIDStruct(cPIDStruct* me, float p, float i, float d, float f, float pMax,
		float iMax, float iStateMax, float dMax, float oMax, float delKp,
		float Kz);
float Update_cPIDStruct(cPIDStruct *pid, float setpoint, float position);
float Update_cPIDStruct2(cPIDStruct *me, float setpoint, float position);
#ifdef __cplusplus
}
#endif
#endif /* ifndef _cAssert_h */
