//************************* Inter Board Communication **************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : main.cpp
// Summary : Receives ping and transmits back acknowledgement
// Note    : None
// Author  : Bimesh Raj K R
// Date    : 10/Aug/2025
//******************************************************************************

//****************************** Include Files *********************************
#include "uartComm.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************
static const uint32 ulInterruptPin = INTERRUPT_PIN;
volatile bool blFlag = false;

//***************************** Local Functions ********************************

//*****************************.triggerInterrupt.*******************************
// Purpose : Function that executes during an interrupt
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void IRAM_ATTR triggerInterrupt() 
{
  blFlag = true;
}

//*********************************.setup.**************************************
// Purpose : Function to set up different GPIO pins
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void setup() 
{
  pinMode(GPIO_LED, OUTPUT);
  pinMode(INTERRUPT_PIN, INPUT);
  Serial.begin(BAUD_RATE);
  Serial2.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);
  attachInterrupt(digitalPinToInterrupt(ulInterruptPin), triggerInterrupt, 
                  RISING);
}

//*********************************.setup.**************************************
// Purpose : Function to run the code indefinitely
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void loop() 
{
  if (true == blFlag)
  {
    uartFailure();
  }

  uartCommunication();

  delay(MAX_SLEEP);
}
