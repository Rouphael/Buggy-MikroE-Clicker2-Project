/* 
 * File:   ADC.c
 * Author: Rafael
 */

#include "xc.h"
#include "math.h"

void ADC_Init(void){
    // IR Sensor analog configuration AN15
    TRISBbits.TRISB15 = 1;
    ANSELBbits.ANSB15 = 1;
    // Battery sensing analog configuration AN11
    TRISBbits.TRISB11 = 1;
    ANSELBbits.ANSB11 = 1;
    AD1CON3bits.ADCS = 14;  // 14*T_CY
    AD1CON1bits.ASAM = 1;   // automatic sampling start
    AD1CON1bits.SSRC = 7;   // automatic conversion
    AD1CON3bits.SAMC = 16;  // sampling lasts 16 Tad
    AD1CON2bits.CHPS = 0;   // use CH0 2-channels sequential sampling mode
    AD1CON1bits.SIMSAM = 0; // sequential sampling
    // Scan mode specific configuration
    AD1CON2bits.CSCNA = 1; // scan mode enabled
    AD1CSSLbits.CSS11 = 1; // scan for AN11 battery
    AD1CSSLbits.CSS15 = 1; // scan for AN15 ir sensor
    AD1CON2bits.SMPI = 1;  // N-1 channels
    AD1CON1bits.ADON = 1;  // turn on ADC
    // IR distance sensor enable line
    TRISAbits.TRISA3 = 0;
    LATAbits.LATA3 = 1;
}

double read_batt(){
        while(!AD1CON1bits.DONE); // Wait for ADC conversion to finish
        double Data = ADC1BUF0;
        // calculate the battery voltage based on the resistor divider
        double R4951 = 200, R54 = 100;
        double v_batt = (Data / 1024.0) * 3.7;
        v_batt = v_batt * (R4951 + R54) / R54;
        
        return v_batt;
}
double read_IR(){
        while(!AD1CON1bits.DONE); // Wait for ADC conversion to finish
        // Read from sensor
        double read_value = ADC1BUF1;
        double volts = (read_value / 1024.0) * 3.3;
        double distance = 0;
        distance = 2.34 - (4.74 * volts) + (4.06 * pow(volts,2)) - (1.60 * pow(volts,3)) + (0.24 * pow(volts,4)); // Distance in m, polynomial fit
        distance = distance * 100; //cm
        return distance;
    
}
