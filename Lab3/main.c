

/**
 * main.c
 */


#include "Timer.h"
#include <stdlib.h>
#include "lcd.h"
#include "open_interface.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include <stdio.h>
//#include "movement.h"
#include <math.h>

#define PI 3.14159265


int main(void){
// part 1

//    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
//    oi_init(sensor_data);
//    lcd_init();
//    cyBot_uart_init();
//    timer_init();
//  //  cyBOT_init_Scan();
//
//    while(1){
//        int B = cyBot_getByte();
//        cyBot_sendByte(B);
//        lcd_printf("%c", B);
//    }
 // part2

//    timer_init();
//    lcd_init();
//    cyBot_uart_init();
//    cyBOT_init_Scan(1111);  // 213500 - right(0) | left(0) - 1256500
//   // cyBOT_SERVO_cal();
//
//    right_calibration_value = 213500;
//    left_calibration_value = 1256500;
//
//    int i, j;
//    cyBOT_Scan_t scan;
//
//       char format[] = "Degrees";
//       char format1[] = "Distance(cm)";
//       cyBOT_Scan(0, &scan);
//       int B = cyBot_getByte();
//       if(B == 'm'){
//           for(i=0; i < strlen(format); i++){
//               cyBot_sendByte(format[i]);
//           }
//           for(j=0; j<8; j++){
//               cyBot_sendByte(' ');
//           }
//           for(i=0; i<strlen(format1); i++){
//               cyBot_sendByte(format1[i]);
//           }
//           cyBot_sendByte('\r');
//           cyBot_sendByte('\n');
//       }
//
//    for (i=0; i <= 180; i+=2){
//        cyBOT_Scan(i, &scan);
//        char c[3];
//        char c1[3];
//
//        sprintf(c, "%d", i);
//        for(j=0; j < strlen(c); j++){
//            cyBot_sendByte(c[j]);
//        }
//
//        for(j=0; j < 14; j++){
//            cyBot_sendByte(' ');
//        }
//
//        sprintf(c1, "%f", scan.sound_dist);
//
//        for(j=0; j<strlen(c1); j++){
//            cyBot_sendByte(c1[j]);
//        }
//
//        cyBot_sendByte('\r');
//        cyBot_sendByte('\n');
//    }

    // part 3
    timer_init();
    lcd_init();
    cyBot_uart_init();
    cyBOT_init_Scan(0b0111);
    //cyBOT_SERVO_cal()

    //Cybot activation
   //    oi_t *sensor_data = oi_alloc();
   //    oi_init(sensor_data); // should turn the iRobot Create's "Dirt Detect" LED to blue
    right_calibration_value = 259000;
    left_calibration_value = 1256000;

    int i, j, x;
    int k = 1;
    cyBOT_Scan_t scan;

    char partTwoF[] = "Degrees";
    char partTwoF1[] = "Distance (cm)";
    char partTwoF2[] = "IR Value";

    char format[] = "Object#";
    char format1[] = "Angle";
    char format2[] = "Distance";
    char format3[] = "Width";
    int min = 0;
    int minAngle = 0;
    int minAngleDist = 0;
    int minActualWidth = 0;
    cyBOT_Scan(0, &scan);

    x= cyBot_getByte();
    if(x == 'm'){
       for(i = 0; i<strlen(partTwoF); i++){
           cyBot_sendByte(partTwoF[i]);
       }

       for(j = 0; j<8; j++){
             cyBot_sendByte(' ');
          }

       for(i = 0; i<strlen(partTwoF1); i++){
              cyBot_sendByte(partTwoF1[i]);
          }

       for(j = 0; j<8; j++){
               cyBot_sendByte(' ');
           }

       for(i = 0; i<strlen(partTwoF2); i++){
              cyBot_sendByte(partTwoF2[i]);
          }
       cyBot_sendByte('\r');
       cyBot_sendByte('\n');

       for(i = 0; i<=180; i++){
              cyBOT_Scan(i, &scan);
              char c[3];
              char c1[3];
              char c2[3];

              sprintf(c, "%d", i);
               for(j = 0; j<strlen(c); j++){
                         cyBot_sendByte(c[j]);
               }

               for(j = 0; j<14; j++){
                                cyBot_sendByte(' ');
               }

               float converter = scan.sound_dist/scan.IR_raw_val;
               int cm = scan.IR_raw_val*converter;

               sprintf(c1, "%f", scan.sound_dist);
               for(j = 0; j<strlen(c1); j++){
                   cyBot_sendByte(c1[j]);
               }

               for(j = 0; j<14; j++){
                   cyBot_sendByte(' ');
               }

               sprintf(c2, "%d", scan.IR_raw_val);
               for(j = 0; j<strlen(c2); j++){
                     cyBot_sendByte(c2[j]);
               }
                    cyBot_sendByte('\r');
                    cyBot_sendByte('\n');
               }

       for(i = 0; i<strlen(format); i++){
             cyBot_sendByte(format[i]);
       }

       for(i = 0; i<4; i++){
             cyBot_sendByte(' ');
       }

       for(i = 0; i<strlen(format1); i++){
           cyBot_sendByte(format1[i]);
       }

       for(i = 0; i<8; i++){
            cyBot_sendByte(' ');
       }

       for(i = 0; i<strlen(format2); i++){
             cyBot_sendByte(format2[i]);
       }

       for(i = 0; i<4; i++){
             cyBot_sendByte(' ');
       }

       for(i = 0; i<strlen(format3); i++){
             cyBot_sendByte(format3[i]);
       }

       cyBot_sendByte('\r');
       cyBot_sendByte('\n');

       char storedVal[100][20];
       int arrSizeCount = 0;
       int savedStrCount;
       int storedValCount=0;

       for(i = 0; i<=180; i++){
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
                                 cyBot_sendByte(obj[x]);
                             }
                             sprintf(tempStr, "Object %d: %d, %dcm ", k, rawVal, cm);

                             lcd_puts(tempStr);
                             k++;

                             for(x = 0; x<11; x++){
                                 cyBot_sendByte(' ');
                             }

                             sprintf(deg, "%d", begin);
                             for(x = 0; x<strlen(deg); x++){
                                  cyBot_sendByte(deg[x]);
                             }

                             for(x = 0; x<13; x++){
                                  cyBot_sendByte(' ');
                             }

                             sprintf(dist, "%d cm", cm);
                             for(x=0; x<strlen(dist); x++){
                                  cyBot_sendByte(dist[x]);
                             }

                             for(x = 0; x<11; x++){
                                  cyBot_sendByte(' ');
                             }

                             sprintf(wid, "%d", width);
                             for(x = 0; x<strlen(wid); x++){
                                  cyBot_sendByte(wid[x]);
                             }

                             cyBot_sendByte('\r');
                             cyBot_sendByte('\n');

                             minActualWidth = soundDist*sin((width/2)*(PI/180));

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
   cyBOT_Scan(minAngle, &scan);
  }
    return 0;
}
