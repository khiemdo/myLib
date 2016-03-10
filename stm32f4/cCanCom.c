#include "main.h"
FILENUM(27)

#include "cCanCom.h"
#include "cRingBuffer.h"
#include "cCanPort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cAssert.h"

#define CANRX_BUFFER_SIZE	5
#define CANTX_BUFFER_SIZE	5

cCANCom* cc1;
cCANCom* cc2;
cCANCom* CANComConstructor() {
	return calloc(1, sizeof(cCANCom));
}
void CANComInit(cCANCom* me) {
	memset(me, 0, sizeof(cCANCom));
}
cCANCom* GetCAN1ComPtr(void) {
	return cc1;
}
cCANCom* GetCAN2ComPtr(void) {
	return cc2;
}
int32_t CheckHasAnyCANMsgInBuff(RingBuffer* buff) {
	return GetNumberByteUsedOfRBuffer(buff) > 0;
}
int32_t IsCANBufferEmpty(RingBuffer* buff) {
	return ((buff->active) == 0);
}
void CanComControllerLoop(cCANCom* me) {
	//TODO
//	CANCom_TxCpltCallback(me->myCANx);

	if (me->failRearmCAN_FIFO0Signal) {
		HAL_StatusTypeDef ret = HAL_CAN_Receive_IT(me->myCANx, CAN_FIFO0);
		if (ret == HAL_BUSY)
			me->failRearmCAN_FIFO0Signal = 1;
		else
			me->failRearmCAN_FIFO0Signal = 0;
	}
	if (me->failRearmCAN_FIFO1Signal) {
		HAL_StatusTypeDef ret = HAL_CAN_Receive_IT(me->myCANx, CAN_FIFO1);
		if (ret == HAL_BUSY)
			me->failRearmCAN_FIFO1Signal = 1;
		else
			me->failRearmCAN_FIFO1Signal = 0;
	}
}
void CANCom_RxCpltCallback(CAN_HandleTypeDef* me) {
//#if CANID==1
//	cCANCom* cc = GetCAN1ComPtr();
//#elif CANID==2
//	cCANCom* cc = GetCAN2ComPtr();
//#endif
//	if (cc != 0 && cc->rxDebugDataRingBuffer != 0) {
//		REQUIRE(GetNumberByteLeftOfRBuffer(cc->rxDebugDataRingBuffer) >= 0);
//		PushRingBuffer(cc->rxDebugDataRingBuffer, cc->myCANx->pRxMsg);
//	}
}
void CANCom_TxCpltCallback(CAN_HandleTypeDef* me) {
//#if CANID==1
//	cCANCom* cc = GetCAN1ComPtr();
//#elif CANID==2
//	cCANCom* cc = GetCAN2ComPtr();
//#endif
//	if (cc != 0 && cc->txDebugDataRingBuffer != 0) {
//		if (CheckHasAnyCANMsgInBuff(cc->txDebugDataRingBuffer)) {
//			PopRingBuffer(cc->txDebugDataRingBuffer, cc->myCANx->pTxMsg);
//			HAL_StatusTypeDef ret = HAL_CAN_Transmit(cc->myCANx, 5);
//			if (ret == HAL_BUSY || ret == HAL_ERROR) {
//				PushRingBuffer(cc->txDebugDataRingBuffer, cc->myCANx->pTxMsg);
//			} else if (ret == HAL_TIMEOUT || ret == HAL_ERROR) {
//				if (ret == HAL_TIMEOUT) {
//					DEBUG(LOG_ERROR, "HAL_CAN_TIMEOUT\r\n", 0);
//				} else {
//					DEBUG(LOG_ERROR, "HAL_CAN_ERROR code:%d\r\n",
//							cc->myCANx->ErrorCode);
//				}
//			}
//		}
//	}
}

