/*
 * remote.c
 *
 *  Created on: 28.11.2014
 *      Author: Stefan
 */

#include "remote.h"


void sendData42(void){
	uint8_t dest;
	if(txdata.target == isFRDM){
		dest = AddrFRDM;
	} else if(txdata.target == isROBOcop){
		dest = AddrROBO;
	}
	RAPP_SendPayloadDataBlock(&txdata, sizeof(txdata), RAPP_MSG_TYPE_DATA, dest, 42);
}
