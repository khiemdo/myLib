#include "main.h"
FILENUM(501);
#include "cEncoderPort.h"

cEncoderPort* cEncoderPortConstructor(){
	cEncoderPort* me = calloc(1, sizeof(cEncoderPort));
	REQUIRE(me);
	return me;
}
