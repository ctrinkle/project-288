/*
 * movement.c
 *
 *  Created on: Jan 31, 2024
 *      Author: ctrinkle
 */
#include "movement.h"
#include "open_interface.h"

void collisionBumpLeft(oi_t *sensor_data){
    oi_setWheels(-100,-100);
    oi_moveBackward(sensor_data, -10);
    oi_setWheels(0,0); // Move backwards section

    oi_setWheels(-50,50);
            oi_turnClockwise(sensor_data, -82);
            timer_waitMillis(2);
            oi_setWheels(0,0); // Turn clockwise 90 degrees

    oi_setWheels(100,100);
    oi_moveForward(sensor_data, 15);
    oi_setWheels(0,0);

    oi_setWheels(50,-50);
        oi_turnCounterClockwise(sensor_data, 82);
        timer_waitMillis(2);
        oi_setWheels(0,0); // Turn clockwise 90 degrees

    oi_setWheels(100,100);
    oi_moveForward(sensor_data, 20);
    oi_setWheels(0,0);
}

void collisionBumpRight(oi_t *sensor_data){
    oi_setWheels(-100,-100);
    oi_moveBackward(sensor_data, -10);
    oi_setWheels(0,0); // Move backwards section

    oi_setWheels(50,-50);
        oi_turnCounterClockwise(sensor_data, 82);
        timer_waitMillis(2);
        oi_setWheels(0,0);

    oi_setWheels(100,100);
    oi_moveForward(sensor_data, 15);
    oi_setWheels(0,0);

    oi_setWheels(-50,50);
        oi_turnClockwise(sensor_data, -82);
        timer_waitMillis(2);
        oi_setWheels(0,0); // Turn clockwise 90 degrees


    oi_setWheels(100,100);
    oi_moveForward(sensor_data, 20);
    oi_setWheels(0,0);
}

double  move_forward (oi_t *sensor_data,   double distance_mm){
    oi_setWheels(300,300);
    oi_moveForward(sensor_data, distance_mm);
    oi_setWheels(0,0);
    return 0;
}

double move_backward(oi_t *sensor_data,   double distance_mm){
    oi_setWheels(-300,-300);
    oi_moveForward(sensor_data, distance_mm);
    oi_setWheels(0,0);
    return 0;
}

void turn_left(oi_t *sensor_data, double mid_angle){
    oi_setWheels(-300,300);
    oi_turnCounterClockwise(sensor_data, mid_angle);
    oi_setWheels(0,0);
}

void turn_right(oi_t *sensor_data, double mid_angle){
    oi_setWheels(300,-300);
    oi_turnClockwise(sensor_data, mid_angle);
    oi_setWheels(0,0);
}


