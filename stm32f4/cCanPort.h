/****************************************************************/
/** @file:      cCanPort.h
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		Dec 27, 2015
 *  @version:	1.0
 *  @brief:     configure hardware to use canPort
 *
 *  @note:
 *
 ****************************************************************/
#ifndef _cCanPort_h
#define _cCanPort_h
#ifdef __cplusplus
extern "C" {
#endif


void CAN1PortConfig(CAN_HandleTypeDef *hcan);
void CAN1PortInit(CAN_HandleTypeDef *hcan);
void CAN1PortDeInit(CAN_HandleTypeDef *hcan);

void CAN2PortConfig(CAN_HandleTypeDef *hcan);
void CAN2PortInit(CAN_HandleTypeDef *hcan);
void CAN2PortDeInit(CAN_HandleTypeDef *hcan);

void CAN1FilterConfig1(CAN_HandleTypeDef* hcan);
void CAN2FilterConfig1(CAN_HandleTypeDef* hcan);

#ifdef __cplusplus
}
#endif
#endif
