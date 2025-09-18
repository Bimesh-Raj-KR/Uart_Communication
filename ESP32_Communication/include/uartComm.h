//************************* Inter Board Communication **************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//******************************************************************************
//
// Summary : Contains all global constants and forward declarations needed for
//           uartComm.cpp function
// Note    : None
// 
//******************************************************************************
#ifndef UARTCOMM_H
#define UARTCOMM_H

//******************************* Include Files ********************************
#include <stdio.h>
#include <stdbool.h>
#include <Arduino.h>

//******************************* Global Types ********************************* 
typedef unsigned char uint8;
typedef unsigned int uint32;

//***************************** Global Constants ******************************* 
#define GPIO_LED                (2)
#define DATA_SET                (2)
#define MAX_LIMIT               (3)
#define INTERRUPT_PIN           (13)
#define RX_PIN                  (16)
#define TX_PIN                  (17)
#define MIN_SLEEP               (20)
#define MAX_SLEEP               (100)
#define BAUD_RATE               (115200)

//***************************** Global Variables ******************************* 

//**************************** Forward Declarations **************************** 
bool uartCommunication(void);
void uartFailure(void);

//*********************** Inline Method Implementations ************************ 

#endif // UARTCOMM_H
// EOF 