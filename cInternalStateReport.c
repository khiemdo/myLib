#include "main.h"
FILENUM(5);

#include "cInternalStateReport.h"
#include "cDebugUart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct InternalStateReportStr {
    InternalState * myState;
    uint32_t lastTime;
    int32_t periodOfReport;
}InternalStateReport;

static InternalStateReport * myStateReport;

void InternalStateReportInitializeSingleton(void){
    myStateReport = calloc(1, sizeof(InternalStateReport));
    myStateReport->lastTime = 0;
    myStateReport->periodOfReport = DEFAULT_PERIOD;
}
void SetInternalStatePtr(InternalState * myState){
    myStateReport->myState = myState;
}
void SetInternalStateReportFrequency(uint32_t periodTicks){
    myStateReport->periodOfReport = periodTicks;
}
void SetInternalStateReportLastTime(uint32_t lastTime){
    myStateReport->lastTime = lastTime;
}

void InternalStateReportSend(){
    unsigned currentTime = HAL_GetTick();
    int32_t deltaTime = currentTime - myStateReport->lastTime;

    if (deltaTime > myStateReport->periodOfReport) {
        int32_t reportLength = (int32_t)*((int8_t *)(((int32_t)myStateReport->myState) + LENGTH_INDEX));
        myStateReport->myState->starFlag = START_FLAG;
        *((int8_t *)((int32_t)(myStateReport->myState) + reportLength - 1)) = END_FLAG;
        UDebugSendRaw((char *)myStateReport->myState, reportLength);
        myStateReport->lastTime = currentTime;
    }
}
