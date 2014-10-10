/*!
** @file hard_fault.c
** @version 1.0
** @brief
**         Implements two Methods who generate a hard fault
** @author C.Brunner
** @date 09.10.2014
*/


#include"hard_fault.h"



void (*f)(void);

void cause_hard_fault(void) {
  f(); /* will cause a hard fault, as the function pointer is NULL */
}
