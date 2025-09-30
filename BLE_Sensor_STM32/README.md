# STM32_Communication

Allows transmission of ping from **STM32** and reception of telemetry every 2s. On reception of telemetry **DHT11** sensor readings are taken from **PC11,** converted to a struct packet and send over **UART.** If telemetry request is not received before watchdog timeout, **STM32** resets and sends pulse to reset **ESP32** via **PC3** pin. 

## Features

Organized source codes in a single directories
Organized includes in a single directories
Use of **STM32CubeIDE**

## Prerequisites

**STM32CubeIDE** ≥ 1.18.1

## Further Requirements

1. Use **Build** tool of **STM32CubeIDE** to build the code.
2. Use **Run** tool of **STM32CubeIDE** to feed the code to **STM32**
3. Use **STM32CubeIDE** built in console or others like **Tera Term** to monitor output