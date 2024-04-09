/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"
#include <string.h>
#include <stdio.h>

int main (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen functions can be called 
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the LCD screen.  This also clears the screen. 

	// Print "Hello, world" on the LCD
	//lcd_printf("Hello, world");

//	lcd_puts("Hello, world"); // Replace lcd_printf with lcd_puts
        // step through in debug mode and explain to TA how it works
    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
       // NOTE: For time functions, see Timer.h
	/*char strn[] = "                    Microcontrollers are fun! ";
	char strn2[20];
	char temp = '\0';
    int i,k;


	while(1){
	    for(i=0; i<strlen(strn); i++){
	        strn[strlen(strn)-1] = strn[0];
	        temp = strn[0];
	        for(k=0; k < strlen(strn)-1; k++ ){
	            strn[k] = strn[k+1];
	        }
	        strn[strlen(strn)-1 ] = temp;
	        strncpy(strn2, strn, 19);
	        lcd_printf(strn2);
	        timer_waitMillis(300);
	    }
	}*/


}
