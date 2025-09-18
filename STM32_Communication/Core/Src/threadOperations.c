//********************************* Thread Operations **************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : threadOperations.c
// Summary : Wrapper for different thread operations
// Note    : None
// Author  : Bimesh Raj K R
// Date    : 10/Sep/2025
//******************************************************************************

//****************************** Include Files *********************************
#include "threadOperations.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//***************************** Local Functions ********************************

//********************************.threadCreate.********************************
// Purpose : Function to Create a thread
// Inputs  : pTaskName - Name of the thread to be created
//			 pParameter -  Function parameter of the thread
//			 pthreadAttributes - Attributes of thread
// Outputs : None
// Return  : pThreadHandle - thread handle
// Notes   : None
//******************************************************************************
osThreadId_t threadCreate(osThreadFunc_t pTaskName, uint32 *pParameter,
		const osThreadAttr_t *pthreadAttributes)
{
	osThreadId_t pThreadHandle = 0;

	if (NULL != pthreadAttributes)
	{
		pThreadHandle = osThreadNew(pTaskName, (void*)pParameter,
				pthreadAttributes);
	}
	else
	{
		perror("Unable to create task");
	}

	return pThreadHandle;
}

//********************************.timerCreate.*********************************
// Purpose : Function to Create a timer
// Inputs  : pCallback - Callback function that signifies timer timeout
//			 pTimerAttributes -  Attributes of the timer
// Outputs : None
// Return  : pTimerHandle - timer handle
// Notes   : None
//******************************************************************************
osTimerId_t timerCreate(osTimerFunc_t pCallback,
						const osTimerAttr_t *pTimerAttributes)
{
	osThreadId_t pTimerHandle = 0;

	if (NULL != pTimerAttributes)
	{
		pTimerHandle = osTimerNew(pCallback, osTimerPeriodic,
								  NULL, pTimerAttributes);
	}
	else
	{
		perror("Unable to create timer");
	}

	return pTimerHandle;
}

//********************************.mutexCreate.*********************************
// Purpose : Function to Create a mutex
// Inputs  : pMutexAttribute - Attribute of the mutex
// Outputs : None
// Return  : pMutexHandle - mutex handle
// Notes   : None
//******************************************************************************
osMutexId_t mutexCreate(const osMutexAttr_t *pMutexAttribute)
{
	osMutexId_t pMutexHandle = 0;

	if (NULL != pMutexAttribute)
	{
		pMutexHandle = osMutexNew(pMutexAttribute);
	}
	else
	{
		perror("Unable to create Mutex");
	}

	return pMutexHandle;
}

//***********************************.semCreate.*********************************
// Purpose : Function to Create a semaphore
// Inputs  : pSemAttributes - Attribute of the semaphore
// Outputs : None
// Return  : pSemHandle - semaphore handle
// Notes   : None
//******************************************************************************
osSemaphoreId_t semCreate(const osSemaphoreAttr_t *pSemAttributes)
{
	osSemaphoreId_t pSemHandle = 0;

	if (NULL != pSemAttributes)
	{
		pSemHandle = osSemaphoreNew(1, 0, pSemAttributes);
	}
	else
	{
		perror("Unable to create Semaphore");
	}

	return pSemHandle;
}

//********************************.timerStart.**********************************
// Purpose : Function to start a timer
// Inputs  : pTimerHandle - Timer Handle
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool timerStart(osTimerId_t *pTimerHandle)
{
	bool blCheck = false;

	if (NULL != pTimerHandle)
	{
		osTimerStart(*pTimerHandle, TIMER_DELAY);
		blCheck = true;
	}
	else
	{
		perror("Failed to start Timer");
	}

	return blCheck;
}
//********************************.mutexLock.***********************************
// Purpose : Function to lock a mutex
// Inputs  : pMutexHandle - Mutex Handle
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool mutexLock(osMutexId_t *pMutexHandle)
{
	bool blCheck = false;

	if (NULL != pMutexHandle)
	{
		osMutexAcquire(*pMutexHandle, osWaitForever);
		blCheck = true;
	}
	else
	{
		perror("Mutex acquiring failed");
	}

	return blCheck;
}

//********************************.mutexUnlock.*********************************
// Purpose : Function to unlock a mutex
// Inputs  : pMutexHandle - Mutex Handle
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool mutexUnlock(osMutexId_t *pMutexHandle)
{
	bool blCheck = false;

	if (NULL != pMutexHandle)
	{
		osMutexRelease(*pMutexHandle);
		blCheck = true;
	}
	else
	{
		perror("Mutex releasing failed");
	}

	return blCheck;
}

//******************************.semaphoreWait.*********************************
// Purpose : Function to acquire a semaphore
// Inputs  : pSemHandle - Semaphore Handle
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool semaphoreWait(osSemaphoreId_t *pSemHandle)
{
	bool blCheck = false;

	if (NULL != pSemHandle)
	{
		osSemaphoreAcquire(*pSemHandle, osWaitForever);
		blCheck = true;
	}
	else
	{
		perror("Semaphore acquiring failed");
	}

	return blCheck;
}

//******************************.semaphorePost.*********************************
// Purpose : Function to release a semaphore
// Inputs  : pSemHandle - Semaphore Handle
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool semaphorePost(osSemaphoreId_t *pSemHandle)
{
	bool blCheck = false;

	if (NULL != pSemHandle)
	{
		osSemaphoreRelease(*pSemHandle);
		blCheck = true;
	}
	else
	{
		perror("Semaphore releasing failed");
	}

	return blCheck;
}

//********************************.taskDelay.***********************************
// Purpose : Function to run a delay
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void taskDelay(uint32 ulDelay)
{
	osDelay(ulDelay);
}

//EOF
