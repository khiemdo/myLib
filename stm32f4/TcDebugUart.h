#ifndef _TcDebugUart_h
#define _TcDebugUart_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void TPrinf(void);
void TPrinfRbuffAssync(void);
void TPrinfFloat(void);
void TIsUsartTransferComplete(void);
void TcUartMirroInputNOutput(void);

#ifdef __cplusplus
}
#endif
#endif
