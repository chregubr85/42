/*!
** @file init_platform.c
** @version 1.0
** @brief
**         Module for initialize the platform, which is defined in platform.h
**         Before computing the main program do this initialization.
** @author S.Portmann
** @date 03.10.2014
*/


#include "init_platform.h"


uint8 init_platform(void){
	initLED(); //initialize LED

	return 1;
}
