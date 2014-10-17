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
#if PL_IS_FRDM & PL_HAS_JOYSTICK
  EVNT_BTN_GREEN,
  EVNT_BTN_RED,
  EVNT_BTN_BLUE,
  EVNT_BTN_YELLOW,
  EVNT_BTN_E,
  EVNT_BTN_F,
  EVNT_BTN_KEY,
#endif
  EVNT_LED_HEARTBEAT,
  EVNT_BTN,
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
