/* Khiem
 * Dec 2, 2014
 * project:servo motor
 * description: is to make use motorPort interface, process motor_t data, control PID loop
 *
 */

#ifndef _motorController_h
#define _motorController_h
#ifdef __cplusplus
extern "C" {
#endif

#include "MotorPort.h"
#include "Encoder.h"
#include "pid.h"
#include "cAbsEncoder.h"
#include "stdint.h"

#define SECONDSPERMINUTE	(60.0)
typedef enum MotorModeEnum {
	OPENED_LOOP_VELOCITY = 0,
	CLOSED_LOOP_VELOCITY,
	OPENED_LOOP_POSITION,
	CLOSED_LOOP_POSITION
} MotorModeEnum;

typedef enum DirectionEnum {
	FORWARD = 0, REVERSE = 1
} DirectionEnum;

typedef struct motor_data {
	int32_t id;
	int32_t motorSetStopFlag;

	int32_t motorCurrentPosition;
	float motorCurrentSpeed;
	float motorCurrentAcceleration;

	int32_t motorPrevPosition;
	uint32_t lastTimeMotorDataLoop; //for calculate speed
	uint32_t lastTimeMotorControllerLoop;
	uint32_t motorControlLoopTicks;
	uint32_t motorDataLoopTicks;
	uint32_t systemTimerFrequency;
	float motorCountsPerRev;
	float motorPositionLimit;
	float motorVelocityLimit;
	float motorAccelerationLimit; //used in close loop
	float motorPwmLimit;

	int32_t motorPositionDeadband;
	float motorVelocityDeadBand;
	float motorAccelerationDeadband;

	int32_t motorPositionSetpoint;
	float motorPositionRampedSetpoint;
	float motorVelocitySetpoint; //using with motorVelocityRampedSetpoint or motorAccelerationLimit to ramp the change of velocity
	float motorVelocityRampedSetpoint; //used in open loop
	float motorAccelerationSetpoint;
	float motorAccelerationRampedSetpoint;

	float motorIncrementalPWM; //resulted in the velocity PID loop
	float motorOutputPWM; //convert to abs base
} cMotorData;

typedef struct MotorController {
	int32_t id;
	int32_t enableFlag;
	int32_t motorMode;
	cMotorPort* motorPort;
	cEncoder * motorEncoder; //it s attached with the motor
	cMotorData* motorData;
	cPIDStruct* motorVelocityPID;
	cPIDStruct* motorPositionPID;
} cMotorController;

void Initialize_cMotorData(cMotorData *me);
void CheckPointerValid_cMotorData(cMotorData* me);
void Initialize_cMotorController(cMotorController* me);
void CheckPointerValid_cMotorController(cMotorController* me);

void MotorDataConfig0(cMotorData *me);
void MotorControllerConfig0(cMotorController* me);
void MotorControllerConfigForMAT(cMotorController* me, int index,
		cMotorData* motorData, cMotorPort* motorPort, cPIDStruct* veloPID,
		cPIDStruct* posPID, cEncoder* motorEncoder);
int IsMotorControllerEnable_cMotorController(cMotorController* me);
void Enable_cMotorController(cMotorController* me);
void Disable_cMotorController(cMotorController* me);

void SetMotorEncoder_cMotorController(cMotorController* me,
		cEncoder* setEncoder);
void SetMotorPort_cMotorController(cMotorController* me,
		cMotorPort* setMotorPort);
void SetPIDVelocityMotor_cMotorController(cMotorController* me, cPIDStruct* pid);
void SetPIDPositionMotor_cMotorController(cMotorController* me, cPIDStruct* pid);

void SetModeMotor_cMotorController(cMotorController* me, uint16_t mode);
void SetTargetVelocity_CloseLoop_cMotorController(cMotorController* me,
		float velocitySetpoint);
void SetTargetPosition_CloseLoop_cMotorController(cMotorController* me,
		int setPositionSetpoint);
float GetCurrentMotorSpeed_cMotorController(cMotorController* me);
int GetCurrentMotorPosition_cMotorController(cMotorController* me);

int IsMotorControllerStop_cMotorController(cMotorController* me);
void StopMotorController_cMotorController(cMotorController* me);
void SetTargetPosToCurrentPos_cMotorController(cMotorController* me1);
void ResetMotorDataExcludeSetpoints_cMotorController(cMotorController* me1);

void Loop_MotorData_cMotorController(cMotorController* me);
void Loop_MotorController_cMotorController(cMotorController* me);

#ifdef __cplusplus
}
#endif
#endif
