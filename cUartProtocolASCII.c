#include "main.h"
FILENUM(13);

#include "cUartProtocolASCII.h"
#include "cDebugUart.h"
#include "cAssert.h"
#include <stdio.h>
#include <stdlib.h>

const int32_t msgSerialIDArr[] = { 0x00, // NO_MSG
                               0x01, // VERSION_QUERY
                               0x02, // EXAMPLE_QUERY
};
const int32_t msgSerialLengthArr[] = { 0x00, // NO_MSG
                                   3, // VERSION_QUERY
                                   1 // EXAMPLE_QUERY
};

#define EXTRACT_SERIAL_MSGID(X)     *(X)
#define EXTRACT_SERIAL_MSGLENGTH(X) *((X + 1))

/****************************************************************/
/** @brief: the interface of sending msg
 *  @details: it helps to call debugPrintf to use for send MsgProtocol
 *      it is a seperated function to give a choice of change it to another
 *      comInterface, such as CAN, or normalUart.
 *  @param:
 *  @return:
 *
 ****************************************************************/
int32_t SendSerialProtocolMsg(char * msg) {
    int32_t ret = UDebugPrintf(msg);

    return ret;
}
int32_t SendSerialACK(int8_t msgID, int32_t length) {
    char msg[32];

    sprintf((char*)msg,  "%d|%d||ACK\r\n", msgID, (int)length);
    int32_t ret = SendSerialProtocolMsg(msg);
    return ret;
}
int32_t SendSerialNACK(int8_t msgID, int32_t length) {
    char msg[32];

    sprintf((char*)msg, "%d|%d|NACK\r\n", msgID, (int)length);
    int32_t ret = SendSerialProtocolMsg(msg);
    return ret;
}
int32_t SendSerialVersion() {
    char msg[32];

    sprintf((char*)msg, "%d|%d|%s|%s\r\n", (int)msgSerialIDArr[VERSION_QUERY],
    		(int)msgSerialLengthArr[VERSION_QUERY], PROJECT_NAME,
            PROJECT_PROTOCOL_VERSION);
    int32_t ret = SendSerialProtocolMsg(msg);
    return ret;
}
/* ------ ADD UR OWN SENDING METHOD HERE	------*/

/****************************************************************/
/** @brief:	from the msgArr--> determine msgID
 *  @details:
 *  @param[in] msg: array contained msg
 *  @param[in] length: msg Length
 *  @return: msgID corresponding with the processed msg
 *
 ****************************************************************/
int32_t MarshallSerialMsg(char * msg, int32_t length) {
    int32_t i = 0;

    for (i = 1; i < NUMBER_SERIAL_MSG_TYPE; i++) {
        if (EXTRACT_SERIAL_MSGID(msg) == msgSerialIDArr[VERSION_QUERY]
            && EXTRACT_SERIAL_MSGLENGTH(msg)
            == msgSerialLengthArr[VERSION_QUERY]) {
            return VERSION_QUERY;
        } else if (EXTRACT_SERIAL_MSGID(msg) == msgSerialIDArr[EXAMPLE]
                   && EXTRACT_SERIAL_MSGLENGTH(msg)
                   == msgSerialLengthArr[EXAMPLE]) {
            return EXAMPLE;
        }
        /* ------ ADD UR OWN CONDITION HERE	------*/
    }

    return INVALID_MSG;
}
/****************************************************************/
/** @brief:	reaction behavior base on
 *      msgType, which s the result of calling MarshallSerialMsg
 *  @details:
 *  @param[in] msg: array contained msg
 *  @param[in] length: msg Length
 *  @return:
 *
 ****************************************************************/
int32_t SerialMsgHandleController(char * msg, int32_t length) {
    int32_t msgType = MarshallSerialMsg(msg, length);

    switch (msgType) {
        case VERSION_QUERY:
            SendSerialVersion();
            break;
        case EXAMPLE:
            SendSerialACK(EXTRACT_SERIAL_MSGID(msg), EXTRACT_SERIAL_MSGLENGTH(msg));
            break;
        case INVALID_MSG:
            SendSerialNACK(EXTRACT_SERIAL_MSGID(msg),
                           EXTRACT_SERIAL_MSGLENGTH(msg));
            break;
            /* ------ ADD UR OWN REACTION CASES HERE	------*/
    }

    return msgType;
}
