/****************************************************************/
/** @file:      <cSDLogger.h>
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		6/12/15
 *  @version:	1.0
 *  @brief:   singleton for sdCardLogging
 *
 *  @note:    only allow to write into the file, append the new content
 *							end of the file
 *
 ****************************************************************/

#ifndef _cSDLogger_h
#define _cSDLogger_h
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

int32_t cSDLoggerConstructor(void);
int32_t cSDLoggerDestructor(void);
int32_t cSDLoggerGetFilePtr(const int8_t * fileName);
int32_t cSDLoggerCloseFilePtr(void);
uint32_t cSDLoggerWrite(int8_t * wtext, int32_t length);

#ifdef __cplusplus
}
#endif
#endif
