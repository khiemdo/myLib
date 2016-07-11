#ifndef _generalUtility_h
#define _generalUtility_h
#ifdef __cplusplus
extern "C" {
#endif
#include "stdint.h"

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
#define SWAP_UINT16T(x)		((((x)>>8)&0x00ff)|(((x)<<8)&0xff00))

void ConvertStringToLowerCase(int8_t* buffer, int32_t length);

#ifdef __cplusplus
}
#endif
#endif
