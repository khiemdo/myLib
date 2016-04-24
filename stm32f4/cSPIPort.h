#ifndef _cSPIPort_h
#define _cSPIPort_h
#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#define SPIx		SPI3

void SPI2PortConfig(SPI_HandleTypeDef* hspi);
void SPI3PortConfig(SPI_HandleTypeDef* hspi);

#ifdef __cplusplus
}
#endif
#endif
