#include "main.h"
FILENUM(17)

#include "cConfigHandle.h"
#include "eeprom.h"
#include "configuration.h"
#include "cAssert.h"
#include "math.h"
#include "crc.h"
#include <stddef.h>

int32_t ReadConfigInEEPROMEmul(const uint32_t offset, uint32_t nBytes,
		uint8_t * const dest) {
	int ret = 0xff;
	uint32_t virtualAddress = PERSISTENT_CONFIG_VIRTUAL_BASE_ADDR + offset;
	uint16_t * valueArrayPtr = (uint16_t *) dest;
	while (nBytes > 0) {
		uint16_t tempU16 = 0;
		if (nBytes == 1) {
			ret = EE_ReadVariable(virtualAddress, &tempU16);
			if (ret == EE_OK) {
				*((uint8_t *) valueArrayPtr) = tempU16;
				virtualAddress += sizeof(uint8_t);
				valueArrayPtr = (uint16_t *) ((uint32_t) valueArrayPtr
						+ sizeof(uint8_t));
				nBytes -= sizeof(uint8_t);
			} else {
				break;
			}
		} else {
			ret = EE_ReadVariable(virtualAddress, &tempU16);
			if (ret == EE_OK) {
				*(valueArrayPtr) = tempU16;
				virtualAddress += sizeof(uint16_t);
				valueArrayPtr = (uint16_t *) ((uint32_t) valueArrayPtr
						+ sizeof(uint16_t));
				nBytes -= sizeof(uint16_t);
			} else {
				break;
			}
		}
	}
	return nBytes;
}
int32_t WriteConfigInEEPROMEmul(const uint32_t offset, uint32_t nBytes,
		uint8_t * const valueBuff) {
	int ret = 0xff;
	uint32_t virtualAddress = PERSISTENT_CONFIG_VIRTUAL_BASE_ADDR + offset;
	uint16_t * valueBuffPtr = (uint16_t *) valueBuff;
	while (nBytes > 0) {
		uint16_t tempU16 = 0;
		if (nBytes == 1) {
			tempU16 = *((uint8_t *) valueBuffPtr);
			ret = EE_WriteVariable(virtualAddress, tempU16);
			if (ret == EE_OK || ret == PAGE_FULL) {
				*((uint8_t *) valueBuffPtr) = tempU16;
				virtualAddress += sizeof(uint8_t);
				valueBuffPtr = (uint16_t *) ((uint32_t) valueBuffPtr
						+ sizeof(uint8_t));
				nBytes -= sizeof(uint8_t);
			} else {
				break;
			}
		} else {
			tempU16 = *((uint16_t *) valueBuffPtr);
			ret = EE_WriteVariable(virtualAddress, tempU16);
			if (ret == EE_OK || ret == PAGE_FULL) {
				*(valueBuffPtr) = tempU16;
				virtualAddress += sizeof(uint16_t);
				valueBuffPtr = (uint16_t *) ((uint32_t) valueBuffPtr
						+ sizeof(uint16_t));
				nBytes -= sizeof(uint16_t);
			} else {
				break;
			}
		}
	}
	return nBytes;
}

int32_t LoadAllConfigsStr(uint8_t* const buff) {
	REQUIRE(buff != 0);
	return ReadConfigInEEPROMEmul(0, sizeof(PersistentConfigStorage), buff);
}
int32_t SaveAllConfigsStr(uint8_t* const buff) {
	REQUIRE(buff != 0);
	//todo:cal crc
	PersistentConfigStorage* ptr = (PersistentConfigStorage*) buff;
	SaveFactoryConfigsStr((uint8_t*) &(ptr->factorySettings));
	SaveUserConfigsStr((uint8_t*) &(ptr->factorySettings));
	return 0;
}
int32_t LoadFactoryConfigsStr(uint8_t* const buff) {
	REQUIRE(buff != 0);
	READ_CONFIG_BY_MEMBER_NAME(factorySettings,buff);
	return 0;
}
int32_t SaveFactoryConfigsStr(uint8_t* const buff) {
	REQUIRE(buff != 0);
	int ret = 0;
	WRITE_CONFIG_BY_MEMBER_NAME_WITH_CRC(factorySettings, buff);
	return ret;
}
int32_t LoadUserConfigsStr(uint8_t* const buff) {
	REQUIRE(buff != 0);
	READ_CONFIG_BY_MEMBER_NAME(userSettings,buff);
	return 0;
}
int32_t SaveUserConfigsStr(uint8_t* const buff) {
	REQUIRE(buff != 0);
	int ret = 0;
	WRITE_CONFIG_BY_MEMBER_NAME_WITH_CRC(userSettings, buff);
	return ret;
}

