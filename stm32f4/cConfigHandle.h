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
 *
 ****************************************************************/
#ifndef _cConfigHandl_h
#define _cConfigHandl_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>

#define COMPILE_PSVN 1
#define PERSISTENT_CONFIG_VIRTUAL_BASE_ADDR	 0x01

#define CASSERT(ex) { typedef uint8_t cassert_type[(ex) ? 1 : -1]; }
#define SIZEOF(s,m) ((size_t) sizeof(((s *)0)->m))
		
int32_t GetConfigVersion(void);
int32_t SetConfigVersion(void);
int32_t ResetConfigVersion(void);
int32_t GetConfigByID(int32_t id);
int32_t SaveConfigByID(int32_t id, int32_t value);

void PersistentConfigInit(void);
void SaveSourceConfigIntoEEPROM(void);
uint32_t GetFlashAddressOfConfigHeader(uint16_t VirtAddress, uint16_t * Data);
void LoadConfigFromEEPROMByID(int id, uint16_t* dest);
void GetPersistentConfigFromSource(void) ;

#ifdef __cplusplus
}
#endif
#endif
