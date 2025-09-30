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
#define TIM_COUNTER				(65535)
#define RELOAD_COUNTER			(875)
#define MAX_SLEEP               (100)
#define TIM_PRESCALER			(63)
#define PRIORITY				(5)
#define TIM_ERROR				(3)
#define CLOCK_ERROR				(2)

//***************************** Global Variables *******************************

//**************************** Forward Declarations ****************************
bool halInitialize(void);
bool clockConfiguration(void);
bool uartInit(UART_HandleTypeDef *pHuart, USART_TypeDef *pUsart);
void gpioInit(void);
bool watchDogInit(IWDG_HandleTypeDef *pHiwdg);
bool timerInit(TIM_HandleTypeDef *pHtim);
void interruptEnable(void);
bool schedulerInit(void);
bool schedulerStart(void);
void gpioWrite(GPIO_TypeDef* pPeripheral, uint16 unGpioPin, uint16 unPinState);
bool gpioRead(GPIO_TypeDef* pPeripheral, uint16 unGpioPin);
void gpioToggle(GPIO_TypeDef* pPeripheral, uint16 gpioPin);
bool gpioTransmit(UART_HandleTypeDef *pHuart, void *cData, uint32 ulSize);
bool gpioReceive(UART_HandleTypeDef *pHuart, uint8 *cData);
bool refreshWatchDog(IWDG_HandleTypeDef *pHiwdg);
bool checkReset(void);
void clearReset(void);
void modeChange(uint32 ulMode);
bool milliDelay(uint32 ulDelay);
bool timeBaseStart(TIM_HandleTypeDef *pHtim);

//*********************** Inline Method Implementations ************************

#endif // GPIOFUNCTIONS_H
// EOF