int32_t CANComSendMsg1(cCANCom* me) {
	int32_t ret = -1;
	if (me->enableFlag) {
		HAL_CAN_StateTypeDef canState = HAL_CAN_GetState(me->myCANx);
		if (canState == HAL_CAN_STATE_READY
				|| canState == HAL_CAN_STATE_TIMEOUT) {
			if (CheckHasAnyCANMsgInBuff(me->txDebugDataRingBuffer)) {
				REQUIRE(
						GetNumberByteLeftOfRBuffer(me->txDebugDataRingBuffer)
								> 0);
				PushRingBuffer(me->txDebugDataRingBuffer, me->myCANx->pTxMsg);
				ret = 1;
			} else {
				if (canState == HAL_CAN_STATE_TIMEOUT)
					me->myCANx->State = HAL_CAN_STATE_READY;
				HAL_CAN_Transmit_IT(me->myCANx);
				ret = 0;
			}
		} else {
			REQUIRE(GetNumberByteLeftOfRBuffer(me->txDebugDataRingBuffer) > 0);
			PushRingBuffer(me->txDebugDataRingBuffer, me->myCANx->pTxMsg);
			ret = 2;
		}
	}

	return ret;
}
int32_t CANComSendMsg(cCANCom* me) {
	int32_t ret = -1;
	if (me->enableFlag) {
		if (CheckHasAnyCANMsgInBuff(me->txDebugDataRingBuffer)) { //if alr has pending msg in rBuff, cont to push2RB
			REQUIRE(GetNumberByteLeftOfRBuffer(me->txDebugDataRingBuffer) > 0);
			PushRingBuffer(me->txDebugDataRingBuffer, me->myCANx->pTxMsg);
			ret = 1;
		} else {
			HAL_StatusTypeDef res = HAL_CAN_Transmit(me->myCANx, 5);
			if (res == HAL_BUSY) {
				REQUIRE(
						GetNumberByteLeftOfRBuffer(me->txDebugDataRingBuffer)
								> 0);
				PushRingBuffer(me->txDebugDataRingBuffer, me->myCANx->pTxMsg);
				ret = 2;
			} else if (ret == HAL_TIMEOUT || ret == HAL_ERROR) {
				if (ret == HAL_TIMEOUT) {
					DEBUG(LOG_ERROR, "HAL_CAN_TIMEOUT\r\n", 0);
				} else {
					DEBUG(LOG_ERROR, "HAL_CAN_ERROR code:%d\r\n",
							me->myCANx->ErrorCode);
				}
			} else {
				ret = 0;
			}

		}
	}
	return ret;
}

int32_t CANComReadMsg(cCANCom* me, CanRxMsgTypeDef* rxMsg) {
	int32_t ret = -1;
	if (me->enableFlag) {
		ret = PopRingBuffer(me->rxDebugDataRingBuffer, rxMsg);
	}
	return ret;
}

void CANComConfigUsingCan1(cCANCom * me) {
	cc1 = me;
	me->id = 1;
	me->rxDebugDataRingBuffer = RingBufferConstructor();
	REQUIRE(me->rxDebugDataRingBuffer != 0);
	RingBufferConfig(me->rxDebugDataRingBuffer, CANRX_BUFFER_SIZE,
			sizeof(CanRxMsgTypeDef));
	me->txDebugDataRingBuffer = RingBufferConstructor();
	REQUIRE(me->txDebugDataRingBuffer != 0);
	RingBufferConfig(me->txDebugDataRingBuffer, CANTX_BUFFER_SIZE,
			sizeof(CanTxMsgTypeDef));
	me->myCANx = calloc(1, sizeof(CAN_HandleTypeDef));
	CAN1PortConfig(me->myCANx);
	CAN1PortInit(me->myCANx);

	me->myCANx->pTxMsg = calloc(1, sizeof(CanTxMsgTypeDef));
	me->myCANx->pRxMsg = calloc(1, sizeof(CanRxMsgTypeDef));
	CAN1FilterConfig1(me->myCANx);

	me->enableFlag = 1;
}
void CANComConfigUsingCan2(cCANCom * me) {
	cc2 = me;
	me->id = 2;
	me->rxDebugDataRingBuffer = RingBufferConstructor();
	REQUIRE(me->rxDebugDataRingBuffer != 0);
	RingBufferConfig(me->rxDebugDataRingBuffer, CANRX_BUFFER_SIZE,
			sizeof(CanRxMsgTypeDef));
	me->txDebugDataRingBuffer = RingBufferConstructor();
	REQUIRE(me->txDebugDataRingBuffer != 0);
	RingBufferConfig(me->txDebugDataRingBuffer, CANTX_BUFFER_SIZE,
			sizeof(CanTxMsgTypeDef));
	me->myCANx = calloc(1, sizeof(CAN_HandleTypeDef));
	CAN2PortConfig(me->myCANx);
	CAN2PortInit(me->myCANx);

	me->myCANx->pTxMsg = calloc(1, sizeof(CanTxMsgTypeDef));
	me->myCANx->pRxMsg = calloc(1, sizeof(CanRxMsgTypeDef));
	CAN2FilterConfig1(me->myCANx);

	//TODO: use HAL_CAN_Receive_IT, if correct plz edit CANComConfigUsingCan1 as well
	HAL_StatusTypeDef ret = HAL_CAN_Receive_IT(me->myCANx, CAN_FIFO0);
	if (ret == HAL_BUSY)
		me->failRearmCAN_FIFO1Signal = 1;
	ret = HAL_CAN_Receive_IT(me->myCANx, CAN_FIFO1);
	if (ret == HAL_BUSY)
		me->failRearmCAN_FIFO1Signal = 1;

	me->enableFlag = 1;

}
