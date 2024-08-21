# Command Protocol

The system communicates with a PC via UART using a custom command protocol. Below is a breakdown of the commands:

## Command Format
`$PCCMD,x,t*`
- **x**: Action type (1 = forward, 2 = counterclockwise rotation, etc.)
- **t**: Duration of the action in milliseconds.

## Acknowledgment Messages
- `$MACK,1*`: Command accepted and added to the queue.
- `$MACK,0*`: Command rejected (FIFO full).

## System Messages
- `$MBATT,v_batt*`: Battery voltage reading (sent at 1 Hz).
- `$MDIST,distance*`: Obstacle distance reading (sent at 10 Hz).
