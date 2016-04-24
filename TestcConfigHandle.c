#include "main.h"
FILENUM(18)

#include "TestcConfigHandle.h"
#include "cConfigHandle.h"
#include "cAssert.h"
#include "eeprom.h"
#include "crc.h"
#include "configuration.h"
#include <stddef.h>
#include "string.h"

#define PSVN_FACTORYSETTINGS	(2)
#define PSVN_USERSETTINGS		(3)
#define SW_VERSION_FACTORYSETTINGS	(6)
#define SW_VERSION_USERSETTINGS		(6)
const FactorySettings DEFAULT_FACTORY_SETTINGS = { .psvn = PSVN_FACTORYSETTINGS,
		.psvnTilda = ~PSVN_FACTORYSETTINGS, .softwareVersion =
		SW_VERSION_FACTORYSETTINGS, .deviceID = 4, .paraU16 = 0x0222, .paraU32 =
				0x01111111, .paraI16 = -1024, .paraI32 = -131072, .paraF = 3.14,
		.string1 = { 'a', '\0' }, .string2 = "cd", .string3 = "ban", .char1 =
				'k' };

const UserSettings DEFAULT_USER_SETTINGS = { .psvn = PSVN_USERSETTINGS,
		.psvnTilda = ~PSVN_USERSETTINGS, .softwareVersion =
		SW_VERSION_USERSETTINGS, .deviceID = 1, .paraU16 = 0x7222, .paraU32 =
				0x71111111, .paraI16 = -1024, .paraI32 = -131072, .paraF = 3.14,
		.string1 = "khiem", .string3 = "hello\r\n" };

//todo contain the config stored in flash

void TestcConfigHandleConfig(void) {
	HAL_FLASH_Unlock();
	int ret = EE_Init();
	crcInit();
	REQUIRE(ret == EE_OK);
	ret = ValidateConfigurations(&DEFAULT_FACTORY_SETTINGS,
			&DEFAULT_USER_SETTINGS);
	REQUIRE(ret>0);
}

/* Test PersistentConfigWrite
 * can write u8,u16,u32, char[n]
 */
void TesConfigWriteAndReadDIffTypes() {
	HAL_Delay(1000);
	int ret = 0;

	uint16_t testU16 = 0xabcd;
	WRITE_CONFIG_BY_MEMBER_NAME(factorySettings.paraU16, (uint8_t* )&testU16);
	uint16_t retU16 = 0;
	READ_CONFIG_BY_MEMBER_NAME(factorySettings.paraU16, (uint8_t* )&retU16);
	REQUIRE(testU16 == retU16);

	uint32_t testU32 = 0x1234abcd;
	WRITE_CONFIG_BY_MEMBER_NAME(factorySettings.paraU32, (uint8_t* )&testU32);
	uint32_t retU32 = 0;
	READ_CONFIG_BY_MEMBER_NAME(factorySettings.paraU32, (uint8_t* )&retU32);
	REQUIRE(testU32 == retU32);

	int16_t testI16 = -20000;
	WRITE_CONFIG_BY_MEMBER_NAME(factorySettings.paraI16, (uint8_t* )&testI16);
	int16_t retI16 = 0;
	READ_CONFIG_BY_MEMBER_NAME(factorySettings.paraI16, (uint8_t* )&retI16);
	REQUIRE(testI16 == retI16);

	int32_t testI32 = -500000;
	WRITE_CONFIG_BY_MEMBER_NAME(factorySettings.paraI32, (uint8_t* )&testI32);
	int32_t retI32 = 0;
	READ_CONFIG_BY_MEMBER_NAME(factorySettings.paraI32, (uint8_t* )&retI32);
	REQUIRE(testI32 == retI32);

	char string1[] = "a";
	WRITE_CONFIG_BY_MEMBER_NAME(factorySettings.string1, (uint8_t* )string1);
	char retstring1[2] = { 0 };
	READ_CONFIG_BY_MEMBER_NAME(factorySettings.string1, (uint8_t* )retstring1);
	ret = strcmp(string1, retstring1);
	REQUIRE(ret);

	char string2[] = "cd";
	WRITE_CONFIG_BY_MEMBER_NAME(factorySettings.string2, (uint8_t* )string2);
	char retstring2[3] = { 0 };
	READ_CONFIG_BY_MEMBER_NAME(factorySettings.string2, (uint8_t* )retstring2);
	ret = strcmp(string2, retstring2);
	REQUIRE(ret);

	char string3[] = "ban";
	WRITE_CONFIG_BY_MEMBER_NAME(factorySettings.string3, (uint8_t* )string3);
	char retstring3[4] = { 0 };
	READ_CONFIG_BY_MEMBER_NAME(factorySettings.string3, (uint8_t* )retstring3);
	ret = strcmp(string3, retstring3);
	REQUIRE(ret);

	char char1 = 'k';
	WRITE_CONFIG_BY_MEMBER_NAME(factorySettings.char1, (uint8_t* )&char1);
	char retchar1 = 0;
	READ_CONFIG_BY_MEMBER_NAME(factorySettings.char1, (uint8_t* )&retchar1);
	char1 = retchar1;
	REQUIRE(ret);
}

