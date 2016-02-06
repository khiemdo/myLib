#ifndef _TestcConfigHandle_h
#define	_TestcConfigHandle_h
#ifdef __cplusplus
extern "C" {
#endif

void TestcConfigHandleConfig(void);
int32_t TestcConfigHandle_offsetof(void);
void TestcConfigHandleConfig_SaveDefaultConfigIntoEEPROM(void);
void TestcConfigHandleConfig_GetFlashAddressOfConfigHeader(void);
void TestcConfigHandleConfig_LoadConfigFromEEPROMByID(void);

#ifdef __cplusplus
}
#endif
#endif
