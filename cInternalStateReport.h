/****************************************************************/
/** @file:    cInternalStateReport.h
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		12/4/2015
 *  @version:	1.0
 *  @brief:   use cDebugUart to send structure of info about internal state
 *			of the machine
 *  @note: the format of the block msg is as follow
 *		[startFlag-1byte][id-2byte][length-1byte][content][cs-optional-2byte][endFlag-1byte]
 *
 ****************************************************************/

#ifndef _cInternalStateReport_h
#define _cInternalStateReport_h
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define START_FLAG       0xAA
#define END_FLAG         0xBB
#define START_FLAG_INDEX 0
#define ID_INDEX         1
#define LENGTH_INDEX     3
#define PAYLOAD_INDEX    4

#define DEFAULT_PERIOD   1000

typedef struct InternalStateStr {
    int8_t starFlag;
    uint16_t id;
}__attribute__((packed)) InternalState;

void InternalStateReportInitializeSingleton(void);
void SetInternalStatePtr(InternalState * myState);

void SetInternalStateReportLastTime(uint32_t lastTime);
void SetInternalStateReportFrequency(uint32_t periodTicks);

void InternalStateReportSend(void);

#ifdef __cplusplus
}
#endif
#endif /* ifndef _cInternalStateReport_h */
