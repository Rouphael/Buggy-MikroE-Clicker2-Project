# Troubleshooting

## Common Issues
- **No Response from Buggy**: Ensure the UART connection is correctly established.
- **Incorrect Movement**: Double-check the motor PWM pin mappings.
- **FIFO Full Error**: Wait for the current commands to complete before sending new ones.

## Debugging Tips
- Use an oscilloscope to verify PWM signal generation.
- Monitor UART messages to ensure commands are received and processed correctly.
