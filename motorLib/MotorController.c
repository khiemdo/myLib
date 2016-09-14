#include "MotorController.h"
#include <string.h>
#include "generalUtility.h"
#include "cAssert.h"

#include <math.h>

void Initialize_cMotorData(cMotorData *me) {
	memset(me, 0, sizeof(cMotorData));
}
void CheckPointerValid_cMotorData(cMotorData* me) {
	REQUIRE(me);
}
void Initialize_cMotorController(cMotorController* me) {
	memset(me, 0, sizeof(cMotorController));
}
void CheckPointerValid_cMotorController(cMotorController* me) {
	REQUIRE(me); REQUIRE(me->motorData); REQUIRE(me->motorEncoder); REQUIRE(me->motorPort);
	CheckPointerValid_cMotorPort(me->motorPort);
	REQUIRE(me->motorPositionPID); REQUIRE(me->motorVelocityPID);
}

int IsMotorControllerEnable_cMotorController(cMotorController* me) {
	return me->enableFlag;
}
void Enable_cMotorController(cMotorController* me) {
	EnablePort_MotorPort(me->motorPort);
	me->enableFlag = 1;
}
void Disable_cMotorController(cMotorController* me) {
	DisablePort_MotorPort(me->motorPort);
	me->enableFlag = 1;
}

void SetModeMotor_cMotorController(cMotorController* me, uint16_t mode) {
	me->motorMode = mode;
}
void SetMotorEncoder_cMotorController(cMotorController* me,
		cEncoder* setEncoder) {
	me->motorEncoder = setEncoder;
}
void SetMotorPort_cMotorController(cMotorController* me,
		cMotorPort* setMotorPort) {
	me->motorPort = setMotorPort;
}

void SetPIDVelocityMotor_cMotorController(cMotorController* me, cPIDStruct* pid) {
	me->motorVelocityPID = pid;
}
void SetPIDPositionMotor_cMotorController(cMotorController* me, cPIDStruct* pid) {
	me->motorPositionPID = pid;
}

void SetTargetVelocity_CloseLoop_cMotorController(cMotorController* me,
		float velocitySetpoint) {
	if (me->motorMode == CLOSED_LOOP_VELOCITY) {
		me->motorData->motorSetStopFlag = 0;
		me->motorData->motorVelocitySetpoint = velocitySetpoint;
	}
}
void SetTargetPosition_CloseLoop_cMotorController(cMotorController* me,
		int setPositionSetpoint) {
	if (me->motorMode == CLOSED_LOOP_POSITION) {
		me->motorData->motorSetStopFlag = 0;
		me->motorData->motorPositionSetpoint = setPositionSetpoint;
	}
}
float GetCurrentMotorSpeed_cMotorController(cMotorController* me) {
	return me->motorData->motorCurrentSpeed;
}
int GetCurrentMotorPosition_cMotorController(cMotorController* me) {
	return me->motorData->motorCurrentPosition;
}

inline int IsMotorControllerStop_cMotorController(cMotorController* me) {
	if (me->motorData->motorCurrentSpeed != 0) {
		return 0;
	} else
		return 1;
}
void StopMotorController_cMotorController(cMotorController* me) {
	SetSoftStop_MotorPort(me->motorPort);
	me->motorData->motorCurrentSpeed = 0;
	SetTargetPosToCurrentPos_cMotorController(me);
	ResetMotorDataExcludeSetpoints_cMotorController(me);
	me->motorData->motorSetStopFlag = 1;
}

void SetTargetPosToCurrentPos_cMotorController(cMotorController* me1) {
	cMotorData* me = me1->motorData;
	me->motorPositionSetpoint = me->motorCurrentPosition;
}
void ResetMotorDataExcludeSetpoints_cMotorController(cMotorController* me1) {
	cMotorData* me = me1->motorData;
	me->motorVelocitySetpoint = 0;
	me->motorVelocityRampedSetpoint = 0;
	me->motorIncrementalPWM = 0;
	me->motorOutputPWM = 0;
}
void CalculateMotorSpeed_cMotorController(cMotorController* me,
		unsigned int currentTime) {
	int deltaCounts;
	cMotorData * mdata = me->motorData;
	unsigned int deltaTicks = currentTime - mdata->lastTimeMotorDataLoop;
	mdata->motorCurrentPosition = GetCounts_cEncoder(me->motorEncoder); //will help to update EncoderCounter as well
	deltaCounts = mdata->motorCurrentPosition - mdata->motorPrevPosition;
	mdata->motorPrevPosition = mdata->motorCurrentPosition;
	//float rawSpeed = deltaCounts*encCONST/deltaTicks;
	float rawSpeed = (deltaCounts * SECONDSPERMINUTE
			* me->motorData->systemTimerFrequency * 1.0)
			/ (mdata->motorCountsPerRev * deltaTicks);
	mdata->motorCurrentSpeed += (0.2 * (rawSpeed - mdata->motorCurrentSpeed)); //low pass filter

	if (fabs(mdata->motorCurrentSpeed) < 10) {
		deltaTicks++;
	}

}

