/**
 * Driver for ping sensor
 * @file ping.c
 * @author
 */

#include "ping_template.h"
#include "Timer.h"
#include <math.h>
#include "driverlib/interrupt.h"
volatile unsigned long START_TIME = 0;
volatile unsigned long END_TIME = 0;
volatile enum{LOW, HIGH, DONE} STATE = LOW; // State of ping echo pulse
#define MICROS_PER_TICK 64999UL
int overflow = 0;

void ping_init (void){

  // YOUR CODE HERE


    SYSCTL_RCGCGPIO_R |= 0b000010;
    while((SYSCTL_PRGPIO_R & 0x02) == 0){};
    GPIO_PORTB_DEN_R |= 0x08;
    GPIO_PORTB_DIR_R &= ~0x08;
    GPIO_PORTB_AFSEL_R |= 0x08;
    GPIO_PORTB_PCTL_R &= 0xFFFF0FFF;
    GPIO_PORTB_PCTL_R |= 0x00007000;

    SYSCTL_RCGCTIMER_R |= 0x08;
    // Configure and enable the timer
    while(SYSCTL_RCGCTIMER_R & 0x08 == 0){};
    TIMER3_CTL_R &= ~0x100;
    TIMER3_CFG_R = 0x04;
    TIMER3_TBMR_R |= 0x07;
    TIMER3_TBMR_R &= ~0x10;
    TIMER3_TBILR_R |= 0xFFFF;
    TIMER3_ICR_R |= 0x400;
    TIMER3_TBPR_R = 0xFF;
    TIMER3_IMR_R |= 0x400;

    NVIC_EN1_R |= 0x10;
    NVIC_PRI9_R |= 0x20;

    IntRegister(INT_TIMER3B, TIMER3B_Handler);
    IntMasterEnable();

    TIMER3_CTL_R |= 0x0C00;
    TIMER3_CTL_R |= 0x0100;
}

void ping_trigger (void){
    STATE = LOW;
    TIMER3_CTL_R &= ~0x100;
    TIMER3_IMR_R &= ~0x400;

    //ping_sendPulse();
    GPIO_PORTB_DIR_R |= 0x08;
    GPIO_PORTB_AFSEL_R &= ~0x08;

    GPIO_PORTB_DATA_R &= ~0x08;
    GPIO_PORTB_DATA_R |= 0x08;
    STATE = HIGH;
    timer_waitMicros(10);
    GPIO_PORTB_DATA_R &= ~0x08;
    STATE = DONE;

    TIMER3_ICR_R |= 0x400;

    GPIO_PORTB_AFSEL_R |= 0x08;
    TIMER3_IMR_R |= 0x400;
    TIMER3_CTL_R |= 0x100;

//    TIMER3_CTL_R |= 0xD00;
//
//
//    while(STATE != DONE);
//
//    int change_time = START_TIME - END_TIME;
//    return (change_time);

}

//void ping_sendPulse(void){
//
//   GPIO_PORTB_AFSEL_R &= ~(0x08);
//   GPIO_PORTB_PCTL_R &= ~(0x0000F000);
//   GPIO_PORTB_DIR_R |= 0x08;
//   GPIO_PORTB_DATA_R |= 0x08;
//   timer_waitMicros(5);
//   GPIO_PORTB_DATA_R &= 0xF7;
//   GPIO_PORTB_DIR_R &= 0xF7;
//   GPIO_PORTB_AFSEL_R |= 0x08;
//   GPIO_PORTB_PCTL_R |= 0x00007000;
//
//   TIMER3_ICR_R |= 0xFFFFF;
//   TIMER3_IMR_R = 0x400;
//
//
//}


void TIMER3B_Handler(void)
{

    // YOUR CODE HERE
    // As needed, go back to review your interrupt handler code for the UART lab.
    // What are the first lines of code in the ISR? Regardless of the device, interrupt handling
    // includes checking the source of the interrupt and clearing the interrupt status bit.
    // Checking the source: test the MIS bit in the MIS register (is the ISR executing
    // because the input capture event happened and interrupts were enabled for that event?
    // Clearing the interrupt: set the ICR bit (so that same event doesn't trigger another interrupt)
    // The rest of the code in the ISR depends on actions needed when the event happens.

    if (TIMER3_MIS_R &= 0x400)
    {
        TIMER3_ICR_R |= 0x400;
        if (STATE == LOW)
        {
            START_TIME = TIMER3_TBR_R;
            STATE = HIGH;
        }
        else
        {
            END_TIME = TIMER3_TBR_R;
            //STATE = LOW;
            STATE = DONE;
        }
        //TIMER3_ICR_R |= 0xFFFFF;
    }
}


float ping_getDistance (void){

   ping_trigger();
    while(STATE != DONE);
        STATE = LOW;
        float dist = 0;

        if(END_TIME > START_TIME){
            overflow++;
            dist = (START_TIME - END_TIME + 0xFFFFFF) * 0.5 * 343 * 0.00000625;
        }
        else{
            dist = (START_TIME - END_TIME) * 0.5 * 343 * 0.00000625;
        }

        return dist;
    }



