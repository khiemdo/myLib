/*
 * @author:khiem
 * @Date: 17/3/2015
 * @describe: using integrator algorithm to debound switch
 * http://www.kennethkuhn.com/electronics/debounce.c
 * @version: 2.0
 *
 real signal 0000111111110000000111111100000000011111111110000000000111111100000
 corrupted   0100111011011001000011011010001001011100101111000100010111011100010
 integrator  0100123233233212100012123232101001012321212333210100010123233321010
 output      0000001111111111100000001111100000000111111111110000000001111111000
 */

#ifndef cDebounceSwitch_h
#define cDebounceSwitch_h

#include "main.h"

#define CHECK_MSEC			1	//sample evey 1 ms
#define SAMPLE_FREQUENCY    (1000/CHECK_MSEC)	//sampling_fre = 1/CHECK_MSEC = 1000Hz
#define DEBOUNCE_TIME       (0.01)	//in s
#define MAXIMUM         	((int32_t)(DEBOUNCE_TIME*SAMPLE_FREQUENCY))

typedef enum {
	PRESSED = 1, RELEASED = 0
} BtnState;

typedef struct {
	int32_t id;
	int32_t keyIntegrator;
	BtnState keyPressed; //hold the debounce state of btn
	uint32_t lastTime;
	uint16_t pin;
	GPIO_TypeDef* port;
} cDebounceBtn;

cDebounceBtn* cDebounceBtnConstructor();
void cDebounceBtnInit(cDebounceBtn *me);
void cDebounceBtnLoop(cDebounceBtn *me);
int32_t ReadDebounceBtn(cDebounceBtn *me);
void cDebounceBtnConfig1(cDebounceBtn *me);
#endif
