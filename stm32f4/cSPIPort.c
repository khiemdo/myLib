#include "main.h"
FILENUM(1000000);
#include "cSPIPort.h"
#include "cAssert.h"

void SPI2GPIOInit(SPI_HandleTypeDef* hspi) {
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE()
	; //sck,miso,mosi

	/* SPI SCK GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* SPI MISO GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_14;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* SPI MOSI GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void SPI2GPIONSSInit(SPI_HandleTypeDef* hspi) {
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE()
	; //nss
	/* SPI NSS GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void SPI3GPIOInit(SPI_HandleTypeDef* hspi) {
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE()
	; //sck,miso,mosi

	/* SPI SCK GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* SPI MISO GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_11;
	GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* SPI MOSI GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
void SPI3GPIONSSInit(SPI_HandleTypeDef* hspi) {
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE()
	; //nss
	/* SPI NSS GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void SPI2DMAInit(SPI_HandleTypeDef* hspi) {
	__HAL_RCC_DMA1_CLK_ENABLE()
	;

	hspi->hdmatx->Instance = DMA1_Stream4;
	hspi->hdmatx->Init.Channel = DMA_CHANNEL_0;
	hspi->hdmatx->Init.Direction = DMA_MEMORY_TO_PERIPH;
	hspi->hdmatx->Init.PeriphInc = DMA_PINC_DISABLE;
	hspi->hdmatx->Init.MemInc = DMA_MINC_ENABLE;
	hspi->hdmatx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hspi->hdmatx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hspi->hdmatx->Init.Mode = DMA_NORMAL;
	hspi->hdmatx->Init.Priority = DMA_PRIORITY_LOW;
	hspi->hdmatx->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hspi->hdmatx->Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	hspi->hdmatx->Init.MemBurst = DMA_MBURST_INC4;
	hspi->hdmatx->Init.PeriphBurst = DMA_PBURST_INC4;
	HAL_DMA_Init(hspi->hdmatx);
	hspi->hdmatx->Parent = hspi;

	/* Configure the DMA handler for Transmission process */
	hspi->hdmarx->Instance = DMA1_Stream3;
	hspi->hdmarx->Init.Channel = DMA_CHANNEL_0;
	hspi->hdmarx->Init.Direction = DMA_PERIPH_TO_MEMORY;
	hspi->hdmarx->Init.PeriphInc = DMA_PINC_DISABLE;
	hspi->hdmarx->Init.MemInc = DMA_MINC_ENABLE;
	hspi->hdmarx->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hspi->hdmarx->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hspi->hdmarx->Init.Mode = DMA_NORMAL;
	hspi->hdmarx->Init.Priority = DMA_PRIORITY_HIGH;
	hspi->hdmarx->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hspi->hdmarx->Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	hspi->hdmarx->Init.MemBurst = DMA_MBURST_INC4;
	hspi->hdmarx->Init.PeriphBurst = DMA_PBURST_INC4;
	HAL_DMA_Init(hspi->hdmarx);
	hspi->hdmarx->Parent = hspi;
}
void SPI2NVICInit(SPI_HandleTypeDef* hspi) {
	HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
	HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
}

void SPI2SPIInit(SPI_HandleTypeDef* hspi, uint32_t mode) {
	__HAL_RCC_SPI2_CLK_ENABLE()
	;
	hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	hspi->Init.Direction = SPI_DIRECTION_2LINES;
	hspi->Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi->Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi->Init.CRCPolynomial = 7;
	hspi->Init.DataSize = SPI_DATASIZE_8BIT;
	hspi->Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi->Init.NSS = SPI_NSS_SOFT;
	hspi->Init.TIMode = SPI_TIMODE_DISABLE;
	hspi->Init.Mode = mode;
	HAL_StatusTypeDef ret = HAL_SPI_Init(hspi);
	REQUIRE(ret == HAL_OK);
}
void SPI3SPIInit(SPI_HandleTypeDef* hspi, uint32_t mode) {
	__HAL_RCC_SPI3_CLK_ENABLE()
	;
	//todo
	hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	hspi->Init.Direction = SPI_DIRECTION_1LINE;
	hspi->Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi->Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi->Init.CRCPolynomial = 7;
	hspi->Init.DataSize = SPI_DATASIZE_16BIT;
	hspi->Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi->Init.NSS = SPI_NSS_SOFT;
	hspi->Init.TIMode = SPI_TIMODE_DISABLE;
	hspi->Init.Mode = mode;
	HAL_StatusTypeDef ret = HAL_SPI_Init(hspi);
	REQUIRE(ret == HAL_OK);
}

void SPI2PortConfig(SPI_HandleTypeDef* hspi) {
	hspi->Instance = SPI2;
	SPI2GPIOInit(hspi);
	SPI2DMAInit(hspi);
	SPI2NVICInit(hspi);
	SPI2SPIInit(hspi, SPI_MODE_SLAVE);
}
void SPI3PortConfig(SPI_HandleTypeDef* hspi) {
	hspi->Instance = SPI3;
	SPI3GPIOInit(hspi);
	SPI3GPIONSSInit(hspi);
//	SPI3DMAInit(hspi);
//	SPI3NVICInit(hspi);
	SPI3SPIInit(hspi, SPI_MODE_MASTER);

}

