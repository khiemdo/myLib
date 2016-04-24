#include "main.h"
FILENUM(26);

#include "TestCanPort.h"
#include "Tumbler3BSP.h"
#include <stdio.h>
#include <stdlib.h>
#include "cCanPort.h"
#include "string.h"

CAN_HandleTypeDef _testCan;
CAN_HandleTypeDef * testCan;
CAN_FilterConfTypeDef sFilterConfig;
CanTxMsgTypeDef TxMessage;
CanRxMsgTypeDef RxMessage;

void TestCAN2Config(void) {
	memset(&_testCan,sizeof(CAN_HandleTypeDef),0);
	testCan = &_testCan;
	CAN2PortConfig(testCan);
	CAN2PortInit(testCan);

	testCan->pTxMsg = &TxMessage;
	testCan->pRxMsg = &RxMessage;

	CAN2FilterConfig1(testCan);
}

void TestCAN1Config(void) {
	memset(&_testCan,sizeof(CAN_HandleTypeDef),0);
	testCan = &_testCan;
	CAN1PortConfig(testCan);
	CAN1PortInit(testCan);

	testCan->pTxMsg = &TxMessage;
	testCan->pRxMsg = &RxMessage;

	CAN1FilterConfig1(testCan);
}

void TestCANSend(void) {
	testCan->pTxMsg->StdId = 0;
	testCan->pTxMsg->RTR = CAN_RTR_DATA;
	testCan->pTxMsg->IDE = CAN_ID_STD;
	testCan->pTxMsg->DLC = 2;
	testCan->pTxMsg->Data[0] = 0x01;
	testCan->pTxMsg->Data[1] = 0x01;
	HAL_CAN_Transmit(testCan, 10);

	testCan->pTxMsg->StdId = 1;
	testCan->pTxMsg->RTR = CAN_RTR_DATA;
	testCan->pTxMsg->IDE = CAN_ID_STD;
	testCan->pTxMsg->DLC = 2;
	testCan->pTxMsg->Data[0] = 0;
	testCan->pTxMsg->Data[1] = 0;
	HAL_CAN_Transmit(testCan, 10);

}
void TestCANSendIT(void) {
	testCan->pTxMsg->StdId = 0;
	testCan->pTxMsg->RTR = CAN_RTR_DATA;
	testCan->pTxMsg->IDE = CAN_ID_STD;
	testCan->pTxMsg->DLC = 2;
	testCan->pTxMsg->Data[0] = 0x01;
	testCan->pTxMsg->Data[1] = 0x01;
	HAL_CAN_Transmit_IT(testCan);
	testCan->pTxMsg->StdId = 1;
	testCan->pTxMsg->RTR = CAN_RTR_DATA;
	testCan->pTxMsg->IDE = CAN_ID_STD;
	testCan->pTxMsg->DLC = 2;
	testCan->pTxMsg->Data[0] = 0;
	testCan->pTxMsg->Data[1] = 0;
	HAL_CAN_Transmit_IT(testCan);
}
