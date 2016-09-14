#include "generalUtility.h"
#include "ctype.h"

void ConvertStringToLowerCase(int8_t* buffer, int32_t length) {
	while (length) {
		buffer[length - 1] = tolower(buffer[length - 1]);
		length--;
	}
}

void SimpleDelay_Utility(int32_t count) {
	while (count--)
		;
}
float_t LimitToRange_Utility(float_t input, float_t min, float_t max) {
	if (input > max)
		input = max;
	if (input < min)
		input = min;
	return input;
}
float_t Mapf_Utility(float_t value, float_t fromLow, float_t fromHigh,
		float_t toLow, float_t toHigh) {
	return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

int16_t BitConverterToInt16_Utility(uint8_t * byte, int32_t index) {
	int16_t ret = ((int16_t) byte[index]) + ((int16_t) byte[index + 1] << 8);
	return ret;
}
int32_t BitConverterToInt32_Utility(uint8_t * byte, int32_t index) {
	int32_t ret = (((int32_t) byte[index]) + ((int32_t) byte[index + 1] << 8)
			+ ((int32_t) byte[index + 2] << 16) + ((int32_t) byte[index + 3] << 24));
	return ret;
}
float_t BitConverterToFloat_Utility(uint8_t * byte, int32_t index) {
	float_t ret = (float_t) (((uint32_t) byte[index]) + ((uint32_t) byte[index + 1] << 8)
			+ ((uint32_t) byte[index + 1] << 16) + ((uint32_t) byte[index + 1] << 24));
	return ret;
}
