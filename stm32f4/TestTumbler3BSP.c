#include "main.h"
FILENUM(24);

#include "TestTumbler3BSP.h"
#include "Tumbler3BSP.h"
#include "stdint.h"

void TestStatusLED_Init_T3B_Config(void) {
	StatusLED_Init_T3B(STATUS_LED_0);
	StatusLED_Init_T3B(STATUS_LED_1);
	StatusLED_Init_T3B(STATUS_LED_2);

}
void TestStatusLED_T3B(void) {
	static uint32_t lastTime0 = 0;
	static uint32_t lastTime1 = 0;
	static uint32_t lastTime2 = 0;

	uint32_t currentTime = HAL_GetTick();

	int32_t deltaTime0 = (int32_t) (currentTime - lastTime0);
	if (deltaTime0 > 10) {
		StatusLED_Toggle_T3B(STATUS_LED_0);
		lastTime0 = currentTime;
	}

	int32_t deltaTime1 = (int32_t) (currentTime - lastTime1);
	if (deltaTime1 > 200) {
		StatusLED_Toggle_T3B(STATUS_LED_1);
		lastTime1 = currentTime;
	}

	int32_t deltaTime2 = (int32_t) (currentTime - lastTime2);
	if (deltaTime2 > 1000) {
		StatusLED_Toggle_T3B(STATUS_LED_2);
		lastTime2 = currentTime;
	}
}
