/* 
 * File:   UART.c
 * Author: Rafael
 */

#include "xc.h"
#include "UART.h"
#include <stdio.h>
#include <string.h>
#include "CB.h"

uint8_t byte;

void UART_Init (void){
    TRISDbits.TRISD0 = 0;       // Output port TX/RD0
    TRISDbits.TRISD11 = 1;      // Input pin RX/RD11
    
    U2MODE = 0x0000;            // Clear UART2 registers
    U2STA = 0x0000;
    U2BRG = BRGVAL;             // Load UART2 Baud Rate Generator
    U2STAbits.UTXISEL0 = 1;     // Interrupt is generated when the last transmission is over 
    U2STAbits.UTXISEL1 = 0;     //(that is, the last character is shifted out
                                //of the Transmit Shift register) 
                                //and all the transmit operations are completed
    U2STAbits.URXISEL = 0;      // Interrupt after one RX character is received;
    //U2STAbits.URXISEL = 2;      //Interrupt flag bit is set when Receive Buffer is 3/4 full
        
    IEC1bits.U2TXIE = 1;        // Enable UART2 TX Interrupt
    IEC1bits.U2RXIE = 1;        // Enable UART2 RX Interrupt
    
    U2MODEbits.UARTEN = 1;      // Enable UART2
    U2STAbits.UTXEN = 1;        // Enable UART2 TX
    
    RPOR0bits.RP64R = 0x03;     // U2TX -> RP64
    RPINR19bits.U2RXR = 0x4B;   // U2RX <- RP175
    
    IFS1bits.U2TXIF = 0;        // Clear UART2 TX Interrupt Flag
    IFS1bits.U2RXIF = 0;        // Clear UART2 RX Interrupt Flag
}

void UART_wstr(char str[]){
    for(int i=0;i<strlen(str);i++){
        while(U2STAbits.UTXBF);
        U2TXREG = str[i];
    }
}
void UART_TX_CB(circ_bbuf_t *cb){
    while(cb->dataCounter>0 && !U2STAbits.UTXBF){
        
        circ_bbuf_pop(cb,&byte);
        U2TXREG = byte;
    }
}

void cmd_handler(void){
    
}