#include "main.h"
FILENUM(50000);
#include "cMotorDriver.h"

cMotorDriver* cMotorDriverConstructor() {
	cMotorDriver* me = calloc(1, sizeof(cMotorDriver));
	REQUIRE(me);
	return me;
}
