#include "main.h"
FILENUM(15);

#include <stddef.h>
#include "utility.h"

void InitGPIOClockByGPIOName(GPIO_TypeDef* me) {
	__IO uint32_t tmpreg = 0x00U;
	if (me == GPIOA) {
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
	} else if (me == GPIOB) {
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
	} else if (me == GPIOC) {
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
	} else if (me == GPIOD) {
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
	} else if (me == GPIOE) {
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);
	} else if (me == GPIOF) {
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);
	} else if (me == GPIOG) {
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);
	} else if (me == GPIOH) {
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN);
	} else if (me == GPIOI) {
		SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);
	}
	(void)(tmpreg);
}

//#define POLY 0x8408
/*
 * //                                      16   12   5
 * // this is the CCITT CRC 16 polynomial X  + X  + X  + 1.
 * // This works out to be 0x1021, but the way the algorithm works
 * // lets us use 0x8408 (the reverse of the bit pattern).  The high
 * // bit is always assumed to be set, thus we only use 16 bits to
 * // represent the 17 bit value.
 */
//uint16_t crc16(int8_t * data_p, uint16_t length){
//    uint8_t i;
//    uint32_t data;
//    uint32_t crc = 0xffff;
//
//    if (length == 0)
//        return (~crc);
//
//    do {
//        for (i = 0, data = (uint32_t)0xff & *data_p++;
//             i < 8;
//             i++, data >>= 1) {
//            if ((crc & 0x0001) ^ (data & 0x0001))
//                crc = (crc >> 1) ^ POLY;
//            else  crc >>= 1;
//        }
//    } while (--length);
//
//    crc = ~crc;
//    data = crc;
//    crc = (crc << 8) | (data >> 8 & 0xff);
//
//    return (crc);
//} /* crc16 */
