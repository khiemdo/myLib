#ifndef _utility_h
#define _utility_h
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0)

void FletcherChecksum(void);
uint16_t crc16(int8_t * data_p, uint16_t length);

#ifdef __cplusplus
}
#endif
#endif