void TestConfigAPI() {
	PersistentConfigStorage testPersistentConfigStorage;
	FactorySettings testFactorySettings;
	UserSettings testUserSettings;

	HAL_Delay(1000);
	// load config by memName,write config by memName
	int32_t input = 0x23232323;
	int32_t ret = 0;
	WRITE_CONFIG_BY_MEMBER_NAME(factorySettings.paraU32, (uint8_t* )&input);
	READ_CONFIG_BY_MEMBER_NAME(factorySettings.paraU32, (uint8_t* )&ret);
	REQUIRE(input == ret);

	//load all factory configs, write all factory configs
	SaveFactoryConfigsStr((uint8_t*) &DEFAULT_FACTORY_SETTINGS);
	LoadFactoryConfigsStr((uint8_t*) &testFactorySettings);
	REQUIRE(DEFAULT_FACTORY_SETTINGS.deviceID == testFactorySettings.deviceID);
	REQUIRE(DEFAULT_FACTORY_SETTINGS.paraF == testFactorySettings.paraF);
	REQUIRE(DEFAULT_FACTORY_SETTINGS.paraI16 == testFactorySettings.paraI32);
	REQUIRE(DEFAULT_FACTORY_SETTINGS.paraI32 == testFactorySettings.paraI32);
	REQUIRE(DEFAULT_FACTORY_SETTINGS.paraU16 == testFactorySettings.paraU16);
	REQUIRE(DEFAULT_FACTORY_SETTINGS.paraU32 == testFactorySettings.paraU32);
	REQUIRE(DEFAULT_FACTORY_SETTINGS.psvn == testFactorySettings.psvn);
	REQUIRE(
			DEFAULT_FACTORY_SETTINGS.psvnTilda
					== testFactorySettings.psvnTilda);
	REQUIRE(
			DEFAULT_FACTORY_SETTINGS.softwareVersion
					== testFactorySettings.softwareVersion);

	//load all user configs, write all user configs
	SaveUserConfigsStr((uint8_t*) &testUserSettings);
	LoadUserConfigsStr((uint8_t*) &testUserSettings);
	REQUIRE(DEFAULT_USER_SETTINGS.deviceID == testUserSettings.deviceID);
	REQUIRE(DEFAULT_USER_SETTINGS.paraF == testUserSettings.paraF);
	REQUIRE(DEFAULT_USER_SETTINGS.paraI16 == testUserSettings.paraI16);
	REQUIRE(DEFAULT_USER_SETTINGS.paraI32 == testUserSettings.paraI32);
	REQUIRE(DEFAULT_USER_SETTINGS.paraU16 == testUserSettings.paraU16);
	REQUIRE(DEFAULT_USER_SETTINGS.paraU32 == testUserSettings.paraU32);

	//load all configs,write all configs
	SaveAllConfigsStr((uint8_t*) &testPersistentConfigStorage);
	LoadAllConfigsStr((uint8_t*) &testPersistentConfigStorage);
	REQUIRE(testFactorySettings.deviceID == 0);
}

