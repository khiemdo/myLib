#include "greatest.h"
#include "cEncoder.h"
#include "TestcEncoder.hpp"

typedef struct {
	cIncEncoder encoderTim3_TestcEncoder;
	TIM_HandleTypeDef htim3_TestcEncoder;
	cIncEncoder encoderTim1_TestcEncoder;
	TIM_HandleTypeDef htim1_TestcEncoder;
	cIncEncoder encoderTim4_TestcEncoder;
	TIM_HandleTypeDef htim4_TestcEncoder;
} TestcEncoder_str;

void Setup_TestcEncoder(void* data) {
	TestcEncoder_str * ptr = (TestcEncoder_str*) data;
	memset(ptr,0,sizeof(TestcEncoder_str));
	cIncEncoder* me = &(ptr->encoderTim3_TestcEncoder);
	cEncoderTim3Config(me, &(ptr->htim3_TestcEncoder));
	me = &(ptr->encoderTim1_TestcEncoder);
	cEncoderTim1Config(me, &(ptr->htim1_TestcEncoder));
	me = &(ptr->encoderTim4_TestcEncoder);
	cEncoderTim4Config(me, &(ptr->htim4_TestcEncoder));
}
TEST DisplayCount_TestcEncoder(void) {
	TestcEncoder_str * ptr = (TestcEncoder_str*) greatest_info.setup_udata;
	cIncEncoder* me = &(ptr->encoderTim3_TestcEncoder);
	int lastTime = 0;
	int counter = 0;
	while (1) {
		int currentTime = HAL_GetTick();
		int deltaTime = currentTime - lastTime;
		if (deltaTime > 1000) {
			counter++;
			if (counter > 100)
				break;
			printf("encoder:%d\r\n", GetCounts_cIncEncoder(me));
			lastTime = currentTime;
		}
	}
	PASS();
}
SUITE(TestSuiteEncoder)
{
	TestcEncoder_str testcEncoderStr;
	SET_SETUP(Setup_TestcEncoder, &testcEncoderStr);
	RUN_TEST(DisplayCount_TestcEncoder);
}
