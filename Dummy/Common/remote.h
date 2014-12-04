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

#define ADDR_ROBO 42
#define ADDR_FRDM 43

static bool calibratetY;

typedef enum{
	duty_left,
	duty_right,
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
	int16_t data;
} protocol42;


/*static protocol42 txdata = {
		isROBOcop,
		duty_left,
		0
};*/

void sendData42(protocol42 txdata);

void reciveData42(protocol42 rxdata);


#endif /* REMOTE_H_ */
