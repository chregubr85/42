/*
 * remote.c
 *
 *  Created on: 28.11.2014
 *      Author: Stefan
 */

#include "remote.h"
#if PL_HAS_DRIVE
	#include "Drive.h"
#endif
#include "Keys.h"


void sendData42(protocol42 txdata){
	uint8_t dest;


	if(txdata.target == isFRDM){
		dest = ADDR_FRDM;
	} else if(txdata.target == isROBOcop){
		dest = ADDR_ROBO;
	}

	(void)RAPP_SendPayloadDataBlock(&txdata, sizeof(txdata), RAPP_MSG_TYPE_PROTOCOL42, dest, 42);

}

void reciveData42(protocol42 rxdata){
	protocol42_type typ;
	int32_t testi, testi_old;
	  uint8_t buf[32];
	  CLS1_ConstStdIOTypePtr io = CLS1_GetStdio();

	typ = rxdata.type;
	switch (typ) {
	case duty_left:

		break;
	case duty_right:

		break;
	case anal_x:

		break;
	case anal_y:
#if PL_HAS_DRIVE
		if (!calibratetY) {
			ycalib = rxdata.data;
			calibratetY = TRUE;
			DRV_EnableDisable(TRUE);
		}
testi = (rxdata.data-ycalib);
testi = testi<<8;

if(testi != testi_old) {

	CLS1_SendStr((unsigned char*)"Recived Value: ", io->stdOut);
	CLS1_SendNum16s(rxdata.data, io->stdOut);

	CLS1_SendStr((unsigned char*)"     Recived Value - calib: ", io->stdOut);
	CLS1_SendNum32s(rxdata.data-ycalib, io->stdOut);

	CLS1_SendStr((unsigned char*)"     Shifted Value: ", io->stdOut);
	CLS1_SendNum32s(testi, io->stdOut);

	buf[0] = '\0';
	UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
	CLS1_SendStr(buf, io->stdOut);
	testi_old = testi;
}



		//DRV_SetSpeed(testi, testi);
#endif
		break;
	default:
		break;
	}

}



