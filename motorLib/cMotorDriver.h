#ifndef _cMotorDriver_h
#define _cMotorDriver_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "cAssert.h"
#include "stdlib.h"

typedef enum {
	UNDEFINED_Direction_MBSP, FORWARD_DIRECTION_MBSP, BACKWARD_DIRECTION_MBSP
} Direction_MBSP;
typedef enum {
	UNDEFINED_MotorDrvierType,
	PWMDRIVER_WITH_2DIRECTIONPINS,
	PWMDRIVER_WITH_1DIRECTIONPINS,
	DACDRIVER_WITH_2DIRECTIONPINS,
	DACDRIVER_WITH_1DIRECTIONPINS
} MotorDriverType;
typedef struct cMotorDriver_t{
	int id;
	int type;
	int enableFlag;
} cMotorDriver;

cMotorDriver* cMotorDriverConstructor();
//void SetMotorPowerValue();
//void GetMotorPowerValue();
//void DisableMotorPort();
//void EnableMotorPort();


#ifdef __cplusplus
}
#endif
#endif
