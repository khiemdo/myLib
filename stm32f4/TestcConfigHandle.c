#include "main.h"
FILENUM(18)

#include "TestcConfigHandle.h"
#include "cConfigHandle.h"
#include "cAssert.h"
#include "eeprom.h"
#include "configuration.h"
#include <stddef.h>


void TestcConfigHandleConfig(void){
	HAL_FLASH_Unlock();
	int ret = EE_Init();
	REQUIRE(ret == EE_OK);
	GetPersistentConfigFromSource();
}
int32_t TestcConfigHandle_offsetof(void){
	int32_t res = SIZEOF(persistentConfigStorage_t,factorySettings.deviceID);
	res = offsetof(persistentConfigStorage_t,factorySettings.deviceID);
	return res;
}
void TestcConfigHandleConfig_SaveDefaultConfigIntoEEPROM(void){
	SaveSourceConfigIntoEEPROM();
}
void TestcConfigHandleConfig_GetFlashAddressOfConfigHeader(void){
	uint16_t ret = 0;
	uint32_t res = GetFlashAddressOfConfigHeader(0,&ret);
	DEBUG(LOG_TEST,"res = %d\r\n",res);
}
void TestcConfigHandleConfig_LoadConfigFromEEPROMByID(void){
	uint32_t res = 0;
	LoadConfigFromEEPROMByID(1,(uint16_t*)&res);
	DEBUG(LOG_TEST,"res = %d\r\n",res);
}
