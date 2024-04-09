

/**
 * main.c
 */


#include "Timer.h"
#include <stdlib.h>
#include "lcd.h"
#include "open_interface.h"
#include "cyBot_Scan.h"
#include "cyBot_uart.h"
#include <stdio.h>
#include "movement.h"
#include <math.h>
//#include "uart-interrupt.h"
#include "uart.h"
#include "adc.h"


#define PI 3.14159265


int main(void){

    timer_init();
    lcd_init();
    uart_init();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    cyBOT_init_Scan(0b0111);
    //cyBOT_SERVO_cal();
    oi_free(sensor_data);
    uart_interrupt_init();
    right_calibration_value = 285250;
    left_calibration_value = 1309000;


    timer_waitMillis(1);
    cyBOT_Scan_t scan;
    cyBOT_Scan(90, &scan);

    int adcRead = adc_read();
    float converter = scan.sound_dist/adcRead;
    int cm = adcRead*converter;
    char str[20];
    sprintf(str, "IR: %d, Dist: %dcm", adcRead, cm);
    lcd_printf("%s", str);




}
