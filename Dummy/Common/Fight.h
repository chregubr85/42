#ifndef __FIGHT_H_
#define __FIGHT_H_


#include "platform.h"
#include "Application.h"
#include "Motor.h"

#define FightOn		vTaskResume("Fight")
#define FightOff	vTaskSuspend("Fight")







void FIGHT_Init(void);
void Fightmodus(void);


#endif /*__FIGHT_H_*/
