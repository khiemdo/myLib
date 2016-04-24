#include "main.h"
FILENUM(50008);
#include "TestcPWMMotorDriverWith1DirectionPin.h"
#include "stdlib.h"
#include "cAssert.h"

cPWMMotorDriverWith1DirectionPin *testChannel0;
cPWMMotorDriverWith1DirectionPin *testChannel1;

void TestMazherteqBSPConfig(void) {
	testChannel0 = calloc(1, sizeof(cPWMMotorDriverWith1DirectionPin));
	REQUIRE(testChannel0);
	testChannel1 = calloc(1, sizeof(cPWMMotorDriverWith1DirectionPin));
	REQUIRE(testChannel1);
	MotorChannel0Config_cPWMMotorDriverWith1DirectionPin(testChannel0);
	MotorChannel1Config_cPWMMotorDriverWith1DirectionPin(testChannel1);
	EnableMotor_cPWMMotorDriverWith1DirectionPin(testChannel0);
	EnableMotor_cPWMMotorDriverWith1DirectionPin(testChannel1);
}
void TestMotorInterface_Mazherteq(void) {
	int powerValue = 500;
	SetPower_cPWMMotorDriverWith1DirectionPin(testChannel0, powerValue);
	SetPower_cPWMMotorDriverWith1DirectionPin(testChannel1, powerValue);
	HAL_Delay(5000);
	powerValue = 0;
	SetPower_cPWMMotorDriverWith1DirectionPin(testChannel0, powerValue);
	SetPower_cPWMMotorDriverWith1DirectionPin(testChannel1, powerValue);
	HAL_Delay(5000);
	powerValue = 500;
	SetPower_cPWMMotorDriverWith1DirectionPin(testChannel0, powerValue);
	SetPower_cPWMMotorDriverWith1DirectionPin(testChannel1, powerValue);
	HAL_Delay(5000);
	DisableMotor_cPWMMotorDriverWith1DirectionPin(testChannel0);
	DisableMotor_cPWMMotorDriverWith1DirectionPin(testChannel1);
	powerValue = 0;
	SetPower_cPWMMotorDriverWith1DirectionPin(testChannel0, powerValue);
	SetPower_cPWMMotorDriverWith1DirectionPin(testChannel1, powerValue);
	HAL_Delay(5000);
	EnableMotor_cPWMMotorDriverWith1DirectionPin(testChannel0);
	EnableMotor_cPWMMotorDriverWith1DirectionPin(testChannel1);
	powerValue = 500;
	SetPower_cPWMMotorDriverWith1DirectionPin(testChannel0, powerValue);
	SetPower_cPWMMotorDriverWith1DirectionPin(testChannel1, powerValue);
}
