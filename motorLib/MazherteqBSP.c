#include "main.h"
FILENUM(50007);
#include "MazherteqBSP.h"
#include "utility.h"

void PWMDriveWith1DirectionPinConfig0_MBSP(cPWMMotorDriverWith1DirectionPin* me, uint32_t pwmClock, uint32_t pulses ) {
	GPIO_TypeDef* thisGpio;
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_HandleTypeDef TimHandle;
	TIM_OC_InitTypeDef sConfig;
	HAL_StatusTypeDef ret = HAL_ERROR;

	me->directionPin = GPIO_PIN_8;
	me->directionPort = GPIOA;
	me->resetPin = GPIO_PIN_3;
	me->resetPort = GPIOC;
	me->pwmValue = &(TIM5->CCR3);
	__HAL_RCC_TIM5_CLK_ENABLE()
	;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	//SR Pin
	thisGpio = GPIOC;
	GPIO_InitStruct.Pin = GPIO_PIN_14;
	InitGPIOClockByGPIOName(thisGpio);
	HAL_GPIO_Init(thisGpio, &GPIO_InitStruct);
	HAL_GPIO_WritePin(thisGpio, GPIO_InitStruct.Pin, GPIO_PIN_SET); //sync pin must be HIGH
	// Direction Pin
	thisGpio = me->directionPort;
	GPIO_InitStruct.Pin = me->directionPin;
	InitGPIOClockByGPIOName(thisGpio);
	HAL_GPIO_Init(thisGpio, &GPIO_InitStruct);
	// Reset Pin
	thisGpio = me->resetPort;
	GPIO_InitStruct.Pin = me->resetPin;
	InitGPIOClockByGPIOName(thisGpio);
	HAL_GPIO_Init(thisGpio, &GPIO_InitStruct);
	HAL_GPIO_WritePin(me->resetPort, me->resetPin, GPIO_PIN_RESET);	//reset pin s low to disable motor
	//PWM config
	//pwm high pin
	thisGpio = GPIOA;
	InitGPIOClockByGPIOName(thisGpio);
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(thisGpio, &GPIO_InitStruct);
	//pwm low pin
	thisGpio = GPIOA;
	InitGPIOClockByGPIOName(thisGpio);
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(thisGpio, GPIO_InitStruct.Pin, GPIO_PIN_SET);

	TimHandle.Instance = TIM5;
	uint16_t uhPrescalerValue = (uint16_t) ((SystemCoreClock) / pwmClock) - 1;
	TimHandle.Init.Prescaler = uhPrescalerValue;
	TimHandle.Init.Period = pulses;
	TimHandle.Init.ClockDivision = 0;
	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TimHandle.Init.RepetitionCounter = 0;
	ret = HAL_TIM_PWM_Init(&TimHandle);
	REQUIRE(ret == HAL_OK);

	sConfig.OCMode = TIM_OCMODE_PWM1;
	sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfig.OCFastMode = TIM_OCFAST_DISABLE;
	sConfig.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	sConfig.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfig.Pulse = 0;
	ret = HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_3);
	REQUIRE(ret == HAL_OK);
	ret = HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_3);
	REQUIRE(ret == HAL_OK);
}
void PWMDriveWith1DirectionPinConfig1_MBSP(cPWMMotorDriverWith1DirectionPin* me, uint32_t pwmClock, uint32_t pulses ) {
	GPIO_TypeDef* thisGpio;
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_HandleTypeDef TimHandle;
	TIM_OC_InitTypeDef sConfig;
	HAL_StatusTypeDef ret = HAL_ERROR;

	me->directionPin = GPIO_PIN_9;
	me->directionPort = GPIOA;
	me->resetPin = GPIO_PIN_0;
	me->resetPort = GPIOA;
	me->pwmValue = &(TIM12->CCR1);
	__HAL_RCC_TIM12_CLK_ENABLE()
	;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	//SR Pin
	thisGpio = GPIOC;
	GPIO_InitStruct.Pin = GPIO_PIN_15;
	InitGPIOClockByGPIOName(thisGpio);
	HAL_GPIO_Init(thisGpio, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);//sync pin must be HIGH
	// Direction Pin
	thisGpio = me->directionPort;
	GPIO_InitStruct.Pin = me->directionPin;
	InitGPIOClockByGPIOName(thisGpio);
	HAL_GPIO_Init(thisGpio, &GPIO_InitStruct);
	// Reset Pin
	thisGpio = me->resetPort;
	GPIO_InitStruct.Pin = me->resetPin;
	InitGPIOClockByGPIOName(thisGpio);
	HAL_GPIO_Init(thisGpio, &GPIO_InitStruct);
	HAL_GPIO_WritePin(me->resetPort, me->resetPin, GPIO_PIN_RESET);	//reset pin s low to disable motor

	//PWM config
	//pwm high pin
	thisGpio = GPIOB;
	InitGPIOClockByGPIOName(thisGpio);
	GPIO_InitStruct.Alternate = GPIO_AF9_TIM12;
	GPIO_InitStruct.Pin = GPIO_PIN_14;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(thisGpio, &GPIO_InitStruct);

	//pwm low pin
	thisGpio = GPIOB;
	InitGPIOClockByGPIOName(thisGpio);
	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Alternate = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(thisGpio, &GPIO_InitStruct);
	HAL_GPIO_WritePin(thisGpio, GPIO_InitStruct.Pin, GPIO_PIN_SET);

	TimHandle.Instance = TIM12;
	uint16_t uhPrescalerValue = (uint16_t) ((SystemCoreClock) / pwmClock) - 1;
	TimHandle.Init.Prescaler = uhPrescalerValue;
	TimHandle.Init.Period = pulses;
	TimHandle.Init.ClockDivision = 0;
	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TimHandle.Init.RepetitionCounter = 0;
	ret = HAL_TIM_PWM_Init(&TimHandle);
	REQUIRE(ret == HAL_OK);

	sConfig.OCMode = TIM_OCMODE_PWM1;
	sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfig.OCFastMode = TIM_OCFAST_DISABLE;
	sConfig.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	sConfig.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfig.Pulse = 0;
	ret = HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1);
	REQUIRE(ret == HAL_OK);
	ret = HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);
	REQUIRE(ret == HAL_OK);
}

