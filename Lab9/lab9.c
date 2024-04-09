/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "adc.h"
#include "uart.h"
#include "ping_template.h"
#include "movement.h"
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "cyBot_Scan.h"
#include "lcd.h"
//#include "ping_template.c"


// Uncomment or add any include directives that are needed

//#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();

	// YOUR CODE HERE

	while(1)
	{
	  //  ping_trigger();
      // YOUR CODE HERE
	    float dist = 0;
	    dist = ping_getDistance();
	    lcd_printf("%.2f, OF: %d", dist, overflow);
	    timer_waitMicros(500000);

	}



//	        timer_waitMillis(200);
//	    lcd_printf("%d overflow count", overflow);
//	    lcd_printf("%d Milliseconds", ping_trigger());
//	    lcd_printf("Ping distance: %d in cm", ping_getDistance());



}
