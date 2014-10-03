/*!
** @file init_platform.h
** @version 1.0
** @brief
**         Module for initialize the platform, which is defined in platform.h
**         Before computing the main program do this initialization.
** @author S.Portmann
** @date 03.10.2014
*/


#include "platform.h"
#include "LED.h"
#include "PE_Types.h"

/**
 * This function initializes used hardware and modules.
 * @return 1 - if initialization succeeded.
 */
uint8 init_platform(void);
