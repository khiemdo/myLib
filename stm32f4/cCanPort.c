#include "main.h"
FILENUM(25);

#include "cCanPort.h"

static int CAN1_CLK_ENABLED = 0;

void CAN2GPIOInit(void) {
	__GPIOB_CLK_ENABLE()
	;
	GPIO_InitTypeDef GPIO_InitStruct;
	/**CAN2 GPIO Configuration
	 PB12     ------> CAN2_RX
	 PB13     ------> CAN2_TX
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void CAN1GPIOInit(void) {
	__GPIOA_CLK_ENABLE()
	;
	GPIO_InitTypeDef GPIO_InitStruct;
	/**CAN1 GPIO Configuration
	 PA11     ------> CAN1_RX
	 PA12     ------> CAN1_TX
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//TODO what the fuck happen here
//	GPIO_InitStruct.Pin = GPIO_PIN_12;
//	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
//	GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//	GPIO_InitStruct.Pin = GPIO_PIN_11;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void CAN2NVICInit(CAN_HandleTypeDef* hcan) {
//	HAL_NVIC_SetPriority(CAN2_TX_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(CAN2_TX_IRQn);
	HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
	HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
//	HAL_NVIC_SetPriority(CAN2_SCE_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(CAN2_SCE_IRQn);

	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_FMP0);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_FF0);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_FOV0);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_FMP1);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_FF1);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_FOV1);

//	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_EWG);
//	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_EPV);
//	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_BOF);
//	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_LEC);
//	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_ERR);

}
void CAN1NVICInit(CAN_HandleTypeDef* hcan) {
	HAL_NVIC_SetPriority(CAN1_TX_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
	HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
	HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
	HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);

	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_FMP0);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_FF0);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_FOV0);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_FMP1);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_FF1);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_FOV1);

	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_EWG);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_EPV);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_BOF);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_LEC);
	__HAL_CAN_ENABLE_IT(hcan, CAN_IT_ERR);
}

void CAN2CANInit(CAN_HandleTypeDef* hcan) {
	CAN1_CLK_ENABLED++;
	if (CAN1_CLK_ENABLED == 1) {
		__CAN1_CLK_ENABLE()
		;
	}
	__CAN2_CLK_ENABLE()
	;

	hcan->Instance = CAN2;
	hcan->Init.Prescaler = 4;
	hcan->Init.Mode = CAN_MODE_NORMAL;
	hcan->Init.SJW = CAN_SJW_1TQ;
	hcan->Init.BS1 = CAN_BS1_14TQ;
	hcan->Init.BS2 = CAN_BS2_6TQ;
	hcan->Init.TTCM = DISABLE;
	hcan->Init.ABOM = DISABLE;
	hcan->Init.AWUM = DISABLE;
	hcan->Init.NART = DISABLE;
	hcan->Init.RFLM = DISABLE;
	hcan->Init.TXFP = ENABLE;
	HAL_CAN_Init(hcan);
}
void CAN1CANInit(CAN_HandleTypeDef* hcan) {
	CAN1_CLK_ENABLED++;
	if (CAN1_CLK_ENABLED == 1) {
		__CAN1_CLK_ENABLE()
		;
	}

	hcan->Instance = CAN1;
	hcan->Init.Prescaler = 4;
	hcan->Init.Mode = CAN_MODE_NORMAL;
	hcan->Init.SJW = CAN_SJW_1TQ;
	hcan->Init.BS1 = CAN_BS1_14TQ;
	hcan->Init.BS2 = CAN_BS2_6TQ;
	hcan->Init.TTCM = DISABLE;
	hcan->Init.ABOM = DISABLE;
	hcan->Init.AWUM = DISABLE;
	hcan->Init.NART = DISABLE;
	hcan->Init.RFLM = DISABLE;
	hcan->Init.TXFP = ENABLE;
	HAL_CAN_Init(hcan);
}

void CAN1FilterConfig1(CAN_HandleTypeDef* hcan) {
	CAN_FilterConfTypeDef sFilterConfig;
	sFilterConfig.FilterNumber = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = 0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.BankNumber = 14;
	HAL_CAN_ConfigFilter(hcan, &sFilterConfig);

}
void CAN2FilterConfig1(CAN_HandleTypeDef* hcan) {
	CAN_FilterConfTypeDef sFilterConfig;

	sFilterConfig.FilterNumber = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = 0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.BankNumber = 14;
	HAL_CAN_ConfigFilter(hcan, &sFilterConfig);

	sFilterConfig.FilterNumber = 14;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = 0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.BankNumber = 14;
	HAL_CAN_ConfigFilter(hcan, &sFilterConfig);

}
void CAN2PortConfig(CAN_HandleTypeDef *hcan) {
	CAN2CANInit(hcan);
}
void CAN2PortInit(CAN_HandleTypeDef *hcan) {
	if (hcan->Instance == CAN2) {
		CAN2GPIOInit();
		CAN2NVICInit(hcan);
	}
}
void CAN2PortDeInit(CAN_HandleTypeDef *hcan) {
	if (hcan->Instance == CAN2) {
		__CAN2_CLK_DISABLE();
		CAN1_CLK_ENABLED--;
		if (CAN1_CLK_ENABLED == 0) {
			__CAN1_CLK_DISABLE();
		}
		/**CAN2 GPIO Configuration
		 PB12     ------> CAN2_RX
		 PB13     ------> CAN2_TX
		 */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12 | GPIO_PIN_13);

		/* Peripheral interrupt DeInit*/
		HAL_NVIC_DisableIRQ(CAN2_TX_IRQn);
		HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
		HAL_NVIC_DisableIRQ(CAN2_RX1_IRQn);
		HAL_NVIC_DisableIRQ(CAN2_SCE_IRQn);
	}
}

void CAN1PortConfig(CAN_HandleTypeDef *hcan) {
	CAN1CANInit(hcan);
}
void CAN1PortInit(CAN_HandleTypeDef *hcan) {
	if (hcan->Instance == CAN1) {
		CAN1GPIOInit();
		CAN1NVICInit(hcan);
	}
}
void CAN1PortDeInit(CAN_HandleTypeDef *hcan) {
	if (hcan->Instance == CAN1) {
		CAN1_CLK_ENABLED--;
		if (CAN1_CLK_ENABLED == 0) {
			__CAN1_CLK_DISABLE();
		}

		/**CAN2 GPIO Configuration
		 PB12     ------> CAN2_RX
		 PB13     ------> CAN2_TX
		 */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_11 | GPIO_PIN_12);

		/* Peripheral interrupt DeInit*/
		HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
		HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
		HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
		HAL_NVIC_DisableIRQ(CAN1_SCE_IRQn);
	}
}

