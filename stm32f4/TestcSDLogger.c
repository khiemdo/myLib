#include "main.h"
FILENUM(10);

#include "TestcSDLogger.h"
#include "cSDLogger.h"
#include "cAssert.h"
#include <string.h>
#include <stdint.h>

void TestcSDLoggerConfig(void){
    int32_t ret = -1;

    ret = cSDLoggerConstructor();
    REQUIRE(ret == 0);
    ret = cSDLoggerGetFilePtr((int8_t *)"hello1.TXT");
    REQUIRE(ret == 0);
    (void)ret;
}
void TestcSDLogger(void){
    int32_t ret = -1;
    int8_t myString[] = "hello world. Hello File\r\n";

    ret = (int32_t)cSDLoggerWrite(myString, strlen((char*)myString) + 1);
    REQUIRE(ret != 0);
    ret = cSDLoggerCloseFilePtr();
    REQUIRE(ret != 0);
    ret = cSDLoggerDestructor();
    REQUIRE(ret == 0);
    (void)ret;
}
