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
#include "threadOperations.h"
#include "gpioFunctions.h"

//******************************* Global Types *********************************

//***************************** Global Constants *******************************
#define STACK_WORDS				(128)
#define MIN_SLEEP               (20)
#define MAX_LIMIT               (6)
#define STACK_BYTE              (4)
#define DATA_SET                (2)

//***************************** Global Variables *******************************

//**************************** Forward Declarations ****************************
void communicationInit(void);
void handleCreate(void);
void taskSync(void *pArgument);
void Callback(void *pArgument);

//*********************** Inline Method Implementations ************************

#endif // THREADS_H
// EOF
