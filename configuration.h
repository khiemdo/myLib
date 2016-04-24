/****************************************************************/
/** @file:      configuration.h
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		Mar 19, 2016
 *  @version:	1.0
 *  @brief:     store non-volatile data into FLASH-eeprom emul
 *  	with crc, psvn, softwareVersion
 *
 *  @note:
 *		FactorySettings to store factory calibration, MAC ADDR, ...
 *		UserSettings to store any project-dependent data
 *		Every member of the structure must be type uint16_t at least
 *		Ensure MAX_CONFIG_STORAGE_SIZE, FACTORY_SETTINGS_SIZE, USER_SETTINGS_SIZE is valid (enought spaces, and sum correct)
 *		PSVN = persistent store version number. it reflects the structure of PersistentConfigStorage
 *			any time the type of the member in the structure changes, psvn must change as well
 *			any time the layout of the structure changes, psn must change
 *			If it doesn't match the compile time constant,
 *				we know that this version of software is being run for the first time on this device.
 *				It will be necessary to set any new fields to sensible defaults
 *		SoftwareVersion: it reflects the default value of every members inside structure
 *		must make sure that
 *		if wanna to remove any member from the structure, just rename it to "dummy"
 ****************************************************************/

#ifndef _configuration_h
#define _configuration_h
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MAX_CONFIG_STORAGE_SIZE 300
#define FACTORY_SETTINGS_SIZE   140
#define USER_SETTINGS_SIZE      150

#define DEV_CONFIGURATION_FLAG  1

/*
 * @brief: to store
 */
typedef struct factorySettings_t {
	uint16_t psvn;    		// persistent version number
	uint16_t psvnTilda;		//~psvn, for error checking
	uint16_t softwareVersion;
	uint16_t deviceID;
	uint16_t paraU16;
	uint32_t paraU32;
	int16_t paraI16;
	int32_t paraI32;
	float paraF;
	char string1[2];
	char string2[3];
	char string3[4];
	char char1;
} FactorySettings;

typedef struct userSettings_t {
	uint16_t psvn;    		// persistent version number
	uint16_t psvnTilda;		//~psvn, for error checking
	uint16_t softwareVersion;
	uint16_t deviceID;
	uint16_t paraU16;
	uint32_t paraU32;
	int16_t paraI16;
	int32_t paraI32;
	float paraF;
	char string1[6];
	char string3[8];
} UserSettings;

//todo
typedef struct persistentConfigStorage_t {
	FactorySettings factorySettings;
	uint8_t factorySettings_pad[FACTORY_SETTINGS_SIZE - sizeof(FactorySettings)];
	uint16_t factorySettings_crc;
	UserSettings userSettings;
	uint8_t userSettings_pad[USER_SETTINGS_SIZE - sizeof(UserSettings)];
	uint16_t userSettings_crc;
} PersistentConfigStorage;

typedef enum {
	PSVN_FACTORY_SETTING,
	PSVNTILDA_FACTORY_SETTING,
	SOFTWAREVERSION_FACTORY_SETTING,
	DEVICEID_FACTORY_SETTING,
	PARAU8_FACTORY_SETTING,
	PARAU16_FACTORY_SETTING,
	PARAU32_FACTORY_SETTING,
	PARAI8_FACTORY_SETTING,
	PARAI16_FACTORY_SETTING,
	PARAI32_FACTORY_SETTING,
} FACTORY_SETTING_INDEX;

typedef enum {
	PSVN_USER_SETTING,
	PSVNTILDA_USER_SETTING,
	SOFTWAREVERSION_USER_SETTING,
	DEVICEID_USER_SETTING,
	PARAU8_USER_SETTING,
	PARAU16_USER_SETTING,
	PARAU32_USER_SETTING,
	PARAI8_USER_SETTING,
	PARAI16_USER_SETTING,
	PARAI32_USER_SETTING,
} USER_SETTING_INDEX;

#ifdef __cplusplus
}
#endif
#endif
