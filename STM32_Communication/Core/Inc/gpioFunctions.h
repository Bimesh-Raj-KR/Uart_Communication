//*************************** GPIO Functions ***********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
//
// Summary : Contains all global constants and forward declarations needed
//			 for gpioFunctions.c
// Note    : None
//
//******************************************************************************
#ifndef GPIOFUNCTIONS_H
#define GPIOFUNCTIONS_H

//******************************* Include Files ********************************
#include "common.h"

//******************************* Global Types *********************************


//***************************** Global Constants *******************************
#define BAUD_RATE				(115200)
#define RELOAD_COUNTER			(1499)
#define MAX_SLEEP               (100)
#define PRIORITY				(5)

//***************************** Global Variables *******************************

//**************************** Forward Declarations ****************************
void halInitialize(void);
void clockConfiguration(void);
void uartInit(UART_HandleTypeDef *pHuart, USART_TypeDef *pUsart);
void gpioInit(void);
void watchDogInit(IWDG_HandleTypeDef *pHiwdg);
void interruptEnable(void);
void schedulerInit(void);
void schedulerStart(void);
bool gpioRead(GPIO_TypeDef* pPeripheral, uint16 gpioPin);
bool gpioWrite(GPIO_TypeDef* pPeripheral, uint16 unGpioPin, uint16 unPinState);
bool gpioToggle(GPIO_TypeDef* pPeripheral, uint16 gpioPin);
bool gpioTransmit(UART_HandleTypeDef *pHuart, uint8 *cData);
bool gpioReceive(UART_HandleTypeDef *pHuart, uint8 *cData);
bool refreshWatchDog(IWDG_HandleTypeDef *pHiwdg);
bool checkReset(void);
void clearReset(void);

//*********************** Inline Method Implementations ************************

#endif // GPIOFUNCTIONS_H
// EOF
