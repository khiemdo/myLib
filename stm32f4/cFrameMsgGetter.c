#include "main.h"
FILENUM(3);

#include "cFrameMsgGetter.h"
#include "cDebugUart.h"
#include "cAssert.h"
#include <string.h>

#define MSGSTRINGSIZE 10

typedef enum {
    RESET_MSGGETTER_STATE, GETTING_MSGGETTER_STATE, RETURN_MSGGETTER_STATE
} StateCmdGetterEnum;

static int8_t msgString[MSGSTRINGSIZE];
static int32_t indexOfMsgString = 0;
static StateCmdGetterEnum stateFrameMsgGetter;

/****************************************************************/
/** @brief:	set the msgArr to all 0
 ****************************************************************/
void ClearFrameMsgStringBuff(){
    memset(msgString, 0, MSGSTRINGSIZE);
    indexOfMsgString = 0;
}
/****************************************************************/
/** @brief: initialize the private attribute of the frameMsgClass
****************************************************************/
void FrameMsgGetterInitialize(){
    ClearFrameMsgStringBuff();
    stateFrameMsgGetter = RESET_MSGGETTER_STATE;
}
/****************************************************************/
/** @brief: extract the frame msg from the serial stream
 *  @details:
 *  @param[in] inputChar: the int8_t get from the serial stream
 *  @param[out]outputStrCmd: to contain the valid msg when extracting successfully
 *  @return: then length of the frameMsg
 *
 ****************************************************************/
int32_t FrameMsgGetter(int8_t inputChar, int8_t * outputMsg){
    static int32_t msgLength = 0;
    int8_t ch = inputChar;

    switch (stateFrameMsgGetter) {
        case RESET_MSGGETTER_STATE:
            indexOfMsgString = 0;
            msgLength = 0;
            if (ch == '?' || ch == '!') {
                ClearFrameMsgStringBuff();
                msgString[indexOfMsgString] = ch;
                indexOfMsgString++;
                stateFrameMsgGetter = GETTING_MSGGETTER_STATE;
            }
            break;

        case GETTING_MSGGETTER_STATE:
            if (ch != '\0') {
                msgString[indexOfMsgString] = ch;
                indexOfMsgString++;
                if (ch != '\r') {
                    DEBUG(LOG_TEST, "%c", ch);
                } else {
                    DEBUG(LOG_TEST, "%c", ch);
                }

                if (ch == '\r') {
                    msgString[indexOfMsgString] = '\0';            // to replace '\r'
                    stateFrameMsgGetter = RETURN_MSGGETTER_STATE;
                }
            }
            break;

        case RETURN_MSGGETTER_STATE:
            memcpy(outputMsg, msgString, indexOfMsgString);
            msgLength = indexOfMsgString;
            stateFrameMsgGetter = RESET_MSGGETTER_STATE;
            ClearFrameMsgStringBuff();
            break;
    } /* switch */
    return msgLength;
} /* FrameMsgGetter */
