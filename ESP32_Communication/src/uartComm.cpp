//************************* Inter Board Communication **************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : uartComm.cpp
// Summary : Receives ping and transmits back acknowledgement
// Note    : None
// Author  : Bimesh Raj K R
// Date    : 10/Sep/2025
//******************************************************************************

//****************************** Include Files *********************************
#include "uartComm.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//***************************** Local Functions ********************************

//***************************.uartCommunication.********************************
// Purpose : Function to set up different GPIO pins
// Inputs  : None
// Outputs : None
// Return  : true if no error, else false
// Notes   : None
//******************************************************************************
bool uartCommunication(void)
{
    bool blCheck = false;
    uint8 ucPing = 0;
    uint8 ucAcknowledge = 0;

    if (0 < Serial2.available())
    {
        ucPing = Serial2.read();
    }

    if (DATA_SET == ucPing)
    {
        ucAcknowledge = DATA_SET;
        digitalWrite(GPIO_LED, HIGH);
        Serial.println("Successfully received Ping, Sending Acknowledgment");
        delay(MAX_SLEEP);
        Serial2.write((uint8*)&ucAcknowledge, sizeof(uint8));
        digitalWrite(GPIO_LED, LOW);
        blCheck = true;
    }

    return blCheck;
}

//******************************.uartFailure.***********************************
// Purpose : Function to reset ESP32
// Inputs  : None
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void uartFailure(void)
{
    uint8 ucIterator = 0;

    Serial.println("Resetting ESP32");

    for (ucIterator = 0; ucIterator < MAX_LIMIT; ucIterator ++)
    {
      digitalWrite(GPIO_LED, HIGH);
      delay(MIN_SLEEP);
      digitalWrite(GPIO_LED, LOW);
      delay(MIN_SLEEP);
    }

    ESP.restart();
}