#ifndef _TcDebugUart_h
#define _TcDebugUart_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void TPrinf(void);
void TPrinfRbuffAssync(void);
void TPrinfInBurst(void);
void TPrinfFloat(void);
void TSimplePrintf(void);
void TSimplePrintfInBurst(void);	
void TcUartMirroInputNOutput(void);

#ifdef __cplusplus
}
#endif
#endif

