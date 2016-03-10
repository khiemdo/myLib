#include "main.h"
FILENUM(34);

#include "TestcPinOut.h"
#include "cPinOut.h"

cPatternedPinOutStruct myOutput;
void TestGPIOOUtputConfig() {

	PinOutInit((cPinOutStruct*)&myOutput, 1);
	myOutput.super.port = GPIOD;
	myOutput.super.pin = GPIO_PIN_13;

	GPIO_InitTypeDef GPIO_InitStruct;
	__GPIOD_CLK_ENABLE()
		;
	GPIO_InitStruct.Pin = myOutput.super.pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(myOutput.super.port, &GPIO_InitStruct);

}
void TestGPIOOUtputOn(){
	SetPatternOutputPin(&myOutput, 1, 0);
}
void TestGPIOOUtputOff(){
	SetPatternOutputPin(&myOutput, 1, 0);
}
void TestGPIOOUtputBlinking(){
	SetPatternOutputPin(&myOutput, 1000000, 1000000);
	OutputPinPatternLoop(&myOutput);
}

