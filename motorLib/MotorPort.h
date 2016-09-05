/* Khiem
 * Dec 2, 2014
 * project: servo motor
 * description: to interface with the motor controller hardware
 *
 */

#ifndef _motorPort_h
#define _motorPort_h
#ifdef __cplusplus
extern "C" {
#endif

#include "deviceConfig.h"
#include "stdint.h"
#include "stm32f4xx_hal.h"

typedef struct {
	int32_t isEnable;
	int32_t id;
	uint16_t motorControlPin[2];
	GPIO_TypeDef *motorControlPort[2]; //0==index for forward, 1==index for reverse
	volatile uint32_t * motorTIM;
	volatile uint32_t * motorDAC;
} cMotorPort;

void Initialize_cMotorPort(cMotorPort * me);
void CheckPointerValid_cMotorPort(cMotorPort* me);

int IsMotorPortEnable_MotorPort(cMotorPort * me);
void EnablePort_MotorPort(cMotorPort * me);
void DisablePort_MotorPort(cMotorPort * me);
void SetRotate_MotorPort(cMotorPort * me, int iValue); //Port--> setPWM
void SetSoftStop_MotorPort(cMotorPort * me);


#ifdef __cplusplus
}
#endif
#endif
