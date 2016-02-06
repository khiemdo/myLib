#ifndef _configuration_h
#define _configuration_h
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MAX_CONFIG_STORAGE_SIZE 300
#define FACTORY_SETTINGS_SIZE   100
#define USER_SETTINGS_SIZE      100

#define DEV_CONFIGURATION_FLAG  1

typedef struct {
    uint32_t psvn;    // persistent version number
    uint32_t psvnTilda;    ///~psvn
    uint32_t softwareVersion;
    uint32_t deviceID;
    uint32_t paraShort;
    uint32_t paraChar;
}factorySettings_t;

typedef struct {
    uint32_t paraIntU;
    uint32_t paraShortU;
    uint32_t paraCharU;
}userSettings_t;

typedef enum {
    PWVN = 0,
    PSVNTILDA = 4,
    SOFTWARE_VERSION = 8,
    DEVICE_CAN_ID = 12,
    PARASHORT = 16,
    PARACHAR = 20,
    PARAINTU = 24,
    PARASHORTU = 28,
    PARACHARU       = 32
}SettingEnum;

typedef struct {
    factorySettings_t factorySettings;
    uint8_t factorySettings_pad[FACTORY_SETTINGS_SIZE - sizeof(factorySettings_t)];
    uint16_t factorySettings_crc;
    userSettings_t userSettings;
    uint8_t userSettings_pad[USER_SETTINGS_SIZE - sizeof(userSettings_t)];
    uint16_t userSettings_crc;
}persistentConfigStorage_t;

#ifdef __cplusplus
}
#endif
#endif
