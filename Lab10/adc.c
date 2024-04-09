/*
 * adc.c
 *
 *  Created on: Mar 19, 2024
 *      Author: ctrinkle
 */


#include "adc.h"
#include "Timer.h"
#include <stdint.h>
#include <stdbool.h>
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

    void adc_init(void){
        SYSCTL_RCGCGPIO_R |= 0x2;
        SYSCTL_RCGCADC_R |= 0x1;
        // 1) activate ADC0
         // 2) activate clock for Port B
        //while((SYSCTL_PRGPIO_R&0x10) != 0x10){}; // 3 for stabilization
      //  GPIO_PORTB_DIR_R &= ~0x10; // 4) make PE4 input
        GPIO_PORTB_AFSEL_R |= 0x10; // 5) enable alternate function on PE4
        GPIO_PORTB_DEN_R &= ~0x10; // 6) disable digital I/O on PE4
        GPIO_PORTB_AMSEL_R |= 0x10; // 7) enable analog functionality on PE4
        // while((SYSCTL_PRADC_R&0x0001) != 0x0001){}; // good code, but not implemented in simulator
      //  ADC0_PC_R &= ~0xF;
       // ADC0_PC_R |= 0x1; // 8) configure for 125K samples/sec
      // ADC0_SSPRI_R = 0x0123; // 9) Sequencer 3 is highest priority
        ADC0_ACTSS_R &= ~0x1; // 10) disable sample sequencer 3
        ADC0_EMUX_R = 0x0; // 11) seq3 is software trigger
        ADC0_SSMUX0_R |= 0xA;
       // ADC0_SSMUX3_R += 9; // 12) set channel
        ADC0_SSCTL0_R |= 0x6; // 13) no TS0 D0, yes IE0 END0
        ADC0_SAC_R = 0x4;
        ADC0_PSSI_R |= 0x1;
        //ADC0_IM_R &= ~0x0008; // 14) disable SS3 interrupts
        ADC0_ACTSS_R |= 0x01; // 15) enable SS0
    }

    int adc_read(void){

   //     uint32_t result;

        ADC0_PSSI_R = ADC_PSSI_SS0; // 1) initiate SS0
        while((ADC0_RIS_R & 0x01)==0){

        } // 2) wait for
        //conversion done
     //   result = ADC0_SSFIFO0_R & 0xFFF; // 3) read
       // result
        ADC0_ISC_R = ADC_RIS_INR0; // 4)
       // acknowledge completion
        return ADC0_SSFIFO0_R;

    }


