/*
 * remote.h
 *
 *  Created on: 28.11.2014
 *      Author: Stefan
 */

#ifndef REMOTE_H_
#define REMOTE_H_

#include "platform.h"
#include "RApp.h"
#include "RNet_App.h"
#include "RTOS.h"

#define ADDR_ROBO 42
#define ADDR_FRDM 43

static bool remoteON;
static bool calibratetY, calibratetX;

int32_t valX, valY;

typedef enum{
	activateRemote,
	anal_x, //HIHI ANAL
	anal_y
} protocol42_type;

typedef enum{
	isFRDM,
	isROBOcop
} targetPL;


typedef struct{
	targetPL target;
	protocol42_type type;
	uint8_t data;
} protocol42;


void sendData42(protocol42 txdata);

void reciveData42(protocol42 rxdata);

int32_t u8To32s(uint8_t val, bool x);

int8_t ScaleToPercent(uint8_t val, bool x);

void remoteInit(void);


#endif /* REMOTE_H_ */
