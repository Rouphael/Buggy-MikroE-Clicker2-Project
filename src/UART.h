/* 
 * File:   UART.h
 * Author: Rafael
 */

#ifndef UART_H
#define	UART_H

#include "CB.h"

#define Fcy 72000000
#define BAUDRATE 9600                    //Desired Baud Rate
#define BRGVAL ((Fcy/BAUDRATE)/16)-1   //Formula for U2BRG register

void UART_Init (void);
void UART_TX_CB(circ_bbuf_t *cb);

#endif	/* UART_H */

