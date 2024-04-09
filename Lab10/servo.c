/*
 * servo.c
 *
 *  Created on: Apr 1, 2024
 *      Author: ctrinkle
 */

#include "lcd.h"
#include "servo.h"
#include "Timer.h"
#include <math.h>
#include "driverlib/interrupt.h"
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"
volatile unsigned long START_TIME = 0;
volatile unsigned long END_TIME = 0;
volatile enum{LOW, HIGH, DONE} STATE;

void servo_init(){
    SYSCTL_RCGCGPIO_R |= 0b000010;

    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_PCTL_R |= 0x700000;

    GPIO_PORTB_DEN_R |= 0x20;
    GPIO_PORTB_DIR_R |= 0x20;

    SYSCTL_RCGCTIMER_R |= 0x2;

    TIMER1_CTL_R &= ~(0x0100);
    TIMER1_CFG_R |= 0x4;

    TIMER1_TBMR_R |= 0xA;
    TIMER1_TBMR_R &= ~(0x4);

    TIMER1_CTL_R &= 0XBFFF;

    TIMER1_TBILR_R |= (320000 & 0xFFFF);

    TIMER1_TBPR_R |= (320000 >> 16);

    pulse_width = 0;

    servo_move(pulse_width);

    TIMER1_TBMATCHR_R |= ((32000 - pulse_width) & 0xFFFF);

    TIMER1_TBPMR_R |= ((32000 - pulse_width) >> 16);

    TIMER1_CTL_R |= 0x0100;

}

void servo_move(float degrees){

    float ratio = 28500/180;
    pulse_width = ratio*degrees;

    TIMER1_TBMATCHR_R = ((320000 - pulse_width) & 0xFFFF);

    TIMER1_TBPMR_R = ((320000 - pulse_width) >> 16);

    timer_waitMillis(50);
}
