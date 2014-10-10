/*!
** @file hard_fault.h
** @version 1.0
** @brief
**       Implements two Methods who generate a hard fault
** @author C.Brunner
** @date 09.10.2014
*/


#ifndef HARD_FAULT_H_
#define HARD_FAULT_H_

/**
 * NULL-Pointer
 */
void (*f)(void);

/**
 * Method to cause a hard fault
 */
void cause_hard_fault(void);



#endif /* HARD_FAULT_H_ */
