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
//			 pThreadAttributes - Attributes of thread
//			 pThreadHandle - Thread Handle
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool threadCreate(osThreadFunc_t pTaskName, uint32 *pParameter,
		const osThreadAttr_t *pThreadAttributes, osThreadId_t *pThreadHandle)
{
	bool blCheck = false;

	if (NULL != pThreadAttributes && NULL != pThreadHandle)
	{
		*pThreadHandle = osThreadNew(pTaskName, (void*)pParameter,
				pThreadAttributes);
		blCheck = true;
	}
	else
	{
		perror("Unable to create task");
	}

	return blCheck;
}

//********************************.timerCreate.*********************************
// Purpose : Function to Create a timer
// Inputs  : pCallback - Callback function that signifies timer timeout
//			 pTimerAttributes -  Attributes of the timer
//			 pTimerHandle - Timer Handle
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool timerCreate(osTimerFunc_t pCallback,
						const osTimerAttr_t *pTimerAttributes,
						osThreadId_t *pTimerHandle)
{
	bool blCheck = false;

	if (NULL != pTimerAttributes && NULL != pTimerHandle)
	{
		*pTimerHandle = osTimerNew(pCallback, osTimerPeriodic,
								  NULL, pTimerAttributes);
		blCheck = true;
	}
	else
	{
		perror("Unable to create timer");
	}

	return blCheck;
}

//*****************************.semaphoreCreate.********************************
// Purpose : Function to Create a semaphore
// Inputs  : pSemAttributes - Attribute of the semaphore
// 			 pSemaphoreHandle - Semaphore Handle
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool semaphoreCreate(const osSemaphoreAttr_t *pSemaphoreAttributes,
						   osSemaphoreId_t *pSemaphoreHandle)
{
	bool blCheck = false;

	if (NULL != pSemaphoreAttributes && NULL != pSemaphoreHandle)
	{
		*pSemaphoreHandle = osSemaphoreNew(1, 0, pSemaphoreAttributes);
		blCheck = true;
	}
	else
	{
		perror("Unable to create Semaphore");
	}

	return blCheck;
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

//******************************.semaphoreWait.*********************************
// Purpose : Function to acquire a semaphore
// Inputs  : pSemHandle - Semaphore Handle
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool semaphoreWait(osSemaphoreId_t *pSemaphoreHandle)
{
	bool blCheck = false;

	if (NULL != pSemaphoreHandle)
	{
		osSemaphoreAcquire(*pSemaphoreHandle, osWaitForever);
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
bool semaphorePost(osSemaphoreId_t *pSemaphoreHandle)
{
	bool blCheck = false;

	if (NULL != pSemaphoreHandle)
	{
		osSemaphoreRelease(*pSemaphoreHandle);
		blCheck = true;
	}
	else
	{
		perror("Semaphore releasing failed");
	}

	return blCheck;
}

//EOF
