#include "main.h"
FILENUM(6);

#include "TestcInternalStateReport.h"
#include <stdio.h>
#include <stdlib.h>

ProjectInternalState * myProjectState;

void TestcInternalStateReportConfig(void){
    myProjectState = calloc(1, sizeof(ProjectInternalState));
    InternalStateReportInitializeSingleton();
    SetInternalStatePtr((InternalState *)myProjectState);
}
void TestcInternalStateReportLoop(void){
    static uint32_t lastTime = 0;
    uint32_t currentTime = HAL_GetTick();
    int32_t deltaTime = currentTime - lastTime;

    if (deltaTime > 1000) {
        myProjectState->length = sizeof(ProjectInternalState);
        myProjectState->super.id = HAL_GetTick();
        myProjectState->para1 = 1;
        myProjectState->para2 = 100;
        InternalStateReportSend();
        lastTime = currentTime;
    }
}
