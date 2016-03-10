/****************************************************************/
/** @file:      cUartProtocolASCII.h
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		Nov 29, 2015
 *  @version:	1.0
 *  @brief:     define serial Protocol, base on cDebugUart ANSCI. it s project-specific
 *  @note:
 *      _basic query:protocolVersion, projectProtocolName,
 *      _has reponse for every valid cmd
 *      _ReceiveMsgFormat: "?"|id(1byte)|Length(1byte)|Content|(CS)|"\r"
 *      _ReplyMsgFormat: "?"|[previousID|Length|Reply or ACK or NACK|(CS)|"\r"
 *
 ****************************************************************/

#ifndef _cUartProtocolAscii_h
#define _cUartProtocolAscii_h
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define NUMBER_SERIAL_MSG_TYPE   3
#define PROJECT_PROTOCOL_VERSION "1.0.0"
#define PROJECT_NAME             "HELLO"

typedef enum {
	INVALID_MSG = -1, NO_SERIAL_MSG, VERSION_QUERY, EXAMPLE
} SERIAL_MSGID_PROTOCOL;

int32_t SendSerialACK(int8_t msgID, int32_t length);
int32_t SendSerialNACK(int8_t msgID, int32_t length);
int32_t SendSerialVersion(void);
int32_t SendSerialExample(void);
int32_t MarshallSerialMsg(char * msg, int32_t length);
int32_t SerialMsgHandleController(char * msg, int32_t length);

#ifdef __cplusplus
}
#endif
#endif
