/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
#include "open_interface.h"
#include "cyBot_Scan.h"
#include <stdio.h>
#include "movement.h"
#include <math.h>
#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

                            // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1


#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	cyBot_uart_init(); // Don't forget to initialize the cyBot UART before trying to use it
char c1[] = "Button One Pushed";
char c2[] = "Button Two Pushed";
char c3[] = "Button three pushed";
char c4[] = "Button four pushed";
	int j = 0;
	// YOUR CODE HERE
      while(1){

          int ButtonValue = button_getButton();

          if(ButtonValue == 4  ){
              lcd_printf("Button Four Pushed");

                       for( j = 0; j < strlen(c4); j++){
                               cyBot_sendByte(c4[j]);
                       }
                               //sprintf(c1, "%d Button was pushed!", button_getButton());
                               cyBot_sendByte('\r');
                               cyBot_sendByte('\n');

                   }


          else if(ButtonValue == 3  ){
              lcd_printf("Button Three pushed");

                      for( j = 0; j < strlen(c3); j++){
                          cyBot_sendByte(c3[j]);
                      }
                      //sprintf(c1, "%d Button was pushed!", button_getButton());
                      cyBot_sendByte('\r');
                      cyBot_sendByte('\n');

          }


          else if(ButtonValue == 2  ){
              lcd_printf("Button Two Pushed");

                      for( j = 0; j < strlen(c2); j++){
                          cyBot_sendByte(c2[j]);
                      }
                      //sprintf(c1, "%d Button was pushed!", button_getButton());
                      cyBot_sendByte('\r');
                      cyBot_sendByte('\n');

          }


          else if(ButtonValue == 1){
              lcd_printf("Button One Pushed", button_getButton());
             // sprintf(c1, "%d Button was pushed!", button_getButton());

                      for( j = 0; j < strlen(c1); j++){
                          cyBot_sendByte(c1[j]);
                      }
                      //sprintf(c1, "%d Button was pushed!", button_getButton());
                      cyBot_sendByte('\r');
                      cyBot_sendByte('\n');
            //  cyBot_sendByte("%d Button was pushed!", button_getButton());

          }

          else if (ButtonValue == 0){
              continue;
          }

      }
 return 0;
}
