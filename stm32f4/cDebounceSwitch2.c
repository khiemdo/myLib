#include "main.h"
FILENUM(31);

#include "cDebounceSwitch2.h"
#include "string.h"
#include "cAssert.h"
#include "stdlib.h"

void cDebounceBtnInit(cDebounceBtn *me) {
	memset(me, 0, sizeof(cDebounceBtn));
}

void cDebounceBtnProcess(cDebounceBtn *me) {
	unsigned char rawState = HAL_GPIO_ReadPin(me->port, me->pin);

	if(me->id==2){
		int i = 0;
		i++;
	}

	if (rawState == (int32_t) RELEASED) {
		if (me->keyIntegrator > 0) {
			me->keyIntegrator--;
		}
	} else if (me->keyIntegrator < MAXIMUM)
		me->keyIntegrator++;

	if (me->keyIntegrator == 0)
		me->keyPressed = RELEASED;
	else if (me->keyIntegrator >= MAXIMUM) {
		me->keyPressed = PRESSED;
		me->keyIntegrator = MAXIMUM; /* defensive code if integrator got corrupted */
		DEBUG(LOG_TEST,"btnPress\r\n",0);
	}
}

void cDebounceBtnLoop(cDebounceBtn *me) {
	unsigned long tempTimer = HAL_GetTick();
	int32_t tempTimer1 = tempTimer - me->lastTime;
	if (tempTimer1 > CHECK_MSEC) {
		cDebounceBtnProcess(me);
		me->lastTime = tempTimer;
	}
}

int32_t ReadDebounceBtn(cDebounceBtn *me) {
	return (int32_t) me->keyPressed;
}

void cDebounceBtnConfig1(cDebounceBtn *me) {
	GPIO_InitTypeDef GPIO_InitStruct;

	me->pin = GPIO_PIN_0;
	me->port = GPIOA;
	me->keyPressed = RELEASED;
	me->keyIntegrator = 0;

	__GPIOA_CLK_ENABLE()
	;

	/* Configure Button pin as input */
	GPIO_InitStruct.Pin = me->pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(me->port, &GPIO_InitStruct);

}
