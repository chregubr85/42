/**
 * \file
 * \brief RTOS interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module the main tasks of the RTOS.
 */

#ifndef RTOS_H_
#define RTOS_H_

#if PL_HAS_RTOS
#include "FRTOS1.h"
#endif
#include "task.h"

extern TaskHandle_t checkRefl;
extern TaskHandle_t remoteTask;
extern TaskHandle_t fightTask;


/*! \brief Runs the scheduler */
void RTOS_Run(void);

/*! \brief Initializes the RTOS module */
void RTOS_Init(void);

/*! \brief De-Initializes the RTOS module */
void RTOS_Deinit(void);


#endif /* RTOS_H_ */
