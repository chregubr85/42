/**
 * \file
 * \brief Key/Switch driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic keyboard driver for up to 7 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#include "Platform.h"
#if PL_HAS_KEYS
  #include "Keys.h"
#endif
#if PL_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_HAS_DEBOUNCE
  #include "KeyDebounce.h"
#endif


void KEY_Scan(void) {
#if PL_HAS_JOYSTICK
#if PL_HAS_DEBOUNCE
	KEYDBNC_Process();
#else
  if (KEY5_Get()) { /* key pressed */
    EVNT_SetEvent(EVNT_BTN_E_PRESSED);
  }
  if (KEY6_Get()) { /* key pressed */
    EVNT_SetEvent(EVNT_BTN_F_PRESSED);
  }
#endif
#endif
}

void KEY_OnInterrupt(KEY_Buttons button) {
#if PL_HAS_DEBOUNCE
	KEYDBNC_Process();
#else
	switch (button) {
#if PL_IS_FRDM & PL_HAS_KBI
		case KEY_BTN1: EVNT_SetEvent(EVNT_BTN_RED_PRESSED);
			break;
		case KEY_BTN2: EVNT_SetEvent(EVNT_BTN_BLUE_PRESSED);
			break;
		case KEY_BTN3: EVNT_SetEvent(EVNT_BTN_YELLOW_PRESSED);
			break;
		case KEY_BTN4: EVNT_SetEvent(EVNT_BTN_GREEN_PRESSED);
			break;
		case KEY_BTN7: EVNT_SetEvent(EVNT_BTN_KEY_PRESSED);
			break;
	#elif PL_IS_ROBO
		case KEY_BTN1: EVNT_SetEvent(EVNT_BTN);
		break;
		default:
			break;
	#endif
	}
#endif
}

void KEY_EnableInterrupts(void) {
#if PL_NOF_KEYS >= 1 && !PL_KEY_POLLED_KEY1
  SW1_Enable();
#endif
#if PL_NOF_KEYS >= 2 && !PL_KEY_POLLED_KEY2
  SW2_Enable();
#endif
#if PL_NOF_KEYS >= 3 && !PL_KEY_POLLED_KEY3
  SW3_Enable();
  PORT_PDD_ClearPinInterruptFlag(PORTA_BASE_PTR, ExtIntLdd4_PIN_INDEX);
  PORT_PDD_SetPinInterruptConfiguration(PORTA_BASE_PTR, 4, PORT_PDD_DMA_ON_FALLING);
#endif
#if PL_NOF_KEYS >= 4 && !PL_KEY_POLLED_KEY4
  SW4_Enable();
#endif
#if PL_NOF_KEYS >= 5 && !PL_KEY_POLLED_KEY5
  SW5_Enable();
#endif
#if PL_NOF_KEYS >= 6 && !PL_KEY_POLLED_KEY6
  SW6_Enable();
#endif
#if PL_NOF_KEYS >= 7 && !PL_KEY_POLLED_KEY7
  SW7_Enable();
#endif
}

void KEY_DisableInterrupts(void) {
#if PL_NOF_KEYS >= 1 && !PL_KEY_POLLED_KEY1
  SW1_Disable();
#endif
#if PL_NOF_KEYS >= 2 && !PL_KEY_POLLED_KEY2
  SW2_Disable();
#endif
#if PL_NOF_KEYS >= 3 && !PL_KEY_POLLED_KEY3
  SW3_Disable();
  PORT_PDD_SetPinInterruptConfiguration(PORTA_BASE_PTR, 4, PORT_PDD_INTERRUPT_DMA_DISABLED);
#endif
#if PL_NOF_KEYS >= 4 && !PL_KEY_POLLED_KEY4
  SW4_Disable();
#endif
#if PL_NOF_KEYS >= 5 && !PL_KEY_POLLED_KEY5
  SW5_Disable();
#endif
#if PL_NOF_KEYS >= 6 && !PL_KEY_POLLED_KEY6
  SW6_Disable();
#endif
#if PL_NOF_KEYS >= 7 && !PL_KEY_POLLED_KEY7
  SW7_Disable();
#endif
}



#if PL_HAS_ANALOG_JOY

	int8_t ScaleToPercent(uint16_t val, bool x) {
	  int temp;
	  uint16_t calib, min;

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
			  temp = (100*(val-calib))/(0xffff-calib);
		  }
		  else {
			  temp = 0;
		  }
	return (int8_t) temp;

	}

	void CalibXY(void){
			uint16_t vals[2];
		int8_t x,y;

			AD1_Measure(TRUE);
			AD1_GetValue16(&vals[0]);
			xcalib=(vals[0]);
			ycalib=(vals[1]);
		}

	static int8_t ToSigned8Bit(uint16_t val) {
	  int tmp;

	  tmp = ((int)((val>>8)&0xFF))-127;
	  if (tmp<-128) {
		tmp = -128;
	  } else if (tmp>127) {
		tmp = 127;
	  }
	  return (int8_t)tmp;
	}

	void GetXY(int8_t *x, int8_t *y) {
		uint16_t vals[2];

		AD1_Measure(TRUE);
		AD1_GetValue16(&vals[0]);

		/**x = ScaleToPercent(vals[0], TRUE);
		*y = ScaleToPercent(vals[1], FALSE);*/
		*x = ToSigned8Bit(vals[0]);
		*y = ToSigned8Bit(vals[1]);

	}

	uint8_t KEY_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io)
	{
		if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"Key help")==0) {
		   *handled = TRUE;
		   return Key_PrintHelp(io);
		} else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "Key status")==0) {
			*handled = TRUE;
			return  PrintXY(io);
	  }
	}

	 static uint8_t PrintXY(CLS1_ConstStdIOType *io) {

		  int8_t x, y;
		  unsigned char buf[64];

		  GetXY(&x, &y);

			UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"X: (");
			UTIL1_strcatNum8s(buf, sizeof(buf), x);
			UTIL1_strcat(buf, sizeof(buf), (unsigned char*)") Calibration X: (");
			UTIL1_strcatNum8s(buf, sizeof(buf), xcalib);
			UTIL1_strcat(buf, sizeof(buf), (unsigned char*)")\r\n");

			UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"Y: (");
			UTIL1_strcatNum8s(buf, sizeof(buf), y);
			UTIL1_strcat(buf, sizeof(buf), (unsigned char*)") Calibration Y: (");
			UTIL1_strcatNum8s(buf, sizeof(buf), ycalib);
			UTIL1_strcat(buf, sizeof(buf), (unsigned char*)")\r\n\r\n");

			CLS1_SendStr(buf, io->stdOut);
			return ERR_OK;
	  }

	 static uint8_t Key_PrintHelp(const CLS1_StdIOType *io) {
	   CLS1_SendHelpStr((unsigned char*)"Key", (unsigned char*)"Group of Key commands\r\n", io->stdOut);
	   CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows Key help or status\r\n", io->stdOut);
	   return ERR_OK;
	 }

#endif
/*! \brief Key driver initialization */
void KEY_Init(void) {

}

/*! \brief Key driver de-initialization */
void KEY_Deinit(void) {
  /* nothing needed for now */
}
