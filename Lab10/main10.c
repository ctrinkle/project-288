/*
 * main10.c
 *
 *  Created on: Apr 1, 2024
 *      Author: ctrinkle
 */

#include "Timer.h"
#include "lcd.h"
#include "adc.h"
#include "uart.h"
//#include "ping_template.h"
#include "movement.h"
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "cyBot_Scan.h"
#include "lcd.h"
#include "servo.h"

#define PI 3.14159265359


void main(){

    timer_init();
    lcd_init();
    adc_init();
   //uart_interrupt_init();
    //ping_init();
    servo_init();
   // button_init();
    int positions[] = {90, 30, 150, 90};
    int size = 4;

    int i = 0;
    for(i = 0; i < size; i++ ){
        servo_move((float)positions[i]);
        timer_waitMillis(500);
    }

    while(1){
        // hold
    }


}
