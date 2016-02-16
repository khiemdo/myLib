 #include "main.h"
FILENUM(11);

#include "cUartPort.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "cAssert.h"

/****************************************************************/
/** @brief: just configure gpio of uart
 *  @details: used in Uart3Debug_Init
 ****************************************************************/
void Uart3GPIOInit(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	__GPIOB_CLK_ENABLE()
	;
	/**USART3 GPIO Configuration
	 PB10     ------> USART3_TX
	 PB11     ------> USART3_RX
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void Uart2GPIOInit(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	__GPIOA_CLK_ENABLE()
	;
	/**USART3 GPIO Configuration
	 Pa2     ------> USART3_TX
	 Pa3     ------> USART3_RX
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/****************************************************************/
/** @brief: just configure DMA of uart
 *  @details: used in Uart3Debug_Init
 ****************************************************************/
void Uart3DMAInit(UART_HandleTypeDef * huart) {
	__HAL_RCC_DMA1_CLK_ENABLE()
	;

    huart->hdmatx = (DMA_HandleTypeDef *)calloc(1, sizeof(DMA_HandleTypeDef));
    REQUIRE(huart->hdmatx != 0);
    huart->hdmatx->Instance = DMA1_Channel2;
    huart->hdmatx->Init.Direction = DMA_MEMORY_TO_PERIPH;
    huart->hdmatx->Init.PeriphInc = DMA_PINC_DISABLE;
    huart->hdmatx->Init.MemInc = DMA_MINC_ENABLE;
    huart->hdmatx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    huart->hdmatx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    huart->hdmatx->Init.Mode = DMA_NORMAL;
    huart->hdmatx->Init.Priority = DMA_PRIORITY_LOW;
    HAL_DMA_Init(huart->hdmatx);
    huart->hdmatx->Parent = huart;

	HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
} /* Uart3DMAInit */

void Uart2DMAInit(UART_HandleTypeDef* huart) {
	__HAL_RCC_DMA1_CLK_ENABLE()
	;

    huart->hdmatx = (DMA_HandleTypeDef *)calloc(1, sizeof(DMA_HandleTypeDef));
    REQUIRE(huart->hdmatx != 0);
    huart->hdmatx->Instance = DMA1_Channel7;
    huart->hdmatx->Init.Direction = DMA_MEMORY_TO_PERIPH;
    huart->hdmatx->Init.PeriphInc = DMA_PINC_DISABLE;
    huart->hdmatx->Init.MemInc = DMA_MINC_ENABLE;
    huart->hdmatx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    huart->hdmatx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    huart->hdmatx->Init.Mode = DMA_NORMAL;
    huart->hdmatx->Init.Priority = DMA_PRIORITY_LOW;
    HAL_DMA_Init(huart->hdmatx);
    huart->hdmatx->Parent = huart;

	HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
}

void Uart3NVICInit(UART_HandleTypeDef * huart){
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
}

void Uart2NVICInit(UART_HandleTypeDef* huart) {
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}
/****************************************************************/
/** @brief: set registers acc to info in huart
 *  @details: used in HAL_UART3Debug_Init, private
 ****************************************************************/
static void MyUARTSetConfig(UART_HandleTypeDef * huart) {
	uint32_t tmpreg = 0x00;

	/* Check the parameters */
	assert_param(IS_UART_BAUDRATE(huart->Init.BaudRate));
	assert_param(IS_UART_STOPBITS(huart->Init.StopBits));
	assert_param(IS_UART_PARITY(huart->Init.Parity));
	assert_param(IS_UART_MODE(huart->Init.Mode));

	/*------- UART-associated USART registers setting : CR2 Configuration ------*/
	/* Configure the UART Stop Bits: Set STOP[13:12] bits according
	 * to huart->Init.StopBits value */
	MODIFY_REG(huart->Instance->CR2, USART_CR2_STOP, huart->Init.StopBits);

	/*------- UART-associated USART registers setting : CR1 Configuration ------*/
	/* Configure the UART Word Length, Parity and mode:
	 Set the M bits according to huart->Init.WordLength value
	 Set PCE and PS bits according to huart->Init.Parity value
	 Set TE and RE bits according to huart->Init.Mode value */
	tmpreg = (uint32_t) huart->Init.WordLength | huart->Init.Parity
			| huart->Init.Mode;
	MODIFY_REG(huart->Instance->CR1,
			(uint32_t)(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS | USART_CR1_TE | USART_CR1_RE),
			tmpreg);

	/*------- UART-associated USART registers setting : CR3 Configuration ------*/
	/* Configure the UART HFC: Set CTSE and RTSE bits according to huart->Init.HwFlowCtl value */
	MODIFY_REG(huart->Instance->CR3, (USART_CR3_RTSE | USART_CR3_CTSE),
			huart->Init.HwFlowCtl);

	/*------- UART-associated USART registers setting : BRR Configuration ------*/
	if ((huart->Instance == USART1)) {
		huart->Instance->BRR = UART_BRR_SAMPLING16(HAL_RCC_GetPCLK2Freq(),
				huart->Init.BaudRate);
	} else {
		huart->Instance->BRR = UART_BRR_SAMPLING16(HAL_RCC_GetPCLK1Freq(),
				huart->Init.BaudRate);
	}
}

/****************************************************************/
/** @brief: init state flag acc to info in huart
 *  @details: used in Uart3Debug_Init, private
 ****************************************************************/
static HAL_StatusTypeDef MyHAL_UARTInit(UART_HandleTypeDef * huart) {
    /* Check the UART handle allocation */
    if (huart == NULL) {
        return HAL_ERROR;
    }

    /* Check the parameters */
    if (huart->Init.HwFlowCtl != UART_HWCONTROL_NONE) {
        /* The hardware flow control is available only for USART1, USART2, USART3 and USART6 */
        assert_param(IS_UART_HWFLOW_INSTANCE(huart->Instance));
        assert_param(IS_UART_HARDWARE_FLOW_CONTROL(huart->Init.HwFlowCtl));
    } else {
        assert_param(IS_UART_INSTANCE(huart->Instance));
    }
    assert_param(IS_UART_WORD_LENGTH(huart->Init.WordLength));
    assert_param(IS_UART_OVERSAMPLING(huart->Init.OverSampling));

    if (huart->State == HAL_UART_STATE_RESET) {
        /* Allocate lock resource and initialize it */
        huart->Lock = HAL_UNLOCKED;
        /* Init the low level hardware */
//		HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
//		HAL_NVIC_EnableIRQ(USART3_IRQn);
    }

    huart->State = HAL_UART_STATE_BUSY;

    /* Disable the peripheral */
    __HAL_UART_DISABLE(huart);

    /* Set the UART Communication parameters */
    MyUARTSetConfig(huart);

    /* In asynchronous mode, the following bits must be kept cleared:
     * - LINEN and CLKEN bits in the USART_CR2 register,
     * - SCEN, HDSEL and IREN  bits in the USART_CR3 register.*/
    huart->Instance->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
    huart->Instance->CR3 &=
        ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);

    /* Enable the peripheral */
    __HAL_UART_ENABLE(huart);

    /* Initialize the UART state */
    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->State = HAL_UART_STATE_READY;

    return HAL_OK;
} /* MyHAL_UARTInit */

