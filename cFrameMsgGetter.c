//#include "main.h"
//FILENUM(3);

#include "cFrameMsgGetter.h"
#include "cAssert.h"
#include <string.h>

/****************************************************************/
/** @brief:	set the msgArr to all 0
 ****************************************************************/
void ClearFrameMsgStringBuff(cFrameMsgGetter* me) {
	memset(me->msgString, 0, me->msgsSize);
	me->indexOfMsgString = 0;
}
/****************************************************************/
/** @brief: initialize the private attribute of the frameMsgClass
 ****************************************************************/
void FrameMsgGetterInitialize(cFrameMsgGetter* me, int32_t msgsSize,
		int8_t* msgString, int8_t* outputFrame) {
	me->msgsSize = msgsSize;
	me->msgString = msgString;
	me->outputFrame = outputFrame;
	ClearFrameMsgStringBuff(me);
	me->lastMsgLength = 0;
	me->stateFrameMsgGetter = RESET_MSGGETTER_STATE;
}
/****************************************************************/
/** @brief: extract the frame msg from the serial stream
 *  @details:
 *  @param[in] inputChar: the int8_t get from the serial stream
 *  @param[out]outputStrCmd: to contain the valid msg when extracting successfully
 *  @return: then length of the frameMsg
 *
 ****************************************************************/
int32_t FrameMsgGetter(cFrameMsgGetter* me, const int8_t inputChar,
		int8_t * outputMsg) {
	int8_t ch = inputChar;

	switch (me->stateFrameMsgGetter) {
	case RESET_MSGGETTER_STATE:
		me->indexOfMsgString = 0;
		if (ch == '?' || ch == '!') {
			ClearFrameMsgStringBuff(me);
			me->msgString[me->indexOfMsgString] = ch;
			me->indexOfMsgString++;
			me->stateFrameMsgGetter = GETTING_MSGGETTER_STATE;
		}
		break;

	case GETTING_MSGGETTER_STATE:
		if (ch != '\0') {
			me->msgString[me->indexOfMsgString] = ch;
			me->indexOfMsgString++;
			if (ch != '\r') {
				DEBUG(LOG_TEST, "%c", ch);
			} else {
				DEBUG(LOG_TEST, "%c", ch);
			}

			if (ch == '\r') {
				me->msgString[me->indexOfMsgString] = '\0'; // to replace '\r'
				me->stateFrameMsgGetter = RETURN_MSGGETTER_STATE;
			}
		}
		break;

	case RETURN_MSGGETTER_STATE:
		memcpy(outputMsg, me->msgString, me->indexOfMsgString);
		me->stateFrameMsgGetter = RESET_MSGGETTER_STATE;
		ClearFrameMsgStringBuff(me);
		return me->indexOfMsgString;
		break;
	} /* switch */
	return 0;
} /* FrameMsgGetter */
