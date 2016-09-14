#include "main.h"
FILENUM(32)

#include "TestDeboundSwitch2.h"
cDebounceBtn myBtn;

void TestDeboundSwitchConfig() {
	Initialize_cDebounceBtn(&myBtn);
	cDebounceBtnConfig1(&myBtn);
}
void TestDeboundSwitchRun() {
	Loop_cDebounceBtn(&myBtn);

	if (Read_cDebounceBtn(&myBtn)) {
//		STM_EVAL_LEDOn(LED3);
	} else {
//		STM_EVAL_LEDOff(LED3);
	}
}
