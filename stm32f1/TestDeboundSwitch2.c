#include "main.h"
FILENUM(32)

#include "TestDeboundSwitch2.h"
cDebounceBtn myBtn;

void TestDeboundSwitchConfig() {
	cDebounceBtnInit(&myBtn);
	cDebounceBtnConfig1(&myBtn);
}
void TestDeboundSwitchRun() {
	cDebounceBtnLoop(&myBtn);

	if (ReadDebounceBtn(&myBtn)) {
//		STM_EVAL_LEDOn(LED3);
	} else {
//		STM_EVAL_LEDOff(LED3);
	}
}
