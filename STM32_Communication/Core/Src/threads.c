//*********************************** THREADS **********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : gpioFunctions.c
// Summary : Contains the thread that handles UART Communication
// Note    : None
// Author  : Bimesh Raj K R
// Date    : 10/Sep/2025
//******************************************************************************

//****************************** Include Files *********************************
#include "threads.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************
static IWDG_HandleTypeDef hiwdg;
static UART_HandleTypeDef huart1;
static osThreadId_t syncHandle;
static osTimerId_t syncTimerHandle;
static osSemaphoreId_t timerSemHandle;

//***************************** Local Functions ********************************

//***************************.communicationInit.********************************
// Purpose : Function to initialize uart and watchdog
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void communicationInit(void)
{
	uartInit(&huart1, USART1);
	watchDogInit(&hiwdg);
}

//*******************************.handleCreate.*********************************
// Purpose : Function to create handle for thread, timer and semaphore
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void handleCreate(void)
{
	const osThreadAttr_t syncAttributes =
	{
	  .name = "sync",
	  .stack_size = STACK_WORDS * STACK_BYTE,
	  .priority = (osPriority_t) osPriorityNormal,
	};

	const osTimerAttr_t syncTimerAttributes =
	{
	  .name = "syncTimer"
	};

	const osSemaphoreAttr_t interruptAttributes =
	{
	  .name = "interrupt"
	};

	timerSemHandle = semCreate(&interruptAttributes);
	syncTimerHandle = timerCreate(Callback, &syncTimerAttributes);
	syncHandle = threadCreate(taskSync, NULL, &syncAttributes);
}

//********************************.taskSync.************************************
// Purpose : Function to send ping to ESP32 and receive acknowledgment back
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void taskSync(void *pArgument)
{
  uint8 ucPing = 0;
  uint8 ucAcknowledge = 0;
  uint16 unIterator = 0;

  if (true == checkReset())
  {
	  clearReset();
	  printf("Refreshing STM32\r\n");
	  gpioWrite(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	  gpioWrite(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);

	  for (unIterator = 0; unIterator < MAX_LIMIT; unIterator ++)
	  {
		  gpioToggle(GPIOA, GPIO_PIN_5);
		  taskDelay((uint32)MIN_SLEEP);
	  }
  }

  while(1)
  {
	  if (true != timerStart(&syncTimerHandle))
	  {
		  perror("Unable to start timer");
	  }

	  ucPing = DATA_SET;
	  ucAcknowledge = 0;

	  if (true == gpioTransmit(&huart1, &ucPing))
	  {
		  printf("Ping Succesfully transmitted\r\n");
	  }
	  else
	  {
		  perror("Failed to transmit data");
	  }

	  if (true == gpioReceive(&huart1, &ucAcknowledge))
	  {
		  if (DATA_SET == ucAcknowledge)
		  {
			  printf("Acknowledgement Succesfully received\r\n");
			  gpioWrite(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
			  taskDelay(MAX_SLEEP);
			  gpioWrite(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
			  taskDelay(MAX_SLEEP);

			  if (true != refreshWatchDog(&hiwdg))
			  {
				  perror("Unable to refresh watchdog");
			  }
		  }
	  }
	  else
	  {
		  perror("Failed to receive data");
	  }

	  if (true != semaphoreWait(&timerSemHandle))
	  {
		  perror("Unable to acquire semaphore");
	  }
  }
}

//********************************.Callback.************************************
// Purpose : Function to execute when timer timeout
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void Callback(void *pArgument)
{
	if (true != semaphorePost(&timerSemHandle))
	{
	  perror("Unable to release semaphore");
	}

}

//EOF
