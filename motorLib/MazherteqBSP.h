<<<<<<< HEAD
#ifndef	_cMazherteqBSP_h
#define _cMazherteqBSP_h
=======
#ifndef _MazherteqBSP_h
#define _MazherteqBSP_h
>>>>>>> abe91eb6d5ec1f6f3b1fa954ca6b47f6e5d3c882
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
<<<<<<< HEAD

void EncoderSPIConfig();
=======
#include "cAssert.h"
#include "stdlib.h"
#include "cMotorDriver.h"
#include "cPWMMotorDriverWith1DirectionPin.h"

void PWMDriveWith1DirectionPinConfig0_MBSP(cPWMMotorDriverWith1DirectionPin* me, uint32_t pwmClock, uint32_t pulses );
void PWMDriveWith1DirectionPinConfig1_MBSP(cPWMMotorDriverWith1DirectionPin* me, uint32_t pwmClock, uint32_t pulses );

//using port 9, pin 11
uint32_t* P9_11_EncoderPWMOutput_MBSP();
void SPI3PortConfig_MBSP(SPI_HandleTypeDef* hspi);
>>>>>>> abe91eb6d5ec1f6f3b1fa954ca6b47f6e5d3c882

#ifdef __cplusplus
}
#endif
#endif
