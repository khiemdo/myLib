#include "main.h"
FILENUM(7);

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cRingBuffer.h"
#include "cAssert.h"

RingBuffer* RingBufferConstructor(){
	RingBuffer* me = calloc(1,sizeof(RingBuffer));
	REQUIRE(me);
	return me;
}
void RingBufferStructInit(RingBuffer* me) {
	memset(me, 0, sizeof(RingBuffer));
}
void RingBufferConfig(RingBuffer* me, uint32_t numberItems, uint32_t sizeItem) {
	REQUIRE(sizeItem!=0);
	REQUIRE(numberItems!=0);
	me->itemSize = sizeItem;
	me->bufferSize = numberItems * sizeItem;
	me->buffer = malloc((size_t) numberItems * sizeItem);
	REQUIRE(me->buffer!=0);
}

void PushRingBuffer(RingBuffer* me, void* item) {
	memcpy((void*) &me->buffer[me->head], (void*) item, me->itemSize);

	me->head += me->itemSize;
	if (me->head >= me->bufferSize) {
		me->head -= me->bufferSize;
	}

	if (me->active < me->bufferSize) {
		me->active += me->itemSize;
	} else {
		me->tail += me->itemSize;
		if (me->tail >= me->bufferSize) {
			me->tail -= me->bufferSize;
		}
	}

}
int PopRingBuffer(RingBuffer* me, void *item) {
	if (!me->active) {
		return -1;
	}

	memcpy((void*) item, (void*) &me->buffer[me->tail], me->itemSize);
	me->tail += me->itemSize;
	if (me->tail >= me->bufferSize) {
		me->tail -= me->bufferSize;
	}
	me->active -= me->itemSize;
	return 0;
}

void * GetFirstItemPtr(RingBuffer* me) {
	return (void*) ((uint32_t) me->buffer + (uint32_t) me->tail);
}
void * GetNextItemPtr(RingBuffer* me, void* currentPtr) {
	//currentPtr must be a multiple of me->itemSize
	int byteDistance = (int) ((uint32_t) currentPtr - (uint32_t) me->buffer);
	(void) byteDistance;

	void *tempPtr = (void *) ((uint32_t) currentPtr + (uint32_t) me->itemSize);
	if ((uint32_t) tempPtr
			>= ((uint32_t) me->buffer + (uint32_t) me->bufferSize)) {
		tempPtr = (void *)((uint32_t)tempPtr - (uint32_t)me->bufferSize);
	}

	if (((uint32_t) tempPtr - (uint32_t) me->buffer) == ((uint32_t) me->head)) {
		tempPtr = 0;
	}

	return tempPtr;
}

int GetNumberItemLeftOfRBuffer(RingBuffer* me) {
	return (me->bufferSize - me->active) / me->itemSize;
}
int GetNumberItemUsedOfRBuffer(RingBuffer* me) {
	return me->active / me->itemSize;
}
int GetNumberByteLeftOfRBuffer(RingBuffer* me) {
	return me->bufferSize - me->active;
}
int GetNumberByteUsedOfRBuffer(RingBuffer* me) {
	return me->active;
}
void FlushRingBuffer(RingBuffer* me) {
	me->head = 0;
	me->tail = 0;
	me->active = 0;
}
void FreeRingBuffer(RingBuffer* me) {
	if (me->itemSize != 0) {
		free(me->buffer);
		RingBufferStructInit(me);
	}
}
