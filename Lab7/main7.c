//
//  New lab 7.c
//  
//
//  Created by Alan Whitehead on 3/22/24.
//


#define _RESET 1
#define _PART1 0
#define _PART2 0
#define _PART3 0

#include "Timer.h"
#include "lcd.h"
#include "uart.h"
#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "movement.h"
#include "cyBot_Scan.h"
#include <math.h>
#include "open_interface.h"

//#include "bumperMovement.h"

#define PI 3.14159265


//#if _RESET
//#include "Simulation_User Files_resetSimulation.h"
//#endif

// Adding global volatile varibles for communcating between
// your Interupt Service Routine, and your non-interupt code.


void main()
{
    timer_init();
    lcd_init();

    uart_init();

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data); // should turn the iRobot Create's "Dirt Detect" LED to blue
    cyBOT_init_Scan(0b0111);
//    cyBOT_SERVO_cal();
    right_calibration_value = 285250;
    left_calibration_value = 1309000;

    uart_interrupt_init();
    oi_free(sensor_data);

// YOUR CODE HERE
char forward[] = "Move forward";
char backward[] = "Move backward";
char left[] = "Turn left";
char right[] = "Turn right";


int i;
int loop = 1;
int ran0 = 0;
while(loop)
{
    int command = uart_receive();
    lcd_clear();
    if(command == 'w'){
        oi_setWheels(100, 100);
        for(i = 0; i<strlen(forward); i++){
            uart_sendChar(forward[i]);
        }
        oi_moveForward(sensor_data, 2);
        lcd_printf("%s", "Move Forward");
        oi_setWheels(0, 0);
    }
    else if(command == 's'){
        oi_setWheels(-100,-100);
        for(i = 0; i<strlen(backward); i++){
            uart_sendChar(backward[i]);
        }
        oi_moveBackward(sensor_data, -2);
        lcd_printf("%s", "Move Backward");
        oi_setWheels(0, 0);

    }
    else if(command == 'a'){
        oi_setWheels(50, -50);
        for(i = 0; i<strlen(left); i++){
            uart_sendChar(left[i]);
        }

        oi_turnCounterClockwise(sensor_data, 5);

        lcd_printf("%s", "Turn left");
        oi_setWheels(0, 0);
        command = '\0';
    }
    else if(command == 'd'){
        oi_setWheels(-50, 50);
        for(i = 0; i<strlen(right); i++){
            uart_sendChar(right[i]);
        }

        oi_turnClockwise(sensor_data, -5);
        lcd_printf("%s", "Turn right");
        oi_setWheels(0, 0);
        command = '\0';
    }

    else if(command == 'n'){
        int i, j, x;
        int k = 1;
        cyBOT_Scan_t scan;

        char partTwoF[] = "Degrees";
        char partTwoF1[] = "Distance (cm)";
        char partTwoF2[] = "IR Distance";

        char format[] = "Object#";
        char format1[] = "Angle";
        char format2[] = "Distance";
        char format3[] = "Width";
        int min = 0;
        int minAngle = 0;
        int minAngleDist = 0;
        int minActualWidth = 0;
        int flag = 0;

        cyBOT_Scan(0, &scan);


        for(i = 0; i<strlen(format); i++){
            uart_sendChar(format[i]);
        }

        for(i = 0; i<4; i++){
            uart_sendChar(' ');
        }

        for(i = 0; i<strlen(format1); i++){
            uart_sendChar(format1[i]);
        }

        for(i = 0; i<8; i++){
            uart_sendChar(' ');
        }

        for(i = 0; i<strlen(format2); i++){
            uart_sendChar(format2[i]);
        }

        for(i = 0; i<4; i++){
            uart_sendChar(' ');
        }

        for(i = 0; i<strlen(format3); i++){
            uart_sendChar(format3[i]);
        }

        uart_sendChar('\r');
        uart_sendChar('\n');

        //Object detection
        for(i = ran0; i<=180; i++){
            if(uart_event == 1 && uart_typed == 't'){
                minAngle = i;
                flag = 1;
                break;
            }
            cyBOT_Scan(i, &scan);
            float soundDist = 0;
            int rawVal = 0;
            int begin = 0;
            int end = 0;
            int count = 0;
            int width = 0;


            if(scan.IR_raw_val >= 900){
                begin = i;
                soundDist = scan.sound_dist;
                rawVal = scan.IR_raw_val;
                for(j = i+1; j<=180; j++){
                    count++;
                    cyBOT_Scan(j, &scan);
                    if(scan.IR_raw_val <900){
                        end = j;
                        width = end - begin;
                        i = i + count;

                        float converter = soundDist/rawVal;
                        int cm = rawVal*converter;
                        char obj[3];
                        char deg[3];
                        char dist[3];
                        char wid[3];

                        char tempStr[20] = "\0";

                        if(width > 4){
                            sprintf(obj, "%d", k);
                            for(x = 0; x<strlen(obj); x++){
                                uart_sendChar(obj[x]);
                            }
                            sprintf(tempStr, "Object %d: %d, %dcm ", k, rawVal, cm);

                            lcd_puts(tempStr);
                            k++;

                            for(x = 0; x<11; x++){
                                uart_sendChar(' ');
                            }

                            sprintf(deg, "%d", begin);
                            for(x = 0; x<strlen(deg); x++){
                                uart_sendChar(deg[x]);
                            }

                            for(x = 0; x<13; x++){
                                uart_sendChar(' ');
                            }



                            sprintf(dist, "%d cm", cm);
                            for(x=0; x<strlen(dist); x++){
                                uart_sendChar(dist[x]);
                            }

                            for(x = 0; x<11; x++){
                                uart_sendChar(' ');
                            }

                            sprintf(wid, "%d", width);
                            for(x = 0; x<strlen(wid); x++){
                                uart_sendChar(wid[x]);
                            }

                            uart_sendChar('\r');
                            uart_sendChar('\n');


                            minActualWidth = soundDist*sin((width/2)*(PI/180));   // soundDist*

                            if(min == 0){
                                min = minActualWidth;
                                minAngle = begin + (width/2);
                                minAngleDist = soundDist;
                            }
                            else if(min>minActualWidth){
                                min = minActualWidth;
                                minAngle = begin + (width/2);
                                minAngleDist = soundDist;
                            }
                        }

                        break;
                    }
                }
            }
        }
        
        
        /// atonomous
        cyBOT_Scan(minAngle, &scan);
//            float converter = scan.sound_dist/scan.IR_raw_val;
//            int cm = scan.IR_raw_val*converter;
        float centerDist = scan.sound_dist;
        lcd_printf("%d", minAngleDist);
        char skinObjFormat[] = "The skinniest object angle: ";
        for(i = 0; i< strlen(skinObjFormat); i++){
            uart_sendChar(skinObjFormat[i]);
        }
        char minAngleArr[3];
        sprintf(minAngleArr, "%d", minAngle);

        for(i = 0; i< strlen(minAngleArr); i++){
            uart_sendChar(minAngleArr[i]);
        }

        uart_sendChar('\r');
        uart_sendChar('\n');

        if(flag != 1){
        int turnToAngle = minAngle - 90;

        if(turnToAngle < 0){
            turnToAngle = (-1)*minAngle;
            timer_waitMillis(1);
            oi_setWheels(-50, 50);
            timer_waitMillis(1);
            oi_turnClockwise(sensor_data, (float) turnToAngle/1.3);
            oi_setWheels(0,0);
            lcd_printf("SOMething 1");


        }
        else if(turnToAngle > 0){
            turnToAngle = abs(turnToAngle);
            timer_waitMillis(1);
            oi_setWheels(50, -50);
            timer_waitMillis(1);
            oi_turnCounterClockwise(sensor_data, (float) turnToAngle/1.3);
            timer_waitMillis(1);
            oi_setWheels(0,0);
            lcd_printf("SOMething 2");


       }


            cyBOT_Scan(90, &scan);
            timer_waitMillis(1);
            oi_setWheels(100,100);
            oi_moveForward(sensor_data, (minAngleDist - 13));
            oi_setWheels(0,0);
       }

        ran0 = 0;

    }

    else if(command == 'm'){
        int i, j, x;
        int k = 1;
        cyBOT_Scan_t scan;

        char partTwoF[] = "Degrees";
        char partTwoF1[] = "Distance (cm)";
        char partTwoF2[] = "IR Distance";

        cyBOT_Scan(0, &scan);


        for(i = 0; i<strlen(partTwoF); i++){
            uart_sendChar(partTwoF[i]);
        }

        for(j = 0; j<8; j++){
            uart_sendChar(' ');
        }

        for(i = 0; i<strlen(partTwoF1); i++){
            uart_sendChar(partTwoF1[i]);
        }

        for(j = 0; j<8; j++){
            uart_sendChar(' ');
        }

        for(i = 0; i<strlen(partTwoF2); i++){
            uart_sendChar(partTwoF2[i]);
        }
        uart_sendChar('\r');
        uart_sendChar('\n');

        for(i = 0; i<=180; i++){
            if(uart_event == 1 & uart_typed == 't'){
                break;
            }
            cyBOT_Scan(i, &scan);
            char c[3];
            char c1[3];
            char c2[3];

            sprintf(c, "%d", i);
            for(j = 0; j<strlen(c); j++){
                uart_sendChar(c[j]);
            }

            for(j = 0; j<14; j++){
                uart_sendChar(' ');
            }

            sprintf(c1, "%f", scan.sound_dist);
            for(j = 0; j<strlen(c1); j++){
                uart_sendChar(c1[j]);
            }

            for(j = 0; j<14; j++){
                uart_sendChar(' ');
            }

            sprintf(c2, "%d", scan.IR_raw_val);
            for(j = 0; j<strlen(c2); j++){
                uart_sendChar(c2[j]);
            }
            uart_sendChar('\r');
            uart_sendChar('\n');
        }
    }

    else{
        loop = 0;
    }

    uart_sendChar('\r');
    uart_sendChar('\n');


}

oi_free(sensor_data);

}
