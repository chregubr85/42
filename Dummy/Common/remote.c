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
#include "Motor.h"
#include "Event.h"


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
	int32_t testi, testii, testi_old, testii_old;
	uint8_t buf[32];
	CLS1_ConstStdIOTypePtr io = CLS1_GetStdio();


	uint8_t rxold;
	uint8_t delta =0;

	typ = rxdata.type;
	switch (typ) {
	case activateRemote:

		if(!remoteON) {
			remoteON = TRUE;
			EVNT_SetEvent(EVNT_REMOTE_ACTIVATE);
		}
		else {
			remoteON = FALSE;
			EVNT_SetEvent(EVNT_REMOTE_DEACTIVATE);
		}

		break;

	case anal_x:
		if (!calibratetX) {
			xcalib = rxdata.data;
			calibratetX = TRUE;
		}
		valX = (ScaleToPercent(rxdata.data, TRUE)>>1);

		break;
	case anal_y:
		if (!calibratetY) {
			ycalib = rxdata.data;
			calibratetY = TRUE;
		}
		valY = ScaleToPercent(rxdata.data, FALSE);
/*
	testi = valX;
	testii = valY;

	if((testi != testi_old) || (testii != testii_old)) {

		CLS1_SendStr((unsigned char*)"X Value: ", io->stdOut);
		CLS1_SendNum16s(testi, io->stdOut);

		CLS1_SendStr((unsigned char*)"     Y Value: ", io->stdOut);
		CLS1_SendNum32s(testii, io->stdOut);

		buf[0] = '\0';
		UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
		CLS1_SendStr(buf, io->stdOut);
		testi_old = testi;
		testii_old = testii;
	}

*/

		break;
	default:
		break;
	}

}

int32_t u8To32s(uint8_t val, bool x) {

	int32_t scaled = 0;
	uint32_t calib = 0;


	if(x){
		calib = xcalib;
	}
	else {
		calib = ycalib;
	}



	if(val>calib){
		scaled = (0x7FFFFFFF*(val-calib))/(0xFF-calib);
	}
	else{
		scaled = -(0x7FFFFFFF*(val-calib))/(0xFF-calib);
	}


	return scaled;

}

int8_t ScaleToPercent(uint8_t val, bool x) {

  int8_t temp;
  uint8_t calib, min;

	if(x){
		calib = xcalib;
		min = xmin;
	}
	else {
		calib = ycalib;
		min = ymin;
	}

  if(val < calib){
		  temp = -100+(100*(val-min))/(calib-min);
	  }
	  else if(val > calib){
		  temp = (100*(val-calib))/(255-calib);
	  }
	  else {
		  temp = 0;
	  }

	  return temp;
}

void remoteInit(void) {
	remoteON = FALSE;
	FRTOS1_vTaskSuspend(remoteTask);
}


