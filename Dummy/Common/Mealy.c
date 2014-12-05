/*!
** @file Mealy.c
** @version 1.0
** @brief
**
** @author C.Brunner
** @date 09.10.2014
*/

#include "Platform.h"


#if PL_HAS_MEALY
	#include "Mealy.h"

MealyStates_t MyState;


void MEALY_Step(void){
	switch (MyState) {
	case StateInit:
		BUZ_Beep(200,500);
		WAIT1_Waitms(500);
		MyState = StateOne;
		break;
	case StateOne:
		BUZ_Beep(200,500);
		WAIT1_Waitms(500);
		BUZ_Beep(300,500);
		WAIT1_Waitms(500);
		MyState = StateTwo;
		break;
	case StateTwo:
		BUZ_Beep(100,500);
		WAIT1_Waitms(500);
		BUZ_Beep(200,500);
		WAIT1_Waitms(500);
		BUZ_Beep(300,500);
		WAIT1_Waitms(500);
		MyState = StateThree;
		break;
	case StateThree:
		for(int i = 0; i<20; i++){
#if PL_IS_FRDM
			LED2_Neg();
#elif PL_IS_ROBO
			LED1_Neg();
#endif
			WAIT1_Waitms(100);
		}
		MyState = StateInit;
		break;
	default:
		MyState = StateInit;
	}
}


void MEALY_Init(void){
	MyState = StateInit;
}


void MEALY_Deinit(void){
}


#endif
