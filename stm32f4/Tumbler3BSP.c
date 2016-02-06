#include "main.h"
FILENUM(23);

#include "Tumbler3BSP.h"

GPIO_TypeDef* STATUSLED_GPIO_PORT[STATUS_LEDn] = { STATUS_LED_0_PORT,
STATUS_LED_1_PORT,
STATUS_LED_2_PORT };
const uint16_t STATUSLED_GPIO_PIN[STATUS_LEDn] = { STATUS_LED_0_PIN,
STATUS_LED_1_PIN,
STATUS_LED_2_PIN };

CAN_HandleTypeDef * hcan2T3B;


void StatusLED_Init_T3B(StatusLED_T3B_TypeDef Led) {
	GPIO_InitTypeDef GPIO_InitStruct;
	STATUS_LED_CLK_ENABLE()
	;

	GPIO_InitStruct.Pin = STATUSLED_GPIO_PIN[Led];
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(STATUSLED_GPIO_PORT[Led], &GPIO_InitStruct);

	HAL_GPIO_WritePin(STATUSLED_GPIO_PORT[Led], STATUSLED_GPIO_PIN[Led],
			GPIO_PIN_RESET);
}
void StatusLED_On_T3B(StatusLED_T3B_TypeDef Led) {
	HAL_GPIO_WritePin(STATUSLED_GPIO_PORT[Led], STATUSLED_GPIO_PIN[Led],
			GPIO_PIN_SET);
}
void StatusLED_Off_T3B(StatusLED_T3B_TypeDef Led) {
	HAL_GPIO_WritePin(STATUSLED_GPIO_PORT[Led], STATUSLED_GPIO_PIN[Led],
			GPIO_PIN_RESET);
}
void StatusLED_Toggle_T3B(StatusLED_T3B_TypeDef Led) {
	HAL_GPIO_TogglePin(STATUSLED_GPIO_PORT[Led], STATUSLED_GPIO_PIN[Led]);
}

void VehicleCANPortConfig_T3B(void) {

}
