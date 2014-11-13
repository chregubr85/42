/*!
** @file Event.h
** @version 1.0
** @brief	Module for an Event Array.
**
**
** @author S.Portmann
** @date 09.10.2014
*/

#ifndef EVENT_H_
#define EVENT_H_

#include "platform.h"

#if PL_HAS_EVENTS

typedef enum EVNT_Handle {
  EVNT_INIT,            /*!< System Initialization Event */
#if PL_NOF_KEYS >= 1
	#if PL_IS_FRDM & PL_HAS_JOYSTICK
	  // Button Red
	  EVNT_BTN_RED_PRESSED,
	  EVNT_BTN_RED_LPRESSED,
	  EVNT_BTN_RED_RELEASED,
	#elif PL_IS_ROBO
	  EVNT_BTN,
	  EVNT_BTN_LPRESSED,
	  EVNT_BTN_RELEASED,
	#endif
#endif

#if PL_NOF_KEYS >= 2
	#if PL_IS_FRDM & PL_HAS_JOYSTICK
	  // Button Blue
	  EVNT_BTN_BLUE_PRESSED,
	  EVNT_BTN_BLUE_LPRESSED,
	  EVNT_BTN_BLUE_RELEASED,
	#endif
#endif

#if PL_NOF_KEYS >= 3
	#if PL_IS_FRDM & PL_HAS_JOYSTICK
	  // Button Yellow
	  EVNT_BTN_YELLOW_PRESSED,
	  EVNT_BTN_YELLOW_LPRESSED,
	  EVNT_BTN_YELLOW_RELEASED,
	#endif
#endif

#if PL_NOF_KEYS >= 4
	#if PL_IS_FRDM & PL_HAS_JOYSTICK
	  // Button Green
	  EVNT_BTN_GREEN_PRESSED,
	  EVNT_BTN_GREEN_LPRESSED,
	  EVNT_BTN_GREEN_RELEASED,
	#endif
#endif

#if PL_NOF_KEYS >= 5
	#if PL_IS_FRDM & PL_HAS_JOYSTICK
	  // Button E
	  EVNT_BTN_E_PRESSED,
	  EVNT_BTN_E_LPRESSED,
	  EVNT_BTN_E_RELEASED,
	#endif
#endif

#if PL_NOF_KEYS >= 6
	#if PL_IS_FRDM & PL_HAS_JOYSTICK
	  // Button F
	  EVNT_BTN_F_PRESSED,
	  EVNT_BTN_F_LPRESSED,
	  EVNT_BTN_F_RELEASED,
	#endif
#endif

#if PL_NOF_KEYS >= 7
	#if PL_IS_FRDM & PL_HAS_JOYSTICK
	  // Button Key
	  EVNT_BTN_KEY_PRESSED,
	  EVNT_BTN_KEY_LPRESSED,
	  EVNT_BTN_KEY_RELEASED,
	#endif
#endif

#if PL_HAS_LINE_SENSOR
	  EVNT_REF_START_STOP_CALIBRATION,
#endif

#if PL_HAS_MOTOR
	  EVNT_DONT_FALL_DOWN,
#endif

  EVNT_LED_HEARTBEAT,
  EVNT_NOF_EVENTS      /*!< Must be last one! */
} EVNT_Handle;

/*!
 * \brief Sets an event.
 * \param[in] event The handle of the event to set.
 */
void EVNT_SetEvent(EVNT_Handle event);

/*!
 * \brief Clears an event.
 * \param[in] event The event handle of the event to clear.
 */
void EVNT_ClearEvent(EVNT_Handle event);

/*!
 * \brief Returns the status of an event.
 * \param[in] event The event handler of the event to check.
 * \return TRUE if the event is set, FALSE otherwise.
 */
bool EVNT_EventIsSet(EVNT_Handle event);

/*!
 * \brief Returns the status of an event. As a side effect, the event gets cleared.
 * \param[in] event The event handler of the event to check.
 * \return TRUE if the event is set, FALSE otherwise.
 */
bool EVNT_EventIsSetAutoClear(EVNT_Handle event);

/*!
 * \brief Routine to check if an event is pending. If an event is pending, the event is cleared and the provided callback is called.
 * \param[in] callback Callback routine to be called. The event handle is passed as argument to the callback.
 */
void EVNT_HandleEvent(void (*callback)(EVNT_Handle));

/*! \brief Event module initialization */
void EVNT_Init(void);

/*! \brief Event module de-initialization */
void EVNT_Deinit(void);

#endif /* PL_HAS_EVENTS */


#endif /* EVENT_H_ */
