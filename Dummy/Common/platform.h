/**
 * This is the platform configuration file.
 * @author: Stefan Portmann
 * @date: 25.09.2014
 * @version: 0.1
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h"
#include "PE_Error.h"
#include "stddef.h"


#define PL_IS_FRDM (defined(PL_BOARD_IS_FRDM))
#define PL_IS_ROBO (defined(PL_BOARD_IS_ROBO))


#if  PL_IS_FRDM
	#define PL_NOF_LEDS 3		// FRDM board has 3 LEDs(RGB)
	#define PL_HAS_KEYS 1
	#define PL_HAS_KBI 1
 	#define PL_HAS_JOYSTICK 1
	#define PL_HAS_EVENTS 1		// FRDM Board supports Events
	#define PL_HAS_TIMER 1
	#define PL_HAS_TRIGGER 1
	#define PL_HAS_BUZZER 0
	#define PL_NOF_KEYS 7
	#define PL_NOF_KBI 4
	#define PL_HAS_MEALY 1
	#define PL_HAS_DEBOUNCE 1
	#define PL_HAS_SHELL 1
	#define PL_HAS_RTOS 1
	#define PL_HAS_BLUETOOTH 0
	#define PL_HAS_USB_CDC 1
	#define PL_HAS_SHELL_QUEUE 1
	#define PL_HAS_ACCEL 1
	#define PL_HAS_RADIO 1
	#define PL_HAS_SEMAPHORE 0
	#define PL_HAS_REMOTE 1
	#define PL_HAS_ANALOG_JOY 1

#if !PL_HAS_KEYS
  	  #define LedRED_On() 		LED1_On()
  	  #define LedRED_Off() 		LED1_Off()
  	  #define LedRED_Neg()		LED1_Neg()
  	  #define LedRED_Get() 		LED1_Get()
  	  #define LedRED_Put(val) 	LED1_Put(val)
  	  #define LedRED_Init() 	LED1_Init()
  	  #define LedRED_Deinit() 	LED1_Deinit()
#endif

  	  #define LedGREEN_On() 	LED2_On()
  	  #define LedGREEN_Off() 	LED2_Off()
  	  #define LedGREEN_Neg()	LED2_Neg()
  	  #define LedGREEN_Get() 	LED2_Get()
  	  #define LedGREEN_Put(val) LED2_Put(val)
  	  #define LedGREEN_Init() 	LED2_Init()
  	  #define LedGREEN_Deinit() LED2_Deinit()

#if !PL_HAS_RADIO
  	  #define LedBLUE_On() 		LED3_On()
  	  #define LedBLUE_Off() 	LED3_Off()
  	  #define LedBLUE_Neg()		LED3_Neg()
  	  #define LedBLUE_Get() 	LED3_Get()
  	  #define LedBLUE_Put(val) 	LED3_Put(val)
  	  #define LedBLUE_Init() 	LED3_Init()
  	  #define LedBLUE_Deinit() 	LED3_Deinit()

	  #define LedYELLOW_On()		led12On()
	  #define LedVIOLET_On()		led13On()
	  #define LedTORQUOISE_On()		led23On()
	  #define LedWHITE_On()			led123On()
	  #define LedYELLOW_Off()		led12Off()
	  #define LedVIOLET_Off()		led13Off()
	  #define LedTORQUOISE_Off()	led23Off()
	  #define LedWHITE_Off()		led123Off()
#endif
	#if PL_IS_FRDM
		#define PL_KEY_POLLED_KEY1    (0)
  	  	#define PL_KEY_POLLED_KEY2    (0)
		#define PL_KEY_POLLED_KEY3    (0)
		#define PL_KEY_POLLED_KEY4    (0)
		#define PL_KEY_POLLED_KEY5    (1)
		#define PL_KEY_POLLED_KEY6    (1)
		#define PL_KEY_POLLED_KEY7    (0)

	#elif PL_IS_ROBO
  	  	#define PL_KEY_POLLED_KEY1    (0)
	#endif


#elif PL_IS_ROBO
	#define PL_NOF_LEDS 2

	#define PL_NOF_LEDS 2		// ROBO board has 2 LEDs(RGB)
	#define PL_HAS_KEYS 1
	#define PL_HAS_KBI 1
 	#define PL_HAS_JOYSTICK 0
	#define PL_HAS_EVENTS 1		// ROBO supports Events
	#define PL_HAS_TIMER 1
	#define PL_HAS_TRIGGER 1
	#define PL_HAS_BUZZER 1
	#define PL_NOF_KEYS 1
	#define PL_NOF_KBI 1
	#define PL_HAS_SHELL 1
	#define  PL_HAS_MEALY 1
	#define PL_HAS_RTOS 1
	#define PL_HAS_USB_CDC 1
	#define PL_HAS_BLUETOOTH 1
	#define PL_HAS_SHELL_QUEUE 1
	#define PL_HAS_SEMAPHORE 1
	#define PL_HAS_LINE_SENSOR 1
	#define PL_HAS_DEBOUNCE 1
	#define PL_HAS_MOTOR 1
	#define PL_HAS_QUAD_CALIBRATION 1
	#define PL_HAS_MPC4728 1
	#define PL_IS_CALIBRATED 1
	#define PL_HAS_CONFIG_NVM 1
	#define PL_HAS_MOTOR_QUAD 1
	#define PL_HAS_MOTOR_TACHO 1
	#define PL_HAS_DRIVE 1
	#define PL_HAS_PID 1
	#define PL_HAS_ULTRASONIC 1
	#define PL_HAS_ACCEL 0
	#define PL_HAS_RADIO 1
	#define PL_HAS_REMOTE 1
	#define PL_HAS_FIGHT 1
	#define REMOTE_WITHOUT_REFLECTANCE 1

#else
	#error "unknown board?"
#endif

void PL_Init(void);

#endif	/*PLATFORM_H_*/
