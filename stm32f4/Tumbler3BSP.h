/****************************************************************/
/** @file:      Tumbler3BSP.h
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		Dec 27, 2015
 *  @version:	1.0
 *  @brief:     board support packages for tumbler 3 board
 *
 *  @note:
 *
****************************************************************/

#ifndef _tumbler3Bsp_h
#define _tumbler3Bsp_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define STATUS_LEDn							3

#define STATUS_LED0							STATUS_CPU_Usage
#define STATUS_LED1							STATUS_CAN_NETWORK
#define STATUS_LED2							STATUS_ERROR

#define STATUS_LED_2_PIN					GPIO_PIN_13
#define STATUS_LED_2_PORT					GPIOC

#define STATUS_LED_1_PIN					GPIO_PIN_14
#define STATUS_LED_1_PORT					GPIOC

#define STATUS_LED_0_PIN					GPIO_PIN_15
#define STATUS_LED_0_PORT					GPIOC

#define STATUS_LED_CLK_ENABLE()			__GPIOC_CLK_ENABLE()
#define STATUS_LED_CLK_DISABLE()		__GPIOC_CLK_DISABLE()

typedef enum {
	STATUS_LED_0 = 0, STATUS_LED_1 = 1, STATUS_LED_2 = 2
} StatusLED_T3B_TypeDef;

void StatusLED_Init_T3B(StatusLED_T3B_TypeDef Led);
void StatusLED_On_T3B(StatusLED_T3B_TypeDef Led);
void StatusLED_Off_T3B(StatusLED_T3B_TypeDef Led);
void StatusLED_Toggle_T3B(StatusLED_T3B_TypeDef Led);

void VehicleCANPortConfig_T3B(void);
void CAN2PortConfig(CAN_HandleTypeDef *hcan);
void CAN2PortInit(CAN_HandleTypeDef *hcan);
void CAN2PortDeInit(CAN_HandleTypeDef *hcan);
void CAN1PortConfig(CAN_HandleTypeDef *hcan);
void CAN1PortInit(CAN_HandleTypeDef *hcan);
void CAN1PortDeInit(CAN_HandleTypeDef *hcan);

#ifdef __cplusplus
}
#endif
#endif
