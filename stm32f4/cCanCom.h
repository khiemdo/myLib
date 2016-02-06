/****************************************************************/
/** @file:      cCanCom.h
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		Dec 27, 2015
 *  @version:	1.0
 *  @brief:     contain the canCom interface with ring buffer implementation
 *
 *  @note:
 *
 ****************************************************************/
#ifndef _cCanCom_h
#define _cCanCom_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#if	CANID == 1
#define CAN_ADR	CAN1
#elif CANID ==2
#define CAN_ADR CAN2
#endif

typedef struct RingBufferStr RingBuffer;
typedef struct CANCommStr {
	int32_t id;
	uint32_t enableFlag;
	volatile uint32_t failRearmCAN_FIFO0Signal, failRearmCAN_FIFO1Signal;//0=ok;1=failedSingal
	RingBuffer* rxDebugDataRingBuffer;
	RingBuffer* txDebugDataRingBuffer;
	CAN_HandleTypeDef* myCANx;
} cCANCom;

cCANCom* CANComConstructor();
void CANComInit(cCANCom* me);
cCANCom* GetCAN1ComPtr(void);
cCANCom* GetCAN2ComPtr(void);
void CANComConfigUsingCan1(cCANCom * me);
void CANComConfigUsingCan2(cCANCom * me);
void CANCom_RxCpltCallback(CAN_HandleTypeDef* me);
void CANCom_TxCpltCallback(CAN_HandleTypeDef* me);

int32_t IsCANBufferEmpty(RingBuffer* buff);
int32_t CheckHasAnyCANMsgInBuff(RingBuffer* buff);

int32_t CANComSendMsg(cCANCom* me);
int32_t CANComReadMsg(cCANCom* me, CanRxMsgTypeDef* rxMsg);
void CanComControllerLoop(cCANCom* me);

#ifdef __cplusplus
}
#endif
#endif
