/**
 * \file
 * \brief Key/switch driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic keyboard driver for up to 4 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#ifndef KEYS_H_
#define KEYS_H_

#include "Platform.h"
#include "CLS1.h"
#include "util1.h"

#if PL_HAS_KEYS

typedef enum {
  KEY_BTN1, /*!< button 1 */
#if PL_IS_FRDM
  KEY_BTN2, /*!< button 2 */
  KEY_BTN3, /*!< button 3 */
  KEY_BTN4, /*!< button 4 */
  KEY_BTN5, /*!< button 5 */
  KEY_BTN6, /*!< button 6 */
  KEY_BTN7  /*!< button 7 */
#endif

} KEY_Buttons;

extern uint16_t xcalib, ycalib;

#if PL_NOF_KEYS>=1
  #include "SW1.h"

  #define KEY1_Get()  (!(SW1_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY1_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=2
  #include "SW2.h"

  #define KEY2_Get()  (!(SW2_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY2_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=3
  #include "SW3.h"

  #define KEY3_Get()  (!(SW3_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY3_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=4
  #include "SW4.h"

  #define KEY4_Get()  (!(SW4_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY4_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=5
  #include "SW5.h"

  #define KEY5_Get()  (!(SW5_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY5_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=6
  #include "SW6.h"

  #define KEY6_Get()  (!(SW6_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY6_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=7
  #include "SW7.h"

  #define KEY7_Get()  (!(SW7_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY7_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_HAS_KBI
/*!
 * \brief Function called from a keyboard interrupt (if supported).
 * \param button Button for which interrupt has been generated.
 */
void KEY_OnInterrupt(KEY_Buttons button);
#endif

#define xmin 0
#define ymin 0

#if PL_HAS_ANALOG_JOY
	#include "AD1.h"

    int8_t ToSigned8Bit(uint16_t val);

	void GetXY(uint8_t *x, uint8_t *y);

	void CalibXY(void);

	static uint8_t PrintXY(CLS1_ConstStdIOType *io);

	static uint8_t Key_PrintHelp(const CLS1_StdIOType *io);

	uint8_t ScaleToU8(uint16_t val, bool x);

	uint8_t KEY_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*!
 * \brief Checks the key status and generates the events.
 */
void KEY_Scan(void);

/*! \brief Get access to key hardware. Use KEY_Close() afterwards. */
void KEY_Open(void);

void KEY_EnableInterrupts(void);

void KEY_DisableInterrupts(void);

/*! \brief Finish access to key hardware. Called after KEY_Open(). */
void KEY_Close(void);

/*! \brief Key driver initialization */
void KEY_Init(void);

/*! \brief Key driver de-initialization */
void KEY_Deinit(void);

#endif /* PL_HAS_KEYS */

#endif /* KEYS_H_ */
