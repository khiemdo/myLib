#include "main.h"
FILENUM(17)

#include "cConfigHandle.h"
#include "eeprom.h"
#include "configuration.h"
#include "cAssert.h"
#include "math.h"
#include "crc.h"
#include <stddef.h>

const factorySettings_t DEFAULT_FACTORY_SETTINGS = {
    .psvn            = 1,
    .psvnTilda       = 0,
    .softwareVersion = 2,
    .deviceID        = 3,
    .paraShort       = 4,
    .paraChar        = 5
};

const userSettings_t DEFAULT_USER_SETTINGS = {
    .paraIntU   = 6,
    .paraShortU = 7,
    .paraCharU  = 8
};
persistentConfigStorage_t persistentConfigStorage;

extern persistentConfigStorage_t persistentConfigStorage;

static uint16_t EE_FindValidPage1(uint8_t Operation){
    uint16_t PageStatus0 = 6, PageStatus1 = 6;

    /* Get Page0 actual status */
    PageStatus0 = (*(__IO uint16_t *)PAGE0_BASE_ADDRESS);

    /* Get Page1 actual status */
    PageStatus1 = (*(__IO uint16_t *)PAGE1_BASE_ADDRESS);

    /* Write or read operation */
    switch (Operation) {
        case WRITE_IN_VALID_PAGE: /* ---- Write operation ---- */
            if (PageStatus1 == VALID_PAGE) {
                /* Page0 receiving data */
                if (PageStatus0 == RECEIVE_DATA) {
                    return PAGE0; /* Page0 valid */
                } else {
                    return PAGE1; /* Page1 valid */
                }
            } else if (PageStatus0 == VALID_PAGE) {
                /* Page1 receiving data */
                if (PageStatus1 == RECEIVE_DATA) {
                    return PAGE1; /* Page1 valid */
                } else {
                    return PAGE0; /* Page0 valid */
                }
            } else {
                return NO_VALID_PAGE; /* No valid Page */
            }

        case READ_FROM_VALID_PAGE: /* ---- Read operation ---- */
            if (PageStatus0 == VALID_PAGE) {
                return PAGE0;   /* Page0 valid */
            } else if (PageStatus1 == VALID_PAGE) {
                return PAGE1;   /* Page1 valid */
            } else {
                return NO_VALID_PAGE; /* No valid Page */
            }

        default:
            return PAGE0;       /* Page0 valid */
    } /* switch */
} /* EE_FindValidPage */


/****************************************************************/
/** @brief: find the address of the configHeader
 *  @details: find the address of the configHeader
 *		if it near the end of the sector
 *		--> need to get the configStruct and save the whole configStruct again
 *  @param[int] VirtAddress: Variable virtual address
 *  @param[out] Data store the value of the psvn
 *  @retval lashAddress store the FlashAddress of the header:
 *           - flashAddress: if variable was found
 *           - 0: if the variable was not found or if no valid page was found
 *
 ****************************************************************/
uint32_t GetFlashAddressOfConfigHeader(uint16_t VirtAddress, uint16_t * Data){
    VirtAddress = PERSISTENT_CONFIG_VIRTUAL_BASE_ADDR;

    uint16_t ValidPage = PAGE0;
    uint16_t AddressValue = 0x5555, ReadStatus = 1;
    uint32_t Address = EEPROM_START_ADDRESS, PageStartAddress = EEPROM_START_ADDRESS;

    /* Get active Page for read operation */
    ValidPage = EE_FindValidPage1(READ_FROM_VALID_PAGE);

    /* Check if there is no valid page */
    if (ValidPage == NO_VALID_PAGE) {
        return 0;
    }

    /* Get the valid Page start Address */
    PageStartAddress = (uint32_t)(EEPROM_START_ADDRESS + (uint32_t)(ValidPage * PAGE_SIZE));

    /* Get the valid Page end Address */
    Address = (uint32_t)((EEPROM_START_ADDRESS - 2) + (uint32_t)((1 + ValidPage) * PAGE_SIZE));

    /* Check each active page address starting from end */
    while (Address > (PageStartAddress + 2)) {
        /* Get the current location content to be compared with virtual address */
        AddressValue = (*(__IO uint16_t *)Address);

        /* Compare the read address with the virtual address */
        if (AddressValue == VirtAddress) {
            /* Get content of Address-2 which is variable value */
            *Data = (*(__IO uint16_t *)(Address - 2));

            /* In case variable value is read, reset ReadStatus flag */
            ReadStatus = 0;
            break;
        } else {
            /* Next address location */
            Address = Address - 4;
        }
    }
    /* Return ReadStatus value: (0: variable exist, 1: variable doesn't exist) */
    if (ReadStatus == 1) {
        Address = 0;
    }
    return Address;
} /* GetFlashAddressOfConfigHeader */




void PersistentConfigRead(uint16_t offset, uint16_t nBytes, uint16_t * dest){
    REQUIRE(nBytes >= 2);
    uint32_t virtualAddress = PERSISTENT_CONFIG_VIRTUAL_BASE_ADDR + offset;
    uint16_t * valueArrayPtr = dest;
    while (nBytes) {
        EE_ReadVariable(virtualAddress, (uint16_t *)valueArrayPtr);
        virtualAddress += sizeof(uint16_t);
        valueArrayPtr = (uint16_t *)((uint32_t)valueArrayPtr + sizeof(uint16_t));
        nBytes -= sizeof(uint16_t);
    }
}
void PersistentConfigWrite(uint32_t offset, uint32_t nBytes, uint16_t * valueArray){
    REQUIRE(nBytes >= 2);
    uint16_t value = 0;    // *dest;
    uint32_t virtualAddress = PERSISTENT_CONFIG_VIRTUAL_BASE_ADDR + offset;
    uint16_t * valueArrayPtr = valueArray;
    // suppose nBytes>=2 and nBytes%2==0
    while (nBytes) {
        value = *(valueArrayPtr);
        EE_WriteVariable(virtualAddress, value);
        virtualAddress += sizeof(uint16_t);
        valueArrayPtr   = (uint16_t *)((uint32_t)valueArrayPtr + sizeof(uint16_t));
        nBytes -= sizeof(uint16_t);
    }
}
#define CONFIG_RD(M, D) \
    PersistentConfigRead(offsetof(persistentConfigStorage_t, M), SIZEOF(persistentConfigStorage_t, M), D)
