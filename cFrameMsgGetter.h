/****************************************************************/
/** @file:      cFrameMsgGetter.h
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		Nov 29, 2015
 *  @version:	1.6
 *  @brief:     simple serial human command interface
 *              _CommandGetterInitialize
 *              _CommandGetter
 *  @note:
 *		_this interface used interrupt serial and the same usart port for debug
 *		so its recommand to use it at low transfer rate. high transfer speed need to reexamine again
 *		with the consideration of :
 *			the level of utilization of sending usart debug
 *			any other IRQ that the STM need to be serve
 *		_the protocol for commands is very simple (without checksum, ANSCI base)
 *		the protocol format is: "?"[cmdID][para1][para2]"\r" or "!"[cmd][para1][para2]"\r"
 *		ever valid cmd received got a reply. a reply format is:
 *			[previousMark][previousCmdID][replyContent or NACK or ACK]
 *
 ****************************************************************/

#ifndef _cFrameMsgGetter_h
#define _cFrameMsgGetter_h
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void FrameMsgGetterInitialize(void);
int32_t FrameMsgGetter(char inputChar, char * outputStrCmd);

#ifdef __cplusplus
}
#endif
#endif
