//*********************************** THREADS **********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : threads.c
// Summary : Contains the thread that handles UART Communication and triggers
//			 interrupt in line with sensor pulses
// Note    : None
// Author  : Bimesh Raj K R
// Date    : 10/Sep/2025
//******************************************************************************

//****************************** Include Files *********************************
#include "threads.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************
static IWDG_HandleTypeDef stHiwdg = {0};
static UART_HandleTypeDef stHuartOne = {0};
static TIM_HandleTypeDef stHtimTwo = {0};
static osThreadId_t syncHandle = 0;
static osTimerId_t syncTimerHandle = 0;
static osSemaphoreId_t timerSemHandle = 0;
static uint32 ulCount = 0;

//***************************** Local Functions ********************************

//***************************.communicationInit.********************************
// Purpose : Function to initialize uart and watchdog
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
bool communicationInit(void)
{
	bool blCheck = false;
	uint8 ucCount = 0;

	if (true == uartInit(&stHuartOne, USART1))
	{
		ucCount ++;
	}
	else
	{
		perror("Unable to initialize USART1");
	}

	if (true == watchDogInit(&stHiwdg))
	{
		ucCount ++;
	}
	else
	{
		perror("Unable to initialize watchdog timer");
	}

	if (true == timerInit(&stHtimTwo))
	{
		ucCount ++;
	}
	else
	{
		perror("Unable to initialize TIM2");
	}

	if (MAX_COUNT == ucCount)
	{
		blCheck = true;
	}

	return blCheck;
}

//*******************************.handleCreate.*********************************
// Purpose : Function to create handle for thread, timer and semaphore
// Inputs  : None
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool handleCreate(void)
{
	bool blCheck = false;
	uint8 ucCount = 0;
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

	const osSemaphoreAttr_t interruptTimerAttributes =
	{
	  .name = "interrupt"
	};

	if (true == semaphoreCreate(&interruptTimerAttributes, &timerSemHandle))
	{
		ucCount ++;
	}

	if (true == timerCreate(Callback, &syncTimerAttributes, &syncTimerHandle))
	{
		ucCount ++;
	}

	if (true == threadCreate(taskSync, NULL, &syncAttributes, &syncHandle))
	{
		ucCount ++;
	}

	if (HANDLE_COUNT == ucCount)
	{
		blCheck = true;
	}
	else
	{
		perror("Failed to create all Handles\r");
	}

	return blCheck;
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
  uint8 ucTelemetry = 0;
  uint16 unIterator = 0;
  BLE_SENSOR stReadings = {0};


  if (true != timeBaseStart(&stHtimTwo))
  {
	  perror("Unable to start TIM base in interrupt mode");
  }

  if (true == checkReset())
  {
	  clearReset();
	  printf("\nRefreshing STM32\r\n");
	  gpioWrite(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	  gpioWrite(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);

	  for (unIterator = 0; unIterator < MAX_LIMIT; unIterator ++)
	  {
		  gpioToggle(GPIOA, GPIO_PIN_5);

		  if (true != milliDelay(MIN_SLEEP))
		  {
			  perror("Unable to delay execution");
		  }
	  }
  }

  while (1)
  {
	  ulCount = 0;

	  if (true != timerStart(&syncTimerHandle))
	  {
		  perror("Unable to start timer");
	  }

	  ucPing = DATA_SET;
	  ucTelemetry = 0;

	  if (true == gpioTransmit(&stHuartOne, &ucPing, sizeof(ucPing)))
	  {
		  printf("Ping Succesfully transmitted\r\n");
	  }
	  else
	  {
		  perror("Failed to transmit data");
	  }

	  if (true == gpioReceive(&stHuartOne, &ucTelemetry))
	  {
		  if (DATA_SET == ucTelemetry)
		  {
			  printf("Telemetry request Successfully received\r\n");
			  gpioWrite(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

			  if (true != milliDelay(MAX_SLEEP))
			  {
				  perror("Unable to delay execution");
			  }

			  gpioWrite(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

			  if (true != milliDelay(MAX_SLEEP))
			  {
				  perror("Unable to delay execution");
			  }

			  sensorStart();

			  if (true != milliDelay(THREAD_WAIT))
			  {
				  perror("Unable to delay execution");
			  }

			  if (true == sensorReadings(&stReadings))
			  {
				  if (true == gpioTransmit(&stHuartOne, &stReadings,
						  sizeof(stReadings)))
				  {
					  printf("Sensor Readings Successfully transmitted\r\n");
				  }
				  else
				  {
					  perror("Failed to transmit data");
				  }
			  }
			  else
			  {
				  perror("Unable to read sensor data");
			  }

			  if (true != refreshWatchDog(&stHiwdg))
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

//**********************.HAL_GPIO_EXTI_Callback.********************************
// Purpose : Interrupt function that triggers on every falling edge
// Inputs  : unGpioPin - The GPIO pin that triggered the interrupt
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void HAL_GPIO_EXTI_Callback(uint16 unGpioPin)
{
	uint32 ulTime = 0;

    if(unGpioPin == GPIO_PIN_11)
    {
    	ulCount ++;
    	ulTime = __HAL_TIM_GET_COUNTER(&stHtimTwo);
    	__HAL_TIM_SET_COUNTER(&stHtimTwo, 0);

    	if (OUTPUT_START < ulCount)
    	{
			if (true == sensorOutput(ulTime))
			{
				// Success case
			}
    	}
    }
}


//********************************.microDelay.**********************************
// Purpose : Function to run a delay of microseconds
// Inputs  : unDelay - the delay value
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void microDelay(uint16 unDelay)
{
	__HAL_TIM_SET_COUNTER(&stHtimTwo, 0);

	while (unDelay > __HAL_TIM_GET_COUNTER(&stHtimTwo))
	{
	  // wait until timer counts up to unDelay
	}
}

