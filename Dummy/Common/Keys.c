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



/*! \brief Key driver initialization */
void KEY_Init(void) {
  /* nothing needed for now */
}

/*! \brief Key driver de-initialization */
void KEY_Deinit(void) {
  /* nothing needed for now */
}
