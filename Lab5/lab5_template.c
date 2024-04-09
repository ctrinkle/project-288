/**
 * lab5_template.c
 *
 * Template file for CprE 288 Lab 5
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 * @author Diane Rover, updated 2/25/2021, 2/17/2022
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include <stdio.h>
#include "movement.h"
#include <math.h>
#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "uart.h"


#define LCD_TOTAL_CHARS 80

#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#include "cyBot_Scan.h"  // Scan using CyBot servo and sensors


#warning "Possible unimplemented functions"
#define maxchar 20


char buffer[LCD_TOTAL_CHARS + 1];
int buffer_index = 0;


int main(void) {

	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	void lcd_clear();
	void lcd_putc(char c);
	void lcd_gotoLine(uint8_t lineNum);
	void lcd_setCursorPos(uint8_t x, uint8_t y);
	void uart_sendChar(char data);
	char uart_receive(void);
	void process_received_char(char c);

  // initialize the cyBot UART1 before trying to use it

  // (Uncomment ME for UART init part of lab)
	// cyBot_uart_init_clean();  // Clean UART1 initialization, before running your UART1 GPIO init code

	// Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART1 GPIO init code)
      SYSCTL_RCGCGPIO_R |= 0x02;
	    while ((SYSCTL_PRGPIO_R & 0x02) == 0) {};
		  GPIO_PORTB_DEN_R |= 0xFF;
		  GPIO_PORTB_AFSEL_R |= 0x03;
      GPIO_PORTB_PCTL_R &= 0xFFFFF00;     // Force 0's in the desired locations
      GPIO_PORTB_PCTL_R |= 0x0000011;     // Force 1's in the desired locations
		 // Or see the notes for a coding alternative to assign a value to the PCTL field

    // (Uncomment ME for UART init part of lab)
		 cyBot_uart_init_last_half();  // Complete the UART device configuration

		// Initialize the scan
	//    cyBOT_init_Scan();
		// Remember servo calibration function and variables from Lab 3

	// YOUR CODE HERE
	//init(button_interrupts());
       //   lcd_clear(); // Clear LCD at the beginning

//		    while (1) {
//		        char received_char = uart_receive();
//
//		        process_received_char(received_char);
//		        buffer[] = receivedChar;
//
//		    }
//
//		    return 0;
//		}
//
//		void process_received_char(char c) {
//		    // Handle enter key press
//		    if (c == '\r' || c == '\n') {
//		        // Clear the buffer and print a new line on the LCD
//		        buffer[buffer_index] = '\0'; // Null-terminate buffer
//		        buffer_index = 0;
//		        lcd_gotoLine(1);
//		        lcd_printf("\n");
//		        return;
//		    }
//
//		    // Buffer the received character
//		    buffer[buffer_index++] = c;
//		    buffer[buffer_index] = '\0'; // Null-terminate buffer
//
//		    // Print the character on LCD line 1
//		    lcd_gotoLine(1);
//		    lcd_printf("%c", c);
//
//		    // Print the number of characters in the buffer on LCD line 2
//		//    lcd_gotoLine(2);
//		//    lcd_printf("%d", buffer_index);
//		}
//
//	while(1)
//	{
//
//      // YOUR CODE HERE
//	    char input[maxchar + 1]; // +1 for null terminator
//	        int count = 0;
//
//
//	        while (1) {
//	            char in = cyBot_getByte_blocking(); // Read one character
//
//	            if (in == '\r') { // If ENTER is pressed
//	                input[count] = '\0'; // Null terminate the string
//	                break;
//	            }
//
//	            if (count < maxchar) { // If not reached the limit
//	                input[count++] = in; // Add character to the input array
//	                uart_sendChar(in);
//	                lcd_printf("%c", in);
//	            }
//
//	            if (count == maxchar) { // If reached the limit
//	                // Clear the display
//	                uart_sendChar('\r');
//	                uart_sendChar('\n');
//	                // Print the entire series of characters on LCD line 1
//	                //lcd_printf("%c", input[maxchar]);
//	                count = 0; // Reset the count
//	            }
//	        }
//
//	        // Print remaining characters if any
//	        if (count > 0) {
//	            // Print the entire series of characters on LCD line 1
//	          //  lcd_printf("%c", in);
//	        }
//
//	        return 0;
//	    }

//
//	char buffer[20];
//
//
//	    while(1){
//
//	        char received_char = uart_receive();
//
//	        process_received_char(received_char);
//	        buffer[buffer_index] = received_char;
//	        return 0;
//}
//
//
//
//	        void process_received_char(char c) {
//            if (c == '\r' || c == '\n') {
//                // Clear the buffer and print a new line on the LCD
//                buffer[buffer_index] = '\0'; // Null-terminate buffer
//                buffer_index = 0;dd
//                lcd_gotoLine(1);
//                lcd_printf("\n");
//
//                return;
//            }
//            if(buffer_index == 20){
//                buffer_index = 0;
//                lcd_clear();
//
//            }
//            lcd_printf("%s", buffer);
//            buffer[buffer_index++] = c;
//            buffer[buffer_index] = '\0';
//;
//

		 int i;
		 char ch;
		 while(1){
		     char str[21] = "";
		     i=0;
		     while(i<21){
		         ch = uart_receive();
		         if(ch == '\r'){
		             break;
		         }

		         str[i] = ch;
		         lcd_clear();
		         lcd_puts(str);
		         lcd_gotoLine(2);
		         i++;
		         lcd_printf("%s\n%d", str, i);
		         uart_sendChar(ch);

		     }
		     lcd_clear();
		     uart_sendChar('\r');
		     uart_sendChar('\n');

		 }




   }
