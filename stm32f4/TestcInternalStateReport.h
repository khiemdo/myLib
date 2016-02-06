#ifndef _TestcInternalStateReport_h
#define _TestcInternalStateReport_h
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "cInternalStateReport.h"

typedef struct ProjectInternalStateStr {
    InternalState super;
    uint8_t length;
    int32_t para1;
    int32_t para2;
    /*add ur system para here*/

    int8_t endFlag;
}__attribute__((packed)) ProjectInternalState;

void TestcInternalStateReportConfig(void);
void TestcInternalStateReportLoop(void);

#ifdef __cplusplus
}
#endif
#endif
