/****************************************************************/
/** @file:      cRingBuffer.h
 *  @author:	DO HOANG DUY KHIEM
 *  @date:		Dec 27, 2015
 *  @version:	1.5
 *  @brief:     <Brief description of what the file does>
 *
 *  @note:
 *
 ****************************************************************/

#ifndef         _cRingBuffer_h
#define         _cRingBuffer_h
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct RingBufferStr {
	int8_t * buffer;
	volatile int32_t head, tail, active;
	int32_t itemSize, bufferSize;
} RingBuffer;

void RingBufferStructInit(RingBuffer * me);
void RingBufferConfig(RingBuffer* me, int8_t* buff, uint32_t numberItems, uint32_t sizeItem);
void PushRingBuffer(RingBuffer * me, void * item);
int32_t PopRingBuffer(RingBuffer * me, void * item);
int32_t GetNumberItemLeftOfRBuffer(RingBuffer * me);
int32_t GetNumberItemUsedOfRBuffer(RingBuffer * me);
int32_t GetNumberByteLeftOfRBuffer(RingBuffer * me);
int32_t GetNumberByteUsedOfRBuffer(RingBuffer * me);

// this routine faster than GetNumberItemLeftOfRBuffer in checking if the buffer avail
int32_t GetNumberByteLeftOfRBuffer(RingBuffer * me);
void * GetFirstItemPtr(RingBuffer * me);
void * GetNextItemPtr(RingBuffer * me, void * currentPtr);

void FlushRingBuffer(RingBuffer * me);
void FreeRingBuffer(RingBuffer * me);

#ifdef __cplusplus
}
#endif
#endif /* ifndef         _cRingBuffer_h */
