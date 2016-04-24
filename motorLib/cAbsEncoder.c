#include "main.h"
FILENUM(505);

#include "cAbsEncoder.h"
#include "cSPIPort.h"
#include "cAssert.h"
#include <stdlib.h>
#include "cSPIAbsEnc.h"

cAbsEncoder* cAbsEncoderConstructor() {
	cAbsEncoder* me = calloc(1, sizeof(cAbsEncoder));
	REQUIRE(me);
	return me;
}
void ValidateAbsEncParameters(cAbsEncoder* me){
	REQUIRE(me->encRawStartLmt != me->encRawEndLmt);
	REQUIRE(me->encRawMax > me->encRawMin);
	if (me->encRawStartLmt > me->encRawEndLmt) {
		me->linearizeFlag = 1;
	}
}
void _LinearizeAbsEncValue(cAbsEncoder* me) {
	if (me->rawValue > me->encRawStartLmt) {
		me->linearizedEncValue = me->rawValue - (me->encRawMax + 1);
	} else {
		me->linearizedEncValue = me->rawValue;
	}
}

int32_t GetEncValue_cAbsEncoder(cAbsEncoder* me) {
	cSPIAbsEncoderPort* spiEncPtr = (cSPIAbsEncoderPort*)me->encoderPort;
	me->encoderPort->updateEncoder((void*)spiEncPtr);
	me->rawValue = me->encoderPort->getEncoderValue((void*)spiEncPtr);
	if (me->linearizeFlag == 1) {
		_LinearizeAbsEncValue(me);
	} else {
		me->linearizedEncValue = me->rawValue;
	}
	me->encFinalValue = me->linearizedEncValue - me->encOffset;
	return me->encFinalValue;
}

