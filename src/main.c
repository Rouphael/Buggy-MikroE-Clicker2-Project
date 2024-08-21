/*
 * File:   main.c
 * Author: Rafael
 *         Memebers:    1. Ali RabbaniDoost(5650240)
 *                      2. Seyed Emad Razavi(5782734)
 *                      3. Tanvir Rahman Sajal(6007201)
 *                      4. YAZAN KAYALI(5959956)
 */


#include "xc.h"
#include "timer.h"
#include "UART.h"
#include "CB.h"
#include "ADC.h"
#include "motor.h"
#include "parser.h"
#include "scheduler.h"
#include <stdio.h>
#include <string.h>

#define FOSC 144000000
#define MAX_TASKS 6
#define COMMAND_QUEUE_SIZE 10

typedef struct {
    int state;
    int x;
    int t;
    int obstacle;
} robot_data;

CIRC_BBUF_DEF(cb_UTX, 40);
CIRC_BBUF_DEF(cb_URX, 120);
CIRC_BBUF_int_DEF(cb_x, 10);
CIRC_BBUF_int_DEF(cb_t, 10);

parser_state pstate;
robot_data robot;

int parse_st;
int command;
int command_counter=0;
char buff[40];

void __attribute__((__interrupt__,__auto_psv__)) _U2TXInterrupt(void){
    IFS1bits.U2TXIF = 0;        // clear TX interrupt flag
    UART_TX_CB(&cb_UTX);
}   
void __attribute__((__interrupt__,__auto_psv__)) _U2RXInterrupt(void){
    IEC1bits.U2TXIE = 0;
    while (U2STAbits.URXDA == 1){
        char d =  U2RXREG;
        circ_bbuf_push(&cb_URX,d);
        circ_bbuf_push(&cb_UTX,d);
  
    }
    IFS1bits.U2RXIF = 0;        //Clear the UART1 transmitter interrupt flag
    IEC1bits.U2TXIE = 1;
}

