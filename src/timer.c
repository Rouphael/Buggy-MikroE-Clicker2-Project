/* 
 * File:   timer.c
 * Author: Rafael
 */


#include "xc.h"
#include "timer.h"
        
int prescaler(int ms, int* pr, int* tckps) {
    long tfms = 72000L * ms; //72000 ticks are needed for 1 millisecond
    long scaled_ticks = tfms;
    // pre-scaler 1:1
    if (scaled_ticks <= 65535) {
        *tckps = 0;
        *pr = scaled_ticks;
        return 0;
    }
    // pre-scaler 1:8
    scaled_ticks = tfms / 8;
    if (scaled_ticks <= 65535) {
        *tckps = 1;
        *pr = scaled_ticks;
        return 0;
    }
    // pre-scaler 1:64
    scaled_ticks = tfms / 64;
    if (scaled_ticks <= 65535) {
        *tckps = 2;
        *pr = scaled_ticks;
        return 0;
    }
    // pre-scaler 1:256
    scaled_ticks = tfms / 256;
    if (scaled_ticks <= 65535) {
        *tckps = 3;
        *pr = scaled_ticks;
        return 0;
    }
    return 1;
}
void tmr_setup_period(int timer, int ms) {
    int pr, tckps;
    prescaler(ms, &pr, &tckps);
    switch (timer) {
        case TIMER1:
            T1CONbits.TON = 0;          // Disable Timer
            T1CONbits.TCS = 0;          // Select internal instruction cycle clock
            T1CONbits.TGATE = 0;        // Disable Gated Timer mode
            T1CONbits.TCKPS = tckps;    // Select Pre-scaler
            TMR1 = 0x00;                // Clear timer register
            PR1 = pr;                   // Load the period value
            
            //IPC0bits.T1IP = 0x01;     // Set Timer1 Interrupt Priority Level
            IFS0bits.T1IF = 0;          // Clear Timer1 Interrupt Flag
            //IEC0bits.T1IE = 1;        // Enable Timer1 interrupt
            
            T1CONbits.TON = 1;          // Start Timer
            break;
                        
        case TIMER2:
            T2CONbits.TON = 0;          // Disable Timer
            T2CONbits.TCS = 0;          // Select internal instruction cycle clock
            T2CONbits.TGATE = 0;        // Disable Gated Timer mode
            T2CONbits.TCKPS = tckps;    // Select Pre-scaler
            TMR2 = 0x00;                // Clear timer register
            PR2 = pr;                   // Load the period value
            
            //IPC1bits.T2IP = 0x01;     // Set Timer2 Interrupt Priority Level
            IFS0bits.T2IF = 0;          // Clear Timer2 Interrupt Flag
            //IEC0bits.T2IE = 1;        // Enable Timer2 interrupt
            
            //T2CONbits.TON = 1;          // Start Timer
            break;
                        
        case TIMER3:
            T3CONbits.TON = 0;          // Disable Timer
            T3CONbits.TCS = 0;          // Select internal instruction cycle clock
            T3CONbits.TGATE = 0;        // Disable Gated Timer mode
            T3CONbits.TCKPS = tckps;    // Select Pre-scaler
            TMR3 = 0x00;                // Clear timer register
            PR3 = pr;                   // Load the period value
            
            //IPC2bits.T3IP = 0x01;     // Set Timer3 Interrupt Priority Level
            IFS0bits.T3IF = 0;          // Clear Timer3 Interrupt Flag
            //IEC0bits.T3IE = 1;        // Enable Timer3 interrupt
            
            T3CONbits.TON = 1;          // Start Timer
            break;
                    
        case TIMER4:
            T4CONbits.TON = 0;          // Disable Timer
            T4CONbits.TCS = 0;          // Select internal instruction cycle clock
            T4CONbits.TGATE = 0;        // Disable Gated Timer mode
            T4CONbits.TCKPS = tckps;    // Select Pre-scaler
            TMR4 = 0x00;                // Clear timer register
            PR4 = pr;                   // Load the period value
            
            //IPC6bits.T4IP = 0x01;     // Set Timer4 Interrupt Priority Level
            IFS1bits.T4IF = 0;          // Clear Timer4 Interrupt Flag
            //IEC1bits.T4IE = 1;        // Enable Timer4 interrupt
            
            T4CONbits.TON = 1;          // Start Timer
            break;
    }
}
int tmr_wait_period(int timer) {
    switch (timer) {
        case TIMER1:
            if(IFS0bits.T1IF){
                IFS0bits.T1IF = 0;
                return 1;
            }
            else{
                while(!IFS0bits.T1IF);
                IFS0bits.T1IF = 0;
            }
            break;
        case TIMER2:
            if(IFS0bits.T2IF){
                IFS0bits.T2IF = 0;
                return 1;
            }
            else{
                while(!IFS0bits.T2IF);
                IFS0bits.T2IF = 0;
            }
            break;
        case TIMER3:
            if(IFS0bits.T3IF){
                IFS0bits.T3IF = 0;
                return 1;
            }
            else{
                while(!IFS0bits.T3IF);
                IFS0bits.T3IF = 0;
            }
            break;
        case TIMER4:
            if(IFS1bits.T4IF){
                IFS1bits.T4IF = 0;
                return 1;
            }
            else{
                while(!IFS1bits.T4IF);
                IFS1bits.T4IF = 0;
            }
            break;
    }
    return 0;
}
void tmr_wait_ms(int timer, int ms) {
 
    int dcnt = ms/200;
    int rcnt = ms%200;
    
    while(dcnt){
        tmr_setup_period(timer,200);
        tmr_wait_period(timer);
        dcnt--;
    }
    if(rcnt){
    tmr_setup_period(timer,rcnt);
    tmr_wait_period(timer);
    }
    switch(timer){
        case TIMER1:
            T1CONbits.TON = 0; // Turn off the timer!
            break;
        case TIMER2:
            T2CONbits.TON = 0; // Turn off the timer!
            break;
        case TIMER3:
            T3CONbits.TON = 0; // Turn off the timer!
            break;
        case TIMER4:
            T4CONbits.TON = 0; // Turn off the timer!
            break;
    }
}    