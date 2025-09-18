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
// Return  : None
// Notes   : None
//******************************************************************************
void halInitialize(void)
{
	HAL_Init();
}

//*************************.clockConfiguration.*********************************
// Purpose : Function to configure the STM32 clock
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void clockConfiguration(void)
{

	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		errorHandler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
								|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		errorHandler();
	}
}

//********************************.uartInit.************************************
// Purpose : Function to Initialize the UART
// Inputs  : pHuart - Pointer to the UART to be initialized
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void uartInit(UART_HandleTypeDef *pHuart, USART_TypeDef *pUsart)
{
	pHuart->Instance = pUsart;
	pHuart->Init.BaudRate = BAUD_RATE;
	pHuart->Init.WordLength = UART_WORDLENGTH_8B;
	pHuart->Init.StopBits = UART_STOPBITS_1;
	pHuart->Init.Parity = UART_PARITY_NONE;
	pHuart->Init.Mode = UART_MODE_TX_RX;
	pHuart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	pHuart->Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(pHuart) != HAL_OK)
	{
	  errorHandler();
	}
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

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin : B1_Pin */
	  GPIO_InitStruct.Pin = B1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : PC3 */
	  GPIO_InitStruct.Pin = GPIO_PIN_3;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /*Configure GPIO pin : LD2_Pin */
	  GPIO_InitStruct.Pin = LD2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

//******************************.watchDogInit.**********************************
// Purpose : Function to initialize watchdog timer
// Inputs  : pHiwdg - Pointer to the watchdog timer handle
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void watchDogInit(IWDG_HandleTypeDef *pHiwdg)
{
	pHiwdg->Instance = IWDG;
	pHiwdg->Init.Prescaler = IWDG_PRESCALER_64;
	pHiwdg->Init.Reload = RELOAD_COUNTER;
	if (HAL_IWDG_Init(pHiwdg) != HAL_OK)
	{
	  errorHandler();
	}
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
// Return  : None
// Notes   : None
//******************************************************************************
void schedulerInit(void)
{
	osKernelInitialize();
}

//******************************.schedulerStart.********************************
// Purpose : Function to start the Scheduler
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void schedulerStart(void)
{
	osKernelStart();
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

//********************************.gpioRead.************************************
// Purpose : Function to read GPIO pins
// Inputs  : pPeripheral - The Port that should be read from
//			 unGpioPin - The pin within the port that should be read from
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool gpioRead(GPIO_TypeDef* pPeripheral, uint16 unGpioPin)
{
	bool blCheck = false;

	if (1 == HAL_GPIO_ReadPin(pPeripheral, unGpioPin))
	{
		blCheck = true;
	}

	return blCheck;
}

//********************************.gpioWrite.***********************************
// Purpose : Function to write GPIO pins
// Inputs  : pPeripheral - The Port that should be written to
//			 unGpioPin - The pin within the port that should be written to
//			 unPinState - The state of the pin after writing to it
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool gpioWrite(GPIO_TypeDef* pPeripheral, uint16 unGpioPin, uint16 unPinState)
{
	HAL_GPIO_WritePin(pPeripheral, unGpioPin, unPinState);

	return true;
}

//********************************.gpioToggle.**********************************
// Purpose : Function to toggle GPIO pins
// Inputs  : pPeripheral - The Port that should be toggled
//			 unGpioPin - The pin within the port that should be toggled
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool gpioToggle(GPIO_TypeDef* pPeripheral, uint16 unGpioPin)
{
	HAL_GPIO_TogglePin(pPeripheral, unGpioPin);

	return true;
}

//******************************.gpioTransmit.**********************************
// Purpose : Function to transmit data
// Inputs  : pHuart - USART used for transmitting data
//			 cData - Data to be transmitted
// Outputs : None
// Return  : true if there are no errors in the code else false
// Notes   : None
//******************************************************************************
bool gpioTransmit(UART_HandleTypeDef *pHuart, uint8 *cData)
{
	bool blCheck = false;

	if (NULL != pHuart)
	{
		HAL_UART_Transmit(pHuart, cData, sizeof(*cData), MAX_SLEEP);
		blCheck = true;
	}

	return blCheck;
}

//*******************************.gpioReceive.**********************************
// Purpose : Function to receive data
// Inputs  : pHuart - USART used for receiving data
//			 cData - Data to be received
// Outputs : None
// Return  : true if there are no errors in the code else false
// Notes   : None
//******************************************************************************
bool gpioReceive(UART_HandleTypeDef *pHuart, uint8 *cData)
{
	bool blCheck = false;

	if (NULL != pHuart)
	{
		HAL_UART_Receive(pHuart, cData, sizeof(*cData), MAX_SLEEP);
		blCheck = true;
	}

	return blCheck;
}

//******************************.refreshWatchDog.*******************************
// Purpose : Function to refresh watchdog timer
// Inputs  : pHiwdg - The watchDog Timer to refresh
// Outputs : None
// Return  : true if there are no errors in the code else false
// Notes   : None
//******************************************************************************
bool refreshWatchDog(IWDG_HandleTypeDef *pHiwdg)
{
	bool blCheck = false;

	if(NULL != pHiwdg)
	{
		HAL_IWDG_Refresh(pHiwdg);
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

	return blCheck;
}

//********************************.clearReset.**********************************
// Purpose : Function to clear reset flag
// Inputs  : None
// Outputs : None
// Return  : true if there are no errors in the code else false
// Notes   : None
//******************************************************************************
void clearReset(void)
{
	__HAL_RCC_CLEAR_RESET_FLAGS();
}
