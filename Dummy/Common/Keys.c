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
#if PL_HAS_EVENTS
  #include "Event.h"
#endif

void KEY_Scan(void) {
  if (KEY5_Get()) { /* key pressed */
    EVNT_SetEvent(EVNT_BTN_E);
  }
  if (KEY6_Get()) { /* key pressed */
    EVNT_SetEvent(EVNT_BTN_F);
  }
}

#if PL_HAS_KBI
void KEY_OnInterrupt(KEY_Buttons button) {
	switch (button) {
		case KEY_BTN1: EVNT_SetEvent(EVNT_BTN_RED);
			break;
		case KEY_BTN2: EVNT_SetEvent(EVNT_BTN_BLUE);
			break;
		case KEY_BTN3: EVNT_SetEvent(EVNT_BTN_YELLOW);
			break;
		case KEY_BTN4: EVNT_SetEvent(EVNT_BTN_GREEN);
			break;
		case KEY_BTN7: EVNT_SetEvent(EVNT_BTN_KEY);
			break;
		default:
			break;
	}
}
#endif

/*! \brief Key driver initialization */
void KEY_Init(void) {
  /* nothing needed for now */
}

/*! \brief Key driver de-initialization */
void KEY_Deinit(void) {
  /* nothing needed for now */
}
#endif /* PL_HAS_KEYS */