/****************************************************************/
/** @brief: just to config UART registers of Uart
 *  @details: used in Uart3Debug_Init
 ****************************************************************/
void Uart3UARTInit(UART_HandleTypeDef * huart) {
    __USART3_CLK_ENABLE();
    huart->Instance = USART3;
    huart->Init.BaudRate = 115200;
    huart->Init.WordLength = UART_WORDLENGTH_8B;
    huart->Init.StopBits = UART_STOPBITS_1;
    huart->Init.Parity = UART_PARITY_NONE;
    huart->Init.Mode = UART_MODE_TX_RX;
    huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart->Init.OverSampling = UART_OVERSAMPLING_16;
    MyHAL_UARTInit(huart);
    __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
}

void Uart2UARTInit(UART_HandleTypeDef* huart) {
	__USART2_CLK_ENABLE()
	;
	huart->Instance = USART2;
	huart->Init.BaudRate = 115200;
	huart->Init.WordLength = UART_WORDLENGTH_8B;
	huart->Init.StopBits = UART_STOPBITS_1;
	huart->Init.Parity = UART_PARITY_NONE;
	huart->Init.Mode = UART_MODE_TX_RX;
	huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart->Init.OverSampling = UART_OVERSAMPLING_16;
	MyHAL_UARTInit(huart);
	__HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
	__HAL_UART_ENABLE_IT(huart, UART_IT_TC);
}

/****************************************************************/
/** @brief: call dma,gpio,uart config
 *  @details: after call Uart3PortConfig, all the hardware configuration should be set up properly
 ****************************************************************/
void Uart3PortConfig(UART_HandleTypeDef * huart) {
    Uart3GPIOInit();
    Uart3NVICInit(huart);
    Uart3DMAInit(huart);
    Uart3UARTInit(huart);
    huart->Instance = USART3;
    HAL_UART_Receive_IT(huart, (uint8_t *)(huart->pRxBuffPtr), 1);
}

void Uart2PortConfig(UART_HandleTypeDef* huart) {
	huart->Instance = USART2;
	Uart2GPIOInit();
	Uart2NVICInit(huart);
	Uart2DMAInit(huart);
	Uart2UARTInit(huart);

	HAL_UART_Receive_IT(huart, (uint8_t*) (huart->pRxBuffPtr), 1);
}
