/*
 * movement.c
 *
 *  Created on: Jan 31, 2024
 *      Author: ctrinkle
 */
#include "movement.h"
#include "open_interface.h"

void collisionBumpLeft(oi_t *sensor_data){
    oi_setWheels(-300,-300);
    oi_moveBackward(sensor_data, -15);
    oi_setWheels(0,0); // Move backwards section

    oi_setWheels(-300,300);
    oi_turnCounterClockwise(sensor_data, -77);
    oi_setWheels(0,0); // Turn clockwise 90 degrees

    oi_setWheels(300,300);
    oi_moveForward(sensor_data, 25);
    oi_setWheels(0,0);

    oi_setWheels(300,-300);
    oi_turnClockwise(sensor_data, 77);
    oi_setWheels(0,0);
}

void collisionBumpRight(oi_t *sensor_data){
    oi_setWheels(-300,-300);
    oi_moveBackward(sensor_data, -15);
    oi_setWheels(0,0); // Move backwards section

    oi_setWheels(300,-300);
    oi_turnClockwise(sensor_data, 77);
    oi_setWheels(0,0); // Turn clockwise 90 degrees

    oi_setWheels(300,300);
    oi_moveForward(sensor_data, 25);
    oi_setWheels(0,0);

    oi_setWheels(-300,300);
    oi_turnCounterClockwise(sensor_data, -77);
    oi_setWheels(0,0);
}
double  move_forward (oi_t *sensor_data,   double distance_mm){

}

