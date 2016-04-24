#include "main.h"
FILENUM(28)

#include "TestcCanCom.h"
#include "cCanCom.h"
#include <stdlib.h>
#include "cDebugUart.h"
#include "cAssert.h"

cCANCom* ccTest;

void TestcCanComConfig(void){
	ccTest = CANComConstructor();
	CANComConfigUsingCan2(ccTest);
}
void TestcCanComSend(void){
	ccTest->myCANx->pTxMsg->StdId = 0x01;
	ccTest->myCANx->pTxMsg->RTR = CAN_RTR_DATA;
	ccTest->myCANx->pTxMsg->IDE = CAN_ID_STD;
	ccTest->myCANx->pTxMsg->DLC = 2;
	ccTest->myCANx->pTxMsg->Data[0] = 0x01;
	ccTest->myCANx->pTxMsg->Data[1] = 0x01;
	CANComSendMsg(ccTest);
//	HAL_Delay(10);
	ccTest->myCANx->pTxMsg->StdId = 0;
	ccTest->myCANx->pTxMsg->RTR = CAN_RTR_DATA;
	ccTest->myCANx->pTxMsg->IDE = CAN_ID_STD;
	ccTest->myCANx->pTxMsg->DLC = 2;
	ccTest->myCANx->pTxMsg->Data[0] = 0;
	ccTest->myCANx->pTxMsg->Data[1] = 0;
	CANComSendMsg(ccTest);

	CanComControllerLoop(ccTest);
}
void TestcCanComRead(void){
	if (!IsCANBufferEmpty(ccTest->rxDebugDataRingBuffer)) {
		CanRxMsgTypeDef rxTest;
		CANComReadMsg(ccTest,&rxTest);
		UDebugPrintf("%x|%u\r\n", rxTest.StdId, rxTest.DLC);
	}
}
