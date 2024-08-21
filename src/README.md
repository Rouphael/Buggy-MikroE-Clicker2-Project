# Source Code

## Overview
This folder contains the source code for the Buggy Autonomous Ground Vehicle project. The firmware is written for the mikroE Clicker 2 board with a dsPIC33 microcontroller and is responsible for controlling the Buggy rover platform.

## Contents
- **main.c**: The main entry point for the firmware, including the setup and main control loop.
- **config.h**: Configuration settings for the microcontroller, including clock settings and peripheral initialization.
- **motors.c**: Code related to motor control, including PWM signal generation and direction control.
- **sensors.c**: Handles input from sensors, including the IR sensor for obstacle detection.
- **uart.c**: Manages UART communication, including sending and receiving commands from the PC.
- **utils.c**: Utility functions used throughout the project, such as delay routines and status LED control.
- **Makefile**: A script for building the project, if using a command-line toolchain.

## Firmware Architecture
The firmware is structured around a real-time control loop operating at 1 kHz. It manages motor control, sensor input, and UART communication in a state machine pattern.

### Key Features
- **State Machine**: Manages the operational states of the Buggy (e.g., waiting for start, executing commands).
- **PWM Control**: Generates PWM signals to drive the motors, supporting both forward and backward movement.
- **UART Command Interface**: Receives movement commands from the PC and processes them in a FIFO queue.
- **Obstacle Detection**: Uses an IR sensor to prevent the Buggy from colliding with obstacles.

## Building the Firmware
### Prerequisites
- **MPLAB X IDE**: Download and install MPLAB X IDE from Microchip's website.
- **XC16 Compiler**: Ensure the XC16 compiler is installed and configured in MPLAB X.

### Building
1. Open the project in MPLAB X IDE.
2. Build the project by selecting `Build Main Project` from the `Run` menu.
3. Upload the firmware to the Clicker 2 board using a compatible programmer/debugger.

## Usage
Once the firmware is uploaded, connect the Buggy to your PC via UART and use a serial terminal to send commands. The Buggy will execute commands such as moving forward, rotating, and stopping based on the received UART instructions.

