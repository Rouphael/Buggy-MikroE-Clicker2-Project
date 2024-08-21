/* 
 * File:   motor.c
 * Author: Rafael
 */

#include "xc.h"
#include "motor.h"

void PWM_Init(void){
    // Configure the pins
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    TRISDbits.TRISD4 = 0;
    // Remap the pins
    RPOR0bits.RP65R = 0b010000; // OC1
    RPOR1bits.RP66R = 0b010001; // OC2
    RPOR1bits.RP67R = 0b010010; // OC3
    RPOR2bits.RP68R = 0b010011; // OC4
    
    // Configure the Left Wheels
    // Clear all the contents of two control registers
    OC1CON1 = 0x0000;
    OC1CON2 = 0x0000;
    // Set the peripheral clock as source for the OCx module
    OC1CON1bits.OCTSEL = 0b111;
    // Sets the OC modality to Edge-Aligned PWM mode
    OC1CON1bits.OCM = 0b110;
    // Sets the synchronization source for the OCx module to No Sync
    OC1CON2bits.SYNCSEL = 0x1F;
    // Clear all the contents of two control registers
    OC2CON1 = 0x0000;
    OC2CON2 = 0x0000;
    // Set the peripheral clock as source for the OCx module
    OC2CON1bits.OCTSEL = 0b111;
    // Sets the OC modality to Edge-Aligned PWM mode
    OC2CON1bits.OCM = 0b110;
    // Sets the synchronization source for the OCx module to No Sync
    OC2CON2bits.SYNCSEL = 0x1F;
    // Configure the Right Wheels
    // Clear all the contents of two control registers
    OC3CON1 = 0x0000;
    OC3CON2 = 0x0000;
    // Set the peripheral clock as source for the OCx module
    OC3CON1bits.OCTSEL = 0b111;
    // Sets the OC modality to Edge-Aligned PWM mode
    OC3CON1bits.OCM = 0b110;
    // Sets the synchronization source for the OCx module to No Sync
    OC3CON2bits.SYNCSEL = 0x1F;
    // Clear all the contents of two control registers
    OC4CON1 = 0x0000;
    OC4CON2 = 0x0000;
    // Set the peripheral clock as source for the OCx module
    OC4CON1bits.OCTSEL = 0b111;
    // Sets the OC modality to Edge-Aligned PWM mode
    OC4CON1bits.OCM = 0b110;
    // Sets the synchronization source for the OCx module to No Sync
    OC4CON2bits.SYNCSEL = 0x1F;
    
    OC1RS = OCxRS; // Set the PWM frequency
    OC2RS = OCxRS; // Set the PWM frequency
    OC3RS = OCxRS; // Set the PWM frequency
    OC4RS = OCxRS; // Set the PWM frequency
    
    OC1R = 0;       //set duty cycle to 0
    OC2R = 0;       //set duty cycle to 0
    OC3R = 0;       //set duty cycle to 0
    OC4R = 0;       //set duty cycle to 0
}

void motor(int left_pwm,int right_pwm){
    if(left_pwm >= 0){
        OC1R = (OCxRS/100) * 0;
        OC2R = (OCxRS/100) * left_pwm;
    }
    else{
        OC1R = (OCxRS/100) * -left_pwm;
        OC2R = (OCxRS/100) * 0;
    }
    if(right_pwm >= 0){
        OC3R = (OCxRS/100) * 0;
        OC4R = (OCxRS/100) * right_pwm;
    }
    else{
        OC3R = (OCxRS/100) * -right_pwm;
        OC4R = (OCxRS/100) * 0;
    }
}
