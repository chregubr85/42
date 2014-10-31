/**
 * \file
 * \brief Key debouncing implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements debouncing of up to 4 Keys.
 */

#include "platform.h"
#if PL_HAS_DEBOUNCE

#include "Keys.h"
#include "Debounce.h"
#include "Trigger.h"
#include "Event.h"

/*!
 * \brief Returns the state of the keys. This directly reflects the value of the port
 * \return Port bits
 */
static DBNC_KeySet KEYDBNC_GetKeys(void) {
  DBNC_KeySet keys = 0;

#if PL_NOF_KEYS >= 1
  if (KEY1_Get()) {
    keys |= (1<<0);
  }
#endif
#if PL_NOF_KEYS >= 2
  if (KEY2_Get()) {
    keys |= (1<<1);
  }
#endif
#if PL_NOF_KEYS >= 3
  if (KEY3_Get()) {
    keys |= (1<<2);
  }
#endif
#if PL_NOF_KEYS >= 4
  if (KEY4_Get()) {
    keys |= (1<<3);
  }
#endif
#if PL_NOF_KEYS >= 5
  if (KEY5_Get()) {
    keys |= (1<<4);
  }
#endif
#if PL_NOF_KEYS >= 6
  if (KEY6_Get()) {
    keys |= (1<<5);
  }
#endif
#if PL_NOF_KEYS >= 7
  if (KEY7_Get()) {
    keys |= (1<<6);
  }
#endif
  return keys;
}

/*!
 * \brief Event called in the event of a long key press detected.
 * \param keys The keyboard port content
 * \param event The event kind
 */
static void KEYDBNC_OnDebounceEvent(DBNC_EventKinds event, DBNC_KeySet keys) {
  switch(event) {
    /* pressed */
    case DBNC_EVENT_PRESSED:
#if PL_NOF_KEYS >= 1
      if (keys==(1<<0)) {
        EVNT_SetEvent(EVNT_BTN_RED_PRESSED);
      }
#endif
#if PL_NOF_KEYS >= 2
      if (keys==(1<<1)) {
        EVNT_SetEvent(EVNT_BTN_BLUE_PRESSED);
      }
#endif
#if PL_NOF_KEYS >= 3
      if (keys==(1<<2)) {
        EVNT_SetEvent(EVNT_BTN_YELLOW_PRESSED);
      }
#endif
#if PL_NOF_KEYS >= 4
      if (keys==(1<<3)) {
        EVNT_SetEvent(EVNT_BTN_GREEN_PRESSED);
      }
#endif
#if PL_NOF_KEYS >= 5
      if (keys==(1<<4)) {
        EVNT_SetEvent(EVNT_BTN_E_PRESSED);
      }
#endif
#if PL_NOF_KEYS >= 6
      if (keys==(1<<5)) {
        EVNT_SetEvent(EVNT_BTN_F_PRESSED);
      }
#endif
#if PL_NOF_KEYS >= 7
      if (keys==(1<<6)) {
        EVNT_SetEvent(EVNT_BTN_KEY_PRESSED);
      }
#endif
      break;

    /* long pressed */
    case DBNC_EVENT_LONG_PRESSED:
#if PL_NOF_KEYS >= 1
      if (keys==(1<<0)) {
        EVNT_SetEvent(EVNT_BTN_GREEN_LPRESSED);
      }
#endif
#if PL_NOF_KEYS >= 2
      if (keys==(1<<1)) {
        EVNT_SetEvent(EVNT_BTN_RED_LPRESSED);
      }
#endif
#if PL_NOF_KEYS >= 3
     if (keys==(1<<2)) {
        EVNT_SetEvent(EVNT_BTN_YELLOW_LPRESSED);
      }
#endif
#if PL_NOF_KEYS >= 4
     if (keys==(1<<3)) {
        EVNT_SetEvent(EVNT_BTN_BLUE_LPRESSED);
      }
#endif
#if PL_NOF_KEYS >= 5
     if (keys==(1<<4)) {
        EVNT_SetEvent(EVNT_BTN_E_LPRESSED);
      }
#endif
#if PL_NOF_KEYS >= 6
     if (keys==(1<<5)) {
        EVNT_SetEvent(EVNT_BTN_F_LPRESSED);
      }
#endif
#if PL_NOF_KEYS >= 7
     if (keys==(1<<6)) {
        EVNT_SetEvent(EVNT_BTN_KEY_LPRESSED);
      }
#endif
     break;

     /* released */
    case DBNC_EVENT_RELEASED:
#if PL_NOF_KEYS >= 1
      if (keys==(1<<0)) {
        EVNT_SetEvent(EVNT_BTN_GREEN_RELEASED);
      }
#endif
#if PL_NOF_KEYS >= 2
      if (keys==(1<<1)) {
        EVNT_SetEvent(EVNT_BTN_RED_RELEASED);
      }
#endif
#if PL_NOF_KEYS >= 3
      if (keys==(1<<2)) {
        EVNT_SetEvent(EVNT_BTN_YELLOW_RELEASED);
      }
#endif
#if PL_NOF_KEYS >= 4
      if (keys==(1<<3)) {
        EVNT_SetEvent(EVNT_BTN_BLUE_RELEASED);
      }
#endif
#if PL_NOF_KEYS >= 5
      if (keys==(1<<4)) {
        EVNT_SetEvent(EVNT_BTN_E_RELEASED);
      }
#endif
#if PL_NOF_KEYS >= 6
      if (keys==(1<<5)) {
        EVNT_SetEvent(EVNT_BTN_F_RELEASED);
      }
#endif
#if PL_NOF_KEYS >= 7
      if (keys==(1<<6)) {
        EVNT_SetEvent(EVNT_BTN_KEY_RELEASED);
      }
#endif
      break;
    case DBNC_EVENT_END:
      /*! \todo Implement what you have to do at the end of the debouncing */
#if PL_HAS_KBI
      KEY_EnableInterrupts();
#endif
      break;
  } /* switch */
}

/*! \brief This struct contains all the data and pointers needed to have
 *         our debounce FSM reentrant and usable for multiple ISR's.
 */
static DBNC_FSMData KEYDBNC_FSMdata = {
  /* callbacks: */
  KEYDBNC_GetKeys, /* returns bit set of pressed keys */
  KEYDBNC_OnDebounceEvent, /* event callback */
  /* data: */
  DBNC_KEY_IDLE, /* initial state machine state, here the state is stored */
  0, /* key scan value */
  0, /* long key count */
  TRG_KEYPRESS, /* trigger to be used */
  (20/TRG_TICKS_MS), /* debounceTicks for 20 ms */
  (500/TRG_TICKS_MS), /* longKeyTicks for 500 ms */
};

void KEYDBNC_Process(void) {
  /** \todo call DBNC_Process(&KEY_FSMdata);
   * But be careful: only if we are not debouncing, and if we have a key press if we are polling
   */
  if (KEYDBNC_FSMdata.state==DBNC_KEY_IDLE && KEYDBNC_GetKeys()!=0) { /* a key is pressed and we are not debouncing */
  #if PL_HAS_KBI
    KEY_DisableInterrupts(); /* disable interrupts for all keys */
  #endif
    DBNC_Process(&KEYDBNC_FSMdata); /* starts the state machine */
  }
}

void KEYDBNC_Init(void) {
  /* nothing needed */
}

void KEYDBNC_Deinit(void) {
  /* nothing needed */
}

#endif /* PL_HAS_KEYS && PL_HAS_DEBOUNCE */

