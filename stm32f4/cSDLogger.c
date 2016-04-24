#include "main.h"
FILENUM(9);
#ifdef FATFS
#include "cSDLogger.h"
#include "cAssert.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"

static FATFS SDFatFs;  /* File system object for SD card logical drive */
static int8_t SDPath[4]; /* SD card logical drive path */
static FIL MyFile;     /* File object */

int32_t cSDLoggerConstructor(void){
    int32_t ret = -1;

    ret = FATFS_LinkDriver(&SD_Driver, (char*)SDPath);
    REQUIRE(ret == 0);
    ret += f_mount(&SDFatFs, (TCHAR const *)SDPath, 0);
    REQUIRE(ret == FR_OK);
//	ret += f_mkfs((TCHAR const*)SDPath, 0, 0);
//	REQUIRE(ret==FR_OK);
    return ret;
}
int32_t cSDLoggerGetFilePtr(const int8_t * fileName){
    int32_t ret = -1;

    ret = f_open(&MyFile, (char*)fileName, FA_OPEN_ALWAYS | FA_WRITE);
    ret += f_lseek(&MyFile, f_size(&MyFile));
    return ret;
}
int32_t cSDLoggerCloseFilePtr(void){
    return f_close(&MyFile);
}

uint32_t cSDLoggerWrite(int8_t * wtext, int32_t length){
    int32_t ret = -1;
    uint32_t byteswritten;

    ret = f_write(&MyFile, wtext, length, (void *)&byteswritten);
    REQUIRE(ret == FR_OK);
    (void)ret;
    return byteswritten;
}

int32_t cSDLoggerDestructor(void){
    int32_t ret;

    ret = FATFS_UnLinkDriver((char*)SDPath);
    REQUIRE(ret == 0);
    return ret;
}
#endif