uint32_t* P9_11_EncoderPWMOutput_MBSP( uint32_t pwmClock, uint32_t pulses ) {
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_HandleTypeDef TimHandle;
	TIM_OC_InitTypeDef sConfig;
	HAL_StatusTypeDef ret = HAL_ERROR;

	uint32_t pwmPin = GPIO_PIN_6;
	GPIO_TypeDef* thisGpio = GPIOC;
	TIM_TypeDef* thisTimer = TIM8;
	uint32_t timerChannel = TIM_CHANNEL_1;
	__HAL_RCC_TIM8_CLK_ENABLE()
	;
	uint32_t* pwmPulseRegister = (uint32_t*) &(thisTimer->CCR1);

	//using PWM_INPUT1 as output
	GPIO_InitStruct.Pin = pwmPin;
	InitGPIOClockByGPIOName(thisGpio);
	GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(thisGpio, &GPIO_InitStruct);
	HAL_GPIO_WritePin(thisGpio, GPIO_InitStruct.Pin, GPIO_PIN_RESET);

	TimHandle.Instance = thisTimer;
	uint16_t uhPrescalerValue = (uint16_t) ((SystemCoreClock) / pwmClock) - 1;
	TimHandle.Init.Prescaler = uhPrescalerValue;
	TimHandle.Init.Period = pulses;
	TimHandle.Init.ClockDivision = 0;
	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TimHandle.Init.RepetitionCounter = 0;
	ret = HAL_TIM_PWM_Init(&TimHandle);
	REQUIRE(ret == HAL_OK);

	sConfig.OCMode = TIM_OCMODE_PWM1;
	sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfig.OCFastMode = TIM_OCFAST_DISABLE;
	sConfig.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	sConfig.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfig.Pulse = 0;
	ret = HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, timerChannel);
	REQUIRE(ret == HAL_OK);
	ret = HAL_TIM_PWM_Start(&TimHandle, timerChannel);
	REQUIRE(ret == HAL_OK);

	return pwmPulseRegister;
}

void SPI3GPIOInit_MBSP(SPI_HandleTypeDef* hspi) {
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
void SPI3GPIONSSInit_MBSP(SPI_HandleTypeDef* hspi) {
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
void SPI3SPIInit_MBSP(SPI_HandleTypeDef* hspi, uint32_t mode) {
	__HAL_RCC_SPI3_CLK_ENABLE()
	;
	//todo
	hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	hspi->Init.Direction = SPI_DIRECTION_2LINES;
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
void SPI3PortConfig_MBSP(SPI_HandleTypeDef* hspi) {
	hspi->Instance = SPI3;
	SPI3GPIOInit_MBSP(hspi);
	SPI3GPIONSSInit_MBSP(hspi);
//	SPI3DMAInit(hspi);
//	SPI3NVICInit(hspi);
	SPI3SPIInit_MBSP(hspi, SPI_MODE_MASTER);

}

