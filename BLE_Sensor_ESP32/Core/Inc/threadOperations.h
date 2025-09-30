//****************************** Thread Operations *****************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
//
// Summary : Contain all global constant and forward declaration
//			 required for threadOperations.c functions
// Note    : None
//
//******************************************************************************
#ifndef THREAD_OPERATIONS_H
#define THREAD_OPERATIONS_H

//******************************* Include Files ********************************
#include "gpioFunctions.h"

//******************************* Global Types *********************************

//***************************** Global Constants *******************************
#define TIMER_DELAY             (2000)

//***************************** Global Variables *******************************

//**************************** Forward Declarations ****************************
bool threadCreate(osThreadFunc_t pTaskName, uint32 *pParameter,
		const osThreadAttr_t *pthreadAttributes, osThreadId_t *pThreadHandle);
bool timerCreate(osTimerFunc_t pCallback,
				 const osTimerAttr_t *pTimerAttributes,
				 osThreadId_t *pTimerHandle);
bool semaphoreCreate(const osSemaphoreAttr_t *pSemaphoreAttributes,
						   osSemaphoreId_t *pSemaphoreHandle);
bool timerStart(osTimerId_t *pTimerHandle);
bool semaphoreWait(osSemaphoreId_t *pSemHandle);
bool semaphorePost(osSemaphoreId_t *pSemHandle);

//*********************** Inline Method Implementations ************************

#endif // THREAD_OPERATIONS_H
// EOF
