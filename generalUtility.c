#include "generalUtility.h"
#include "ctype.h"

void ConvertStringToLowerCase(int8_t* buffer, int32_t length) {
	while (length) {
		buffer[length - 1] = tolower(buffer[length - 1]);
		length--;
	}
}
