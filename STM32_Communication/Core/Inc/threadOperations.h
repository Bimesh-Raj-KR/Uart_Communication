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
#include "common.h"

//******************************* Global Types *********************************

//***************************** Global Constants *******************************
#define TIMER_DELAY             (500)

//***************************** Global Variables *******************************

//**************************** Forward Declarations ****************************
osThreadId_t threadCreate(osThreadFunc_t pTaskName, uint32 *pulSum,
		const osThreadAttr_t *pthreadAttributes);
osTimerId_t timerCreate(osTimerFunc_t pCallback,
						const osTimerAttr_t *pTimerAttributes);
osMutexId_t mutexCreate(const osMutexAttr_t *pMutexAttribute);
osSemaphoreId_t semCreate(const osSemaphoreAttr_t *pSemAttributes);
osMessageQueueId_t queueCreate(const osMessageQueueAttr_t *pQueueAttributes);
osEventFlagsId_t eventCreate(void);
bool eventWait(osEventFlagsId_t *pWaitEvent, uint32 *pulTriggerFlag);
bool eventSet(osEventFlagsId_t *pWaitEvent, uint32 pulEventFlag);
bool timerStart(osTimerId_t *pTimerHandle);
bool mutexLock(osMutexId_t *pMutexHandle);
bool mutexUnlock(osMutexId_t *pMutexHandle);
bool semaphoreWait(osSemaphoreId_t *pSemHandle);
bool semaphorePost(osSemaphoreId_t *pSemHandle);
bool messageSend(osSemaphoreId_t *pQueueHandle, void* stMessage);
bool messageReceive(osSemaphoreId_t *pQueueHandle, void* stMessage);
void taskDelay(uint32 ulDelay);

//*********************** Inline Method Implementations ************************

#endif // THREAD_OPERATIONS_H
// EOF
