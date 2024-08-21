# Buggy Autonomous Ground Vehicle
This project implements a basic control system for an autonomous ground vehicle using the mikroE Clicker 2 board for dsPIC33. The system controls a Buggy rover platform, enabling it to perform actions such as moving forward, rotating, and stopping based on commands received via UART. It also integrates sensors for obstacle detection.
## Features
- Real-time motor control with 1 kHz update frequency
- Command processing via UART interface
- Obstacle detection using IR sensors
- Battery voltage monitoring
- Expandability using mikroBUS™ Click boards
## Hardware Setup
- **Microcontroller**: dsPIC33 on mikroE Clicker 2
- **Platform**: Buggy rover with mikroBUS™ sockets
- **Sensors**: IR sensor on mikroBUS 1 or 2
- **Communication**: UART to RS232 module
## Pin Mapping
- RB8: Left side lights
- RF1: Right-side lights
- RF0: Brakes
- RD1/RP65: Left PWM backward motion
- RD2/RP66: Left PWM forward motion
- RD3/RP67: Right PWM backward motion
- RD4/RP68: Right PWM forward motion
- AN14/AN15: IR sensor voltage
- RB9/RA3: IR sensor enable
- RD0/RP64: UART TX
- RD11/RPI75: UART RX
## Firmware Requirements
- Control loop at 1 kHz frequency
- Motor PWM update at 10 kHz
- UART communication for command processing
- LED indicators for status monitoring
## Getting Started
1. Clone the repository: `git clone https://github.com/Rouphael/Buggy-MikroE-Clicker2-Project`
2. Open the project in MPLAB X IDE.
3. Build and upload the firmware to the Clicker 2 board.
4. Connect the Buggy rover and test the system.
## Documentation
Detailed project documentation can be found in the [docs/](docs/) folder.
## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
