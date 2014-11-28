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

#define AddrROBO 42
#define AddrFRDM 43


typedef enum{
	duty_left,
	duty_right
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


static protocol42 txdata = {
		isROBOcop,
		duty_left,
		0
};

void sendData42(void);


#endif /* REMOTE_H_ */