int32_t IsPSVNCorrectAndSame(const uint16_t psvnFromSource,
		const uint16_t psvnTildaFromSource, const uint16_t psvn,
		const uint16_t psvnTilda) {
	int32_t ret = 0;
	if (psvn + psvnTilda == 0xffff) {
		if (psvn == psvnFromSource && psvnTilda == psvnTildaFromSource) {
			ret++;
		}
	}
	return ret;
}
void _ValidatePSVN(const FactorySettings* factorySettingsFromSource,
		const UserSettings* userSettingsFromSource, int32_t* const retFactory,
		int32_t* const retUser) {
	uint16_t psvnFactory = 0;
	uint16_t psvnTildaFactory = 0;
	READ_CONFIG_BY_MEMBER_NAME(factorySettings.psvn, (uint8_t* )&psvnFactory);
	READ_CONFIG_BY_MEMBER_NAME(factorySettings.psvnTilda,
			(uint8_t* )&psvnTildaFactory);
	if (!IsPSVNCorrectAndSame(factorySettingsFromSource->psvn,
			factorySettingsFromSource->psvnTilda, psvnFactory,
			psvnTildaFactory)) {
		SaveFactoryConfigsStr((uint8_t*) factorySettingsFromSource);
		*retFactory = 0;
	} else {
		(*retFactory)++;
	}

	uint16_t psvnUser = 0;
	uint16_t psvnTildaUser = 0;
	READ_CONFIG_BY_MEMBER_NAME(userSettings.psvn, (uint8_t* )&psvnUser);
	READ_CONFIG_BY_MEMBER_NAME(userSettings.psvnTilda,
			(uint8_t* )&psvnTildaUser);
	if (!IsPSVNCorrectAndSame(userSettingsFromSource->psvn,
			userSettingsFromSource->psvnTilda, psvnUser, psvnTildaUser)) {
		SaveUserConfigsStr((uint8_t*) userSettingsFromSource);
		*retUser = 0;
	} else {
		(*retUser)++;
	}
}
void _ValidateCRC(const FactorySettings* factorySettingsFromSource,
		const UserSettings* userSettingsFromSource, int32_t* const retFactory,
		int32_t* const retUser) {

	if (*retFactory > 0) {
		uint16_t factoryCrc = 0;
		READ_CONFIG_BY_MEMBER_NAME(factorySettings_crc, (uint8_t* )&factoryCrc);
		FactorySettings factorySettingsFromFlash;
		LoadFactoryConfigsStr((uint8_t*) &factorySettingsFromFlash);
		uint16_t calFactoryCrc = crcFast((uint8_t*) &factorySettingsFromFlash,
				sizeof(FactorySettings));
		if (factoryCrc == calFactoryCrc) {
			(*retFactory)++;
		} else {
			SaveFactoryConfigsStr((uint8_t*) factorySettingsFromSource);
		}
	}
	if (*retUser > 0) {
		uint16_t userCrc = 0;
		READ_CONFIG_BY_MEMBER_NAME(userSettings_crc, (uint8_t* )&userCrc);
		UserSettings userSettingsFromFlash;
		LoadUserConfigsStr((uint8_t*) &userSettingsFromFlash);
		uint16_t calUserCrc = crcFast((uint8_t*) &userSettingsFromFlash,
				sizeof(UserSettings));
		if (userCrc == calUserCrc) {
			(*retFactory)++;
		} else {
			SaveUserConfigsStr((uint8_t*) userSettingsFromSource);
		}
	}

}
void _ValidateSWVersion(const FactorySettings* factorySettingsFromSource,
		const UserSettings* userSettingsFromSource, int32_t* const retFactory,
		int32_t* const retUser) {

	if (*retFactory > 0) {
		uint16_t swVersionFactory = 0;
		READ_CONFIG_BY_MEMBER_NAME(factorySettings.softwareVersion,
				(uint8_t* )&swVersionFactory);
		uint16_t swVersionFactoryFromSource =
				factorySettingsFromSource->softwareVersion;
		if (swVersionFactory == swVersionFactoryFromSource) {
			(*retFactory)++;
		} else {
			SaveFactoryConfigsStr((uint8_t*) factorySettingsFromSource);
		}
	}
	if (*retUser > 0) {
		uint16_t swVersionUser = 0;
		READ_CONFIG_BY_MEMBER_NAME(userSettings.softwareVersion,
				(uint8_t* )&swVersionUser);
		uint16_t swVersionUserFromSource =
				userSettingsFromSource->softwareVersion;
		if (swVersionUser == swVersionUserFromSource) {
			(*retUser)++;
		} else {
			SaveUserConfigsStr((uint8_t*) userSettingsFromSource);
		}
	}
}
int32_t ValidateConfigurations(const FactorySettings* factorySettingsFromSource,
		const UserSettings* userSettingsFromSource) {
	int32_t retFactory = 0;
	int32_t retUser = 0;
	ASSERT_ON_COMPILE(
			sizeof(PersistentConfigStorage) <= MAX_CONFIG_STORAGE_SIZE);
	ASSERT_ON_COMPILE(
			sizeof(FactorySettings) + sizeof(UserSettings)
					< sizeof(PersistentConfigStorage) - 8);
	//generate virual adress table
	int i = 0;
	for (i = PERSISTENT_CONFIG_VIRTUAL_BASE_ADDR; i < NB_OF_CONFIG_VAR; i++) {
		VirtAddVarTab[i] = i;
	}

#ifndef DEBUGON
	_ValidatePSVN(factorySettingsFromSource, userSettingsFromSource,
			&retFactory, &retUser);
	_ValidateCRC(factorySettingsFromSource, userSettingsFromSource, &retFactory,
			&retUser);
	_ValidateSWVersion(factorySettingsFromSource, userSettingsFromSource,
			&retFactory, &retUser);
#endif
	return (int32_t) (retFactory + retUser);
}
