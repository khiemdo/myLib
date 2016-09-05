#ifndef _generalUtility_h
#define _generalUtility_h
#ifdef __cplusplus
extern "C" {
#endif
#include "stdint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SWAP_UINT16T(x)		((((x)>>8)&0x00ff)|(((x)<<8)&0xff00))
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define WRITE_REGISTER(var) 	__asm volatile("mov " TOSTRING(var) ", %[" TOSTRING(var) "]" "\n\t" : : [var] "r" (var))
#define READ_REGISTER(var) 		__asm volatile("mov %[" TOSTRING(var) "], " TOSTRING(var) "\n\t" : [var] "=r" (var))
#define NELEM(x)		(sizeof(x)/sizeof(x[0]))

void ConvertStringToLowerCase(int8_t* buffer, int32_t length);
void checksum32bit();

void assert_failed(uint8_t* file, uint32_t line);
void SimpleDelay_Utility(int32_t count);

float_t LimitToRange_Utility(float_t input, float_t min, float_t max);
float_t Mapf_Utility(float_t value, float_t fromLow, float_t fromHigh, float_t toHigh, float_t toLow);
int16_t BitConverterToInt16_Utility(uint8_t * byte, int32_t index);
int32_t BitConverterToInt32_Utility(uint8_t * byte, int32_t index);
float_t BitConverterToFloat_Utility(uint8_t * byte, int32_t index);

#ifdef __cplusplus
}
#endif
#endif