#define CONFIG_WR(M, D) \
    PersistentConfigWrite(offsetof(persistentConfigStorage_t, M), SIZEOF(persistentConfigStorage_t, M), D)

/****************************************************************/
/** @brief: save DEFAULT_FACTORY_SETTINGS DEFAULT_USER_SETTINGS into the variable persistentConfigStorage
 *
 ****************************************************************/
void GetPersistentConfigFromSource(void) {
    persistentConfigStorage.factorySettings = DEFAULT_FACTORY_SETTINGS;
    persistentConfigStorage.factorySettings_crc = crcSlow(
            (uint8_t *)&persistentConfigStorage.factorySettings,
            FACTORY_SETTINGS_SIZE);
    persistentConfigStorage.userSettings = DEFAULT_USER_SETTINGS;
    persistentConfigStorage.userSettings_crc = crcSlow(
            (uint8_t *)&persistentConfigStorage.userSettings, USER_SETTINGS_SIZE);
}

/****************************************************************/
/** @brief: save DEFAULT_FACTORY_SETTINGS DEFAULT_USER_SETTINGS into eeprom
 *
 ****************************************************************/
void SaveSourceConfigIntoEEPROM1(void){

    uint32_t offset = offsetof(persistentConfigStorage_t, factorySettings);
    uint32_t nBytes = sizeof(factorySettings_t);

    PersistentConfigWrite(offset, nBytes, (uint16_t *)&DEFAULT_FACTORY_SETTINGS);

    uint8_t * testAddr = (uint8_t *)&DEFAULT_FACTORY_SETTINGS;
    int32_t testSize = sizeof(factorySettings_t);
    uint16_t fsCRC = crcSlow(testAddr, testSize);
    offset = offsetof(persistentConfigStorage_t, factorySettings_crc);
    nBytes = SIZEOF(persistentConfigStorage_t, factorySettings_crc);
    PersistentConfigWrite(offset, nBytes, (uint16_t *)&fsCRC);

    offset = offsetof(persistentConfigStorage_t, userSettings);
    nBytes = sizeof(userSettings_t);
    PersistentConfigWrite(offset, nBytes, (uint16_t *)&DEFAULT_USER_SETTINGS);

    testAddr = (uint8_t *)&DEFAULT_USER_SETTINGS;
    testSize = sizeof(userSettings_t);
    uint16_t usCRC = crcSlow(testAddr, testSize);
    offset = offsetof(persistentConfigStorage_t, userSettings_crc);
    nBytes = SIZEOF(persistentConfigStorage_t, userSettings_crc);
    PersistentConfigWrite(offset, nBytes, (uint16_t *)&usCRC);
} /* SaveSourceConfigIntoEEPROM1 */
void SaveSourceConfigIntoEEPROM(void){
    CONFIG_WR(factorySettings, (uint16_t *)&DEFAULT_FACTORY_SETTINGS);

    uint8_t * testAddr = (uint8_t *)&DEFAULT_FACTORY_SETTINGS;
    int32_t testSize = sizeof(factorySettings_t);
    uint16_t fsCRC = crcSlow(testAddr, testSize);
    CONFIG_WR(factorySettings_crc, (uint16_t *)&fsCRC);

    CONFIG_WR(userSettings, (uint16_t *)&DEFAULT_USER_SETTINGS);

    testAddr = (uint8_t *)&DEFAULT_USER_SETTINGS;
    testSize = sizeof(userSettings_t);
    uint16_t usCRC = crcSlow(testAddr, testSize);
    CONFIG_WR(userSettings_crc, (uint16_t *)&usCRC);
}

void LoadConfigFromEEPROMByID(int id, uint16_t * dest){
    CONFIG_RD(userSettings.paraShortU, dest);
}

/****************************************************************/
/** @brief:
 *  @details: must call the routine at the startup. It includes the helping functions
 *		_SaveSourceConfigIntoEEPROM
 *		_LoadAllConfigFromEEPROM
 *		_LoadConfigFromEEPROMByID
 *  @param:
 *  @return:
 *
 ****************************************************************/
void PersistentConfigInit(void) {
    CASSERT(sizeof(persistentConfigStorage_t) <= MAX_CONFIG_STORAGE_SIZE);

    GetPersistentConfigFromSource();

    // check configDebugFlag
    if (DEV_CONFIGURATION_FLAG) {    // in developement stage--> just use the config from source
        DEBUG(LOG_DEBUG, "in developement stage--> just use the config from source\r\n", 0);
    } else {
        factorySettings_t * fsFromSource = &(persistentConfigStorage.factorySettings);

        factorySettings_t * fsFromEEPROM;
        // check if psvnInEEPROM s corrupted
        if (fsFromEEPROM->psvn != ~(fsFromEEPROM->psvnTilda)) {
            // save default config into eeprom
        } else {
            if (fsFromEEPROM->psvn < fsFromSource->psvn) {               // check psvn versus compile psvn
                // save compile config
            } else {
                // load config from eeprom
            }

        }

    }
} /* PersistentConfigInit */
