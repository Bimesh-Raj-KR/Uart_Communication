//********************************* THREADS ************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
//
// Summary : Contains all global constants and forward declarations needed
// 			 for threads.c
// Note    : None
//
//******************************************************************************
#ifndef THREADS_H
#define THREADS_H

//******************************* Include Files ********************************
#include "sensorDriver.h"

//******************************* Global Types *********************************

//***************************** Global Constants *******************************
#define STACK_WORDS				(128)
#define MIN_SLEEP               (20)
#define MAX_LIMIT               (6)
#define THREAD_WAIT				(5)
#define STACK_BYTE              (4)
#define MAX_COUNT				(3)
#define HANDLE_COUNT 			(3)
#define DATA_SET                (2)
#define OUTPUT_START            (2)

//***************************** Global Variables *******************************

//**************************** Forward Declarations ****************************
bool communicationInit(void);
bool handleCreate(void);
void taskSync(void *pArgument);
void Callback(void *pArgument);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void microDelay(uint16 unDelay);

//*********************** Inline Method Implementations ************************

#endif // THREADS_H
// EOF