void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(){
    
    T2CONbits.TON = 0; // stop timer2
    IFS0bits.T2IF = 0; // reset timer2 interrupt flag
    TMR2 = 0x00;       // reset timer2
    if (PORTEbits.RE8 == 0x01)
    {
        robot.state = !robot.state; // Change the state of the robot
        if(robot.state == 0){
            command_counter=0;
            motor(0,0);
            robot.t = 0;
            cb_t.dataCounter=0;
            cb_x.dataCounter=0;
        }
    }
    IEC0bits.T2IE = 0x00; // disable timer2 interrupt
}
void task_button(){
    
    if (PORTEbits.RE8 == 0)
    {
        tmr_setup_period(TIMER2, 20);
        IEC0bits.T2IE = 1;
        T2CONbits.TON = 1;          // Start Timer
    }
}
void task_control_loop(){
    UART_TX_CB(&cb_UTX);
    if(cb_URX.dataCounter){
        uint8_t stx;
        circ_bbuf_pop(&cb_URX,&stx);
        int ret11 = parse_byte(&pstate,stx);
        if (ret11 == NEW_MESSAGE){
            if (strcmp(pstate.msg_type, "PCCMD") == 0){
                if(command_counter<10){
                    command_counter++;
                    command = extract_integer(pstate.msg_payload);
                    circ_bbuf_int_push(&cb_x,command);
                    int i = next_value(pstate.msg_payload, 0);
                    command = extract_integer(pstate.msg_payload + i);
                    circ_bbuf_int_push(&cb_t,command);
                    sprintf(buff, "$MACK,%d*" , command_counter);
                    for(int i=0;buff[i]!='\0';i++){
                        circ_bbuf_push(&cb_UTX,buff[i]);
                    } 
                }
                else{
                    sprintf(buff, "$MACK,0*");
                    for(int i=0;buff[i]!='\0';i++){
                        circ_bbuf_push(&cb_UTX,buff[i]);
                    }
                }
                UART_TX_CB(&cb_UTX);
            }
        }
    }
    if(robot.state){
        if(command_counter){
                    UART_TX_CB(&cb_UTX);
                    if(robot.t == 0){
                        int by;
                        circ_bbuf_int_pop(&cb_t,&by);
                        robot.t = by;
                        circ_bbuf_int_pop(&cb_x,&by);
                        robot.x = by;
                        command_counter--;
                    }            
        }
    }
    if(robot.t){
        if(robot.x==1){
            if(robot.obstacle==0){motor(100,100);}
            else{motor(0,0);}
        }
        if(robot.x==2){motor(-100,100);}
        if(robot.x==3){motor(100,-100);}
        if(robot.x==4){motor(-100,-100);}
        robot.t--; 
    }
    else{
        motor(0,0);
    }
}
void obstacle_avoide(){
    double ob_dist = read_IR();
    if(ob_dist<20){
        robot.obstacle = 1;
    }
    else{
        robot.obstacle = 0;
    }
}
void indication(){
    if(robot.state){
       LATAbits.LATA0 = ~LATAbits.LATA0;
       LATFbits.LATF1 = 0;
       LATBbits.LATB8 = 0;
    }
    else{
       LATBbits.LATB8 = ~LATBbits.LATB8;
       LATFbits.LATF1 = ~LATFbits.LATF1;
       LATAbits.LATA0 = ~LATAbits.LATA0;  
    }
    
}
void log_batt(){
        sprintf(buff, "$MBAT,%.2f*" ,read_batt());
        IEC1bits.U2TXIE = 0;        // Disable UART2 TX Interrupt
        for(int i=0;buff[i]!='\0';i++){
            circ_bbuf_push(&cb_UTX,buff[i]);
        }
        circ_bbuf_push(&cb_UTX,0x0A);
        IEC1bits.U2TXIE = 1;        // Enable UART2 TX Interrupt
        UART_TX_CB(&cb_UTX);
}
void log_IR(){
        sprintf(buff, "&MDIST,%.1f*" ,read_IR());
        IEC1bits.U2TXIE = 0;        // Disable UART2 TX Interrupt
        for(int i=0;buff[i]!='\0';i++){
            circ_bbuf_push(&cb_UTX,buff[i]);
        }
        IEC1bits.U2TXIE = 1;        // Enable UART2 TX Interrupt
        UART_TX_CB(&cb_UTX);
}
int main(void) {
    ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;
    // LED output pins
    TRISAbits.TRISA0 = 0;       // LED1
    TRISGbits.TRISG9 = 0;       // LED2
    TRISEbits.TRISE8 = 1;       // State changer button
    TRISBbits.TRISB8 = 0;       // Left
    TRISFbits.TRISF1 = 0;       // Right
    
    ADC_Init();
    PWM_Init();
    UART_Init();
    parser_Init(&pstate);

    robot.state = 0;
    robot.t = 0;
    robot.x = 0;
    robot.obstacle = 0;
    
    // scheduler configuration
    heartbeat schedInfo[MAX_TASKS];
    
    schedInfo[0].n = 0;
    schedInfo[0].N = 1;
    schedInfo[0].f = task_button;
    schedInfo[0].enable = 1;
    
    schedInfo[1].n = 0;
    schedInfo[1].N = 1;
    schedInfo[1].f = task_control_loop;
    schedInfo[1].enable = 1;
    
    schedInfo[2].n = 0;
    schedInfo[2].N = 1;
    schedInfo[2].f = obstacle_avoide;
    schedInfo[2].enable = 1;
    
    schedInfo[3].n = 0;
    schedInfo[3].N = 1000;
    schedInfo[3].f = indication;
    schedInfo[3].enable = 1;
/*     
    schedInfo[4].n = 0;
    schedInfo[4].N = 1000;
    schedInfo[4].f = log_batt;
    schedInfo[4].enable = 1;
  
    schedInfo[5].n = 0;
    schedInfo[5].N = 100;
    schedInfo[5].f = log_IR;
    schedInfo[5].enable = 1;
*/        
    tmr_setup_period(TIMER1,1);
    while(1){
        scheduler(schedInfo, MAX_TASKS);
        tmr_wait_period(TIMER1);
    }
    return 0;
}
