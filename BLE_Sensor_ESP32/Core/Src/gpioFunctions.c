//******************************** GPIO Functions ******************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : gpioFunctions.c
// Summary : Wrapper for necessary STM32 functions
// Note    : None
// Author  : Bimesh Raj K R
// Date    : 10/Sep/2025
//******************************************************************************

//****************************** Include Files *********************************
#include "gpioFunctions.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//***************************** Local Functions ********************************
static void errorHandler(void);

//******************************.halInitialize.*********************************
// Purpose : Function to initialize the HAL library
// Inputs  : None
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool halInitialize(void)
{
	bool blCheck = false;

	if (HAL_OK == HAL_Init())
	{
		blCheck = true;
	}
	else
	{
		perror("HAL initialization Failed");
	}

	return blCheck;
}

//*************************.clockConfiguration.*********************************
// Purpose : Function to configure the STM32 clock
// Inputs  : None
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool clockConfiguration(void)
{
	bool blCheck = false;
	uint8 ucCount = 0;

	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI |
			RCC_OSCILLATORTYPE_LSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;

	if (HAL_OK == HAL_RCC_OscConfig(&RCC_OscInitStruct))
	{
		ucCount ++;
	}
	else
	{
		errorHandler();
	}

	/** Initializes the CPU, AHB and APB buses clocks*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
								| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_OK == HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2))
	{
		ucCount ++;
	}
	else
	{
		errorHandler();
	}

	if (CLOCK_ERROR == ucCount)
	{
		blCheck = true;
	}
	else
	{
		perror("Failed to configure clock");
	}

	return blCheck;
}

//********************************.uartInit.************************************
// Purpose : Function to Initialize the UART
// Inputs  : pstHuart - Pointer to the UART to be initialized
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool uartInit(UART_HandleTypeDef *pstHuart, USART_TypeDef *pUsart)
{
	bool blCheck = false;

	if ((NULL != pstHuart) && (NULL != pUsart))
	{
		pstHuart->Instance = pUsart;
		pstHuart->Init.BaudRate = BAUD_RATE;
		pstHuart->Init.WordLength = UART_WORDLENGTH_8B;
		pstHuart->Init.StopBits = UART_STOPBITS_1;
		pstHuart->Init.Parity = UART_PARITY_NONE;
		pstHuart->Init.Mode = UART_MODE_TX_RX;
		pstHuart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
		pstHuart->Init.OverSampling = UART_OVERSAMPLING_16;

		if (HAL_OK == HAL_UART_Init(pstHuart))
		{
			blCheck = true;
		}
		else
		{
			errorHandler();
		}
	}
	else
	{
		perror("NULL check Failed");
	}

	return blCheck;
}

//********************************.gpioInit.************************************
// Purpose : Function to initialize GPIO pins
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void gpioInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// GPIO Ports Clock Enable
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// Configure GPIO pin Output Level
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

	// Configure GPIO pins : B1_Pin PC0
	GPIO_InitStruct.Pin = B1_Pin|GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	// Configure GPIO pin : PC3
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	// Configure GPIO pin : LD2_Pin
	GPIO_InitStruct.Pin = LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);
}

//******************************.watchDogInit.**********************************
// Purpose : Function to initialize watchdog timer
// Inputs  : pstHiwdg - Pointer to the watchdog timer handle
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool watchDogInit(IWDG_HandleTypeDef *pstHiwdg)
{
	bool blCheck = false;

	if (NULL != pstHiwdg)
	{
		pstHiwdg->Instance = IWDG;
		pstHiwdg->Init.Prescaler = IWDG_PRESCALER_256;
		pstHiwdg->Init.Reload = RELOAD_COUNTER;

		if (HAL_OK == HAL_IWDG_Init(pstHiwdg))
		{
			blCheck = true;
		}
		else
		{
			errorHandler();
		}
	}
	return blCheck;
}

//******************************.timerInit.**********************************
// Purpose : Function to initialize TIM timer
// Inputs  : pstHtim - Pointer to TIM timer handle
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool timerInit(TIM_HandleTypeDef *pstHtim)
{
	bool blCheck = false;
	uint8 ucCount = 0;
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	if (NULL != pstHtim)
	{
		pstHtim->Instance = TIM2;
		pstHtim->Init.Prescaler = TIM_PRESCALER;
		pstHtim->Init.CounterMode = TIM_COUNTERMODE_UP;
		pstHtim->Init.Period = TIM_COUNTER;
		pstHtim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		pstHtim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

		if (HAL_OK == HAL_TIM_Base_Init(pstHtim))
		{
			ucCount ++;
		}
		else
		{
			errorHandler();
		}

		sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

		if (HAL_OK == HAL_TIM_ConfigClockSource(pstHtim, &sClockSourceConfig))
		{
			ucCount ++;
		}
		else
		{
			errorHandler();
		}

		sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
		sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

		if (HAL_OK == HAL_TIMEx_MasterConfigSynchronization(pstHtim,
				&sMasterConfig))
		{
			ucCount ++;
		}
		else
		{
			errorHandler();
		}

		if (TIM_ERROR == ucCount)
		{
			blCheck = true;
		}
		else
		{
			perror("Failed to Initialize TIM");
		}
	}
	else
	{
		perror("NULL check Failed");
	}

	return blCheck;
}
//****************************.interruptEnable.*********************************
// Purpose : Function to enable and set priority of the interrupt
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void interruptEnable(void)
{
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, PRIORITY, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

//******************************.schedulerInit.*********************************
// Purpose : Function to initialize the Scheduler
// Inputs  : None
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool schedulerInit(void)
{
	bool blCheck = false;

	if (osOK == osKernelInitialize())
	{
		blCheck = true;
	}
	else
	{
		perror("Failed to initialize kernel");
	}

	return blCheck;
}

//******************************.schedulerStart.********************************
// Purpose : Function to start the Scheduler
// Inputs  : None
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool schedulerStart(void)
{
	bool blCheck = false;

	if (osOK == osKernelStart())
	{
		blCheck = true;
	}
	else
	{
		perror("Failed to start kernel");
	}

	return blCheck;
}

//********************************.errorHandler.********************************
// Purpose : Function to handle any error that happen during execution
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
static void errorHandler(void)
{
  __disable_irq();

  while (1)
  {
	  //infinite loop
  }
}

//********************************.gpioWrite.***********************************
// Purpose : Function to write GPIO pins
// Inputs  : pPeripheral - The Port that should be written to
//			 unGpioPin - The pin within the port that should be written to
//			 unPinState - The state of the pin after writing to it
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void gpioWrite(GPIO_TypeDef* pPeripheral, uint16 unGpioPin, uint16 unPinState)
{
	HAL_GPIO_WritePin(pPeripheral, unGpioPin, unPinState);
}

//********************************.gpioRead.************************************
// Purpose : Function to read GPIO pins
// Inputs  : pPeripheral - The Port that should be read from
//			 unGpioPin - The pin within the port that should be read from
// Outputs : None
// Return  : true if the pin is set, else false
// Notes   : None
//******************************************************************************
bool gpioRead(GPIO_TypeDef* pPeripheral, uint16 unGpioPin)
{
	bool blCheck = false;

	if (GPIO_PIN_SET == HAL_GPIO_ReadPin(pPeripheral, unGpioPin))
	{
		blCheck = true;
	}

	return blCheck;
}

//********************************.gpioToggle.**********************************
// Purpose : Function to toggle GPIO pins
// Inputs  : pPeripheral - The Port that should be toggled
//			 unGpioPin - The pin within the port that should be toggled
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void gpioToggle(GPIO_TypeDef* pPeripheral, uint16 unGpioPin)
{
	HAL_GPIO_TogglePin(pPeripheral, unGpioPin);
}

//******************************.gpioTransmit.**********************************
// Purpose : Function to transmit data
// Inputs  : pstHuart - USART used for transmitting data
//			 cData - Data to be transmitted
//			 ulSize - Size of data to be transmitted
// Outputs : None
// Return  : true if there are no errors in the code else false
// Notes   : None
//******************************************************************************
bool gpioTransmit(UART_HandleTypeDef *pstHuart, void *cData, uint32 ulSize)
{
	bool blCheck = false;

	if (NULL != pstHuart)
	{
		HAL_UART_Transmit(pstHuart, cData, ulSize, MAX_SLEEP);
		blCheck = true;
	}

	return blCheck;
}

//*******************************.gpioReceive.**********************************
// Purpose : Function to receive data
// Inputs  : pstHuart - USART used for receiving data
//			 cData - Data to be received
// Outputs : None
// Return  : true if there are no errors in the code else false
// Notes   : None
//******************************************************************************
bool gpioReceive(UART_HandleTypeDef *pstHuart, uint8 *cData)
{
	bool blCheck = false;

	if (NULL != pstHuart)
	{
		HAL_UART_Receive(pstHuart, cData, sizeof(*cData), MAX_SLEEP);
		blCheck = true;
	}

	return blCheck;
}

//******************************.refreshWatchDog.*******************************
// Purpose : Function to refresh watchdog timer
// Inputs  : pstHiwdg - The watchDog Timer to refresh
// Outputs : None
// Return  : true if there are no errors in the code else false
// Notes   : None
//******************************************************************************
bool refreshWatchDog(IWDG_HandleTypeDef *pstHiwdg)
{
	bool blCheck = false;

	if(NULL != pstHiwdg)
	{
		HAL_IWDG_Refresh(pstHiwdg);
		blCheck = true;
	}

	return blCheck;
}

//********************************.checkReset.**********************************
// Purpose : Function to check if last reset was triggered by watchdog
// Inputs  : None
// Outputs : None
// Return  : true if there are no errors in the code else false
// Notes   : None
//******************************************************************************
bool checkReset(void)
{
	bool blCheck = false;

	if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST))
	{
		blCheck = true;
	}
	else
	{
		perror("Reset was not due to watchDog timer");
	}

	return blCheck;
}

//********************************.clearReset.**********************************
// Purpose : Function to clear reset flag
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void clearReset(void)
{
	__HAL_RCC_CLEAR_RESET_FLAGS();
}

//********************************.modeChange.**********************************
// Purpose : Function to change mode of the GPIO pin PC11
// Inputs  : ulMode - The mode to which the pin must be configured
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void modeChange(uint32 ulMode)
{
	GPIO_InitTypeDef stGpioInitStruct = {0};

	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);

	stGpioInitStruct.Pin = GPIO_PIN_11;
	stGpioInitStruct.Mode = ulMode;
	stGpioInitStruct.Pull = GPIO_NOPULL;
	stGpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &stGpioInitStruct);

	if (ulMode == GPIO_MODE_IT_FALLING)
	{
		interruptEnable();
	}
}

//********************************.milliDelay.**********************************
// Purpose : Function to run a delay of milliseconds
// Inputs  : ulDelay - The Delay for which execution must be halted
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool milliDelay(uint32 ulDelay)
{
	bool blCheck = false;

	if (osOK == osDelay(ulDelay))
	{
		blCheck = true;
	}
	else
	{
		perror("Failed to Start Delay");
	}

	return blCheck;
}

//******************************.timeBaseStart.*********************************
// Purpose : Function to start TIM Base generation in interrupt mode
// Inputs  : pstHtim - TIM handle
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool timeBaseStart(TIM_HandleTypeDef *pstHtim)
{
	bool blCheck = false;

	if (NULL != pstHtim)
	{
		if (HAL_OK == HAL_TIM_Base_Start_IT(pstHtim))
		{
			blCheck = true;
		}
	}
	else
	{
		perror("Null Check Failed");
	}

	return blCheck;
}

// EOF
