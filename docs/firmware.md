# Firmware Architecture

## Overview
The firmware is designed to control the Buggy rover by processing commands received via UART and executing motor control based on those commands.

## Control Loop
The control loop operates at a frequency of 1 kHz, handling motor PWM updates and sensor readings.

## State Machine
The system operates in two primary states:
- **Wait for Start**: The Buggy awaits a start command, with all motors off and indicators blinking.
- **Execute**: The Buggy processes and executes movement commands from the FIFO queue.

## Interrupt Service Routines
The firmware uses ISRs for handling:
- PWM signal generation for motor control.
- UART communication to ensure no loss of commands.