float RampUp_cMotorController(float setpoint, float rampedSetpoint, float inc) {
	if (setpoint > rampedSetpoint) {
		rampedSetpoint += (inc);
		if (rampedSetpoint > setpoint)
			rampedSetpoint = setpoint;
	} else if (setpoint < rampedSetpoint) {
		rampedSetpoint -= (inc);
		if (rampedSetpoint < setpoint)
			rampedSetpoint = setpoint;
	}
	return rampedSetpoint;
}
void UpdatePIDRoutine_cMotorController(cMotorController*me) {
	cMotorData * myMotorData = me->motorData;
	if (me->motorMode != OPENED_LOOP_VELOCITY) {
		if (me->motorMode == CLOSED_LOOP_POSITION) {
			myMotorData->motorCurrentPosition = GetCounts_cEncoder(
					me->motorEncoder);
			myMotorData->motorPositionSetpoint = LimitToRange_Utility(
					(float) myMotorData->motorPositionSetpoint,
					-myMotorData->motorPositionLimit,
					myMotorData->motorPositionLimit);
			myMotorData->motorPositionRampedSetpoint =
					myMotorData->motorPositionSetpoint;
			myMotorData->motorVelocitySetpoint = Update_cPIDStruct(
					me->motorPositionPID,
					(float) myMotorData->motorPositionRampedSetpoint,
					(float) myMotorData->motorCurrentPosition);
		}
		//ramp the velocity increase
		myMotorData->motorVelocityRampedSetpoint = RampUp_cMotorController(
				myMotorData->motorVelocitySetpoint,
				myMotorData->motorVelocityRampedSetpoint,
				myMotorData->motorRampingAcceleration
						/ myMotorData->systemTimerFrequency
						* myMotorData->motorControlLoopTicks);
		//PID for velocityCmd
		myMotorData->motorIncrementalPWM = Update_cPIDStruct(
				me->motorVelocityPID, myMotorData->motorVelocityRampedSetpoint,
				myMotorData->motorCurrentSpeed);
		myMotorData->motorOutputPWM += myMotorData->motorIncrementalPWM;
		myMotorData->motorOutputPWM = LimitToRange_Utility(
				myMotorData->motorOutputPWM, -myMotorData->motorPwmOutputLimit,
				myMotorData->motorPwmOutputLimit);

		//consider Stop?
		int setStop = 0;
		int errorDistance = abs(
				myMotorData->motorPositionSetpoint
						- myMotorData->motorCurrentPosition);
		int isInPosDeathbandCriteria = errorDistance
				< myMotorData->motorPositionDeadband;
		int isInVelDeathbandCriteria = fabsf(myMotorData->motorCurrentSpeed)
				< myMotorData->motorVelocityDeadBand
				&& fabsf(myMotorData->motorVelocityRampedSetpoint)
						< myMotorData->motorVelocityDeadBand;
		if (me->motorMode == CLOSED_LOOP_POSITION && (isInPosDeathbandCriteria))
			setStop = 1;
		if (me->motorMode == CLOSED_LOOP_VELOCITY && isInVelDeathbandCriteria)
			setStop = 1;
		if (me->motorData->motorSetStopFlag) {
			setStop = 1;
		}
		if (setStop == 1) {
			ResetMotorDataExcludeSetpoints_cMotorController(me);
		}
	}
	SetRotate_MotorPort(me->motorPort, (int) myMotorData->motorOutputPWM);
}
void Loop_MotorData_cMotorController(cMotorController* me) {
	uint32_t currentTime = HAL_GetTick();
	int32_t deltaTime = currentTime - me->motorData->lastTimeMotorDataLoop;
	if (deltaTime > me->motorData->motorDataLoopTicks) {
		CalculateMotorSpeed_cMotorController(me, currentTime);
		me->motorData->lastTimeMotorDataLoop = currentTime;
	}
}
void Loop_MotorController_cMotorController(cMotorController* me) {
	uint32_t currentTime = HAL_GetTick();
	int32_t deltaTime = currentTime
			- me->motorData->lastTimeMotorControllerLoop;
	if (deltaTime > me->motorData->motorControlLoopTicks) {
		if (IsMotorControllerEnable_cMotorController(me)) {
			UpdatePIDRoutine_cMotorController(me);
		}
		me->motorData->lastTimeMotorControllerLoop = currentTime;
	}
}
