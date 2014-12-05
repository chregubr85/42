/*!
** @file Mealy.h
** @version 1.0
** @brief
**
** @author C.Brunner
** @date 09.10.2014
*/
#ifndef MEALY_H_
#define MEALY_H_

#include "Buzzer.h"
#include "Wait1.h"
#include "LED.h"

typedef enum MealyStates{
	StateInit,
	StateOne,
	StateTwo,
	StateThree //Go on
}MealyStates_t;

extern MealyStates_t MyState;


/*! \brief This implements our Mealy Sequential Machine. On each call the FSM will perform a check/test advances as necessary. */
void MEALY_Step(void);

/*! \brief Initialization routine of the state machine */
void MEALY_Init(void);

/*! \brief De-iinitialization routine of the state machine */
void MEALY_Deinit(void);

#endif /* MEALY_H_ */
