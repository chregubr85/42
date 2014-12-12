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
#include "Fight.h"


bool remoteOn, analogOn, accelOn, reflOn;
bool calibratetY, calibratetX;

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

	case activateFight:

		if(!fightOn) {
			fightOn = TRUE;
			EVNT_SetEvent(EVNT_FIGHTMODE_ACTIVATE);
		}
		else {
			fightOn = FALSE;
			EVNT_SetEvent(EVNT_FIGHTMODE_DEACTIVATE);
		}
		break;

	case activateRemote:

		if(!remoteOn) {
			remoteOn = TRUE;
			EVNT_SetEvent(EVNT_REMOTE_ACTIVATE);
		}
		else {
			remoteOn = FALSE;
			EVNT_SetEvent(EVNT_REMOTE_DEACTIVATE);
		}

		break;

	case goFastFW:

		EVNT_SetEvent(EVNT_GO_FAST_FW);

		break;

	case toggleRefl:

		EVNT_SetEvent(EVNT_REFL_TOG);

		break;

	case anal_x:
		if (!calibratetX) {
			xcalib = rxdata.data;
			calibratetX = TRUE;
		}
		valX = (ScaleToPercent(rxdata.data, TRUE, TRUE));

		break;
	case anal_y:
		if (!calibratetY) {
			ycalib = rxdata.data;
			calibratetY = TRUE;
		}
		valY = ScaleToPercent(rxdata.data, FALSE, TRUE);

		break;

	case accel_x:
		valX = ScaleToPercent(rxdata.data, FALSE, FALSE)>>1;

		break;

	case accel_y:
		valY = ScaleToPercent(rxdata.data, FALSE, FALSE);

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

int8_t ScaleToPercent(uint8_t val, bool x, bool isAnalog) {

  int8_t temp;
  uint8_t calib, min;

  if(isAnalog) {
		if(x){
			calib = xcalib;
			min = xmin;
		}
		else {
			calib = ycalib;
			min = ymin;
		}
  }
  else {
	  calib = 127;
	  min = 0;
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

uint8_t scaleFromAccelToU8(int16_t val){
	uint8_t temp = 0;
	if(val < 0){
		temp = (127*(val+1000))/1000;
	}
	else if(val > 0) {
		temp = 127+(((255-127)*val)/1000);
	}
	else{
		temp = 127;
	}
	return temp;
}

void remoteInit(void) {
	remoteOn = FALSE;
	FRTOS1_vTaskSuspend(remoteTask);
}


