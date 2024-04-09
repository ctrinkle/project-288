/**
 * lab6-interrupt_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
#include "uart-interrupt.h"
#include "uart.h"

// Uncomment or add any include directives that you want to use
// #include "open_interface.h"
// #include "movement.h"
// #include "button.h"

// Your code can use the global variables defined in uart-interrupt.c
// They are declared with the extern qualifier in uart-interrupt.h, which makes the variables visible to this file.

#warning "Possible unimplemented functions"
#define REPLACEME 0


int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	uart_interrupt_init();
  // cyBOT_init_Scan();

	// OPTIONAL
	//assign a value to command_byte if you want to know whether that ASCII code is received
	//note that command_byte is global shared variable read by the ISR
	//for example, try using a tab character as a command from PuTTY

//	while(1)
//	{
//
//      // YOUR CODE HERE
////	    int i;
////	        char ch;
////	        while(1){
////	            char str[21] = "";
////	            i=0;
////	            while(i<21){
////	               // ch = uart_receive_nonblocking();
//////	                if(ch == '\r'){
//////	                    break;
//////	                }
////	                //UART1_Handler();
//////	                str[i] = ch;
//////	                lcd_clear();
//////	                lcd_puts(str);
//////	                lcd_gotoLine(2);
//////	                i++;
//////	                lcd_printf("%s\n%d", str, i);
//////	                uart_sendChar(ch);
////
////	            }
////	            lcd_clear();
////	            uart_sendChar('\r');
////	            uart_sendChar('\n');
//
//	        }
			//first, try leaving this loop empty and see what happens
			//then add code for your application
			// OPTIONAL
			//test and reset command_flag if your ISR is updating it
			//for example, if the flag is 1, do something, like send a message to PuTTY or LCD, or stop a sensor scan, etc.
			//be sure to reset command_flag so you don't keep responding to an old flag

	}

}
