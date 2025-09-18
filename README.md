# Uart_Communication

An Inter-Board Communication project that allows uart communication between **STM32** and **ESP32**

## Features

Organized source code in multiple directories
Use of **PlatformIO** and **STM32CubeIDE**

## Prerequisites

**PlatformIO** ≥ 3.3.4
**STM32CubeIDE** ≥ 1.18.1

## Physical Connections

### STM32 -> ESP32

1. **D2 -> TX2**
2. **D8 -> RX2**
3. **PC3 -> D13**
4. **GND -> GND**

### Further Requirements

1. Connect the Boards via ST-Link to the System and use console monitor to verify transmission
2. The LEDs on both boards are configured to blink every 100ms incase of successful transmission and every 20ms incase of reset.
3. Connect **PC3** pin to a Pull Down Resistor