/****************************************************************/
/** @file:    cConfigHandle.h
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		7/12
 *  @version:	1.0
 *  @brief:   this allow to
 *			_ get the config version
 *			_ get config
 *			_ save new config
 *			_ uC load config at the start of program
 *			_ have version control manager
 *			
 *				
 *
 *  @note:
 *		_ NEVER EVER PUT THE FLASH WRITING IN THE LOOP
 *		 	--> the flash will die anytime very soon cuz of continuous writing
 *     	_when upload firmware, need configuring the memory map area
 *              to reserve the configuration saving space
 *  @ref:
 *  	http://www.barrgroup.com/Embedded-Systems/How-To/Preserve-Non-Volatile-Data-Software-Versions
 *  	http://embeddedgurus.com/stack-overflow/2009/11/keeping-your-eeprom-data-valid-through-firmware-updates/
 ****************************************************************/
#ifndef _cConfigHandl_h
#define _cConfigHandl_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "configuration.h"
#include <stdint.h>

#define COMPILE_PSVN 1
#define PERSISTENT_CONFIG_VIRTUAL_BASE_ADDR	 0x01

#define READ_CONFIG_BY_MEMBER_NAME(CONFIG_NAME, BUFF) \
		ReadConfigInEEPROMEmul\
    		(offsetof(PersistentConfigStorage, CONFIG_NAME), \
    		SIZEOF(PersistentConfigStorage, CONFIG_NAME), BUFF)
#define WRITE_CONFIG_BY_MEMBER_NAME(CONFIG_NAME, BUFF) \
		WriteConfigInEEPROMEmul \
    			(offsetof(PersistentConfigStorage, CONFIG_NAME), \
    			SIZEOF(PersistentConfigStorage, CONFIG_NAME), BUFF)
#define WRITE_CONFIG_BY_MEMBER_NAME_WITH_CRC(CONFIG_NAME, BUFF) \
		do { \
			WriteConfigInEEPROMEmul(offsetof(PersistentConfigStorage, CONFIG_NAME), \
					SIZEOF(PersistentConfigStorage, CONFIG_NAME), BUFF); \
			if (offsetof(PersistentConfigStorage, CONFIG_NAME) \
					< FACTORY_SETTINGS_SIZE \
					&& offsetof(PersistentConfigStorage, CONFIG_NAME) \
							< USER_SETTINGS_SIZE) { \
				uint16_t fsCRC = crcFast((uint8_t*) BUFF, sizeof(FactorySettings)); \
				WRITE_CONFIG_BY_MEMBER_NAME(factorySettings_crc, (uint8_t* )&fsCRC); \
			} else { \
				uint16_t fsCRC = crcFast((uint8_t*) BUFF, sizeof(UserSettings)); \
				WRITE_CONFIG_BY_MEMBER_NAME(userSettings_crc, (uint8_t* )&fsCRC); \
			} \
		} while (0)

#define SIZEOF(s,m) ((size_t) sizeof(((s *)0)->m))

extern int32_t ReadConfigInEEPROMEmul(const uint32_t offset, uint32_t nBytes,
		uint8_t * const dest);
extern int32_t WriteConfigInEEPROMEmul(const uint32_t offset, uint32_t nBytes,
		uint8_t * const valueBuff);
int32_t LoadAllConfigsStr(uint8_t* const buff);
int32_t SaveAllConfigsStr(uint8_t* const buff);
int32_t LoadFactoryConfigsStr(uint8_t* const buff);
int32_t SaveFactoryConfigsStr(uint8_t* const buff);
int32_t LoadUserConfigsStr(uint8_t* const buff);
int32_t SaveUserConfigsStr(uint8_t* const buff);

int32_t ValidateConfigurations(const FactorySettings* factorySettingsFromSource,
		const UserSettings* userSettingsFromSource);

#ifdef __cplusplus
}
#endif
#endif
