

/**
 * main.c
 */
#include "open_interface.h"
#include "movement.h"
#include "lcd.h"
#include "timer.h"
#include <stdio.h>


int main(void)
{

  //Part1
   /* timer_init();

    lcd_init();

    oi_t *sensor_data = oi_alloc(); // do this only once at start of main()
    oi_init(sensor_data); // do this only once at start of main()
    // the following code could be put in function move_forward()
    double sum = 0; // distance member in oi_t struct is type double
    oi_setWheels(300,300); //move forward at full speed
        while (sum < 100) {
        oi_update(sensor_data);
        move_forward(sensor_data, 10);
        sum += sensor_data -> distance; // use -> notation since pointer
        lcd_printf("%d", sum);
    }
    oi_setWheels(0,0); //stop
    oi_free(sensor_data); // do this once at end of main()
*/

    //Part2
/*
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    oi_setWheels(0,0);
*/
/*
    oi_t *sensor_data = oi_alloc();

    lcd_init();

    oi_init(sensor_data);
    oi_setWheels(300,300);

    int i;
    for (i=0; i<4; i++){
        oi_setWheels(300,300);
        oi_moveForward(sensor_data, 50);
        oi_setWheels(0,0);

        oi_setWheels(500,-500);
        oi_turnClockwise(sensor_data, 80); //turn 90 degree right
        oi_setWheels(0,0);
    }
    oi_free(sensor_data);
*/

    //Part3

    oi_t *sensor_data = oi_alloc();
    lcd_init();
    oi_init(sensor_data);

    oi_setWheels(300,300);

    oi_moveForward(sensor_data, 200);

    oi_setWheels(0,0);

    oi_free(sensor_data);

return 0;
}
