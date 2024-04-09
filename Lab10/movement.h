/*
 * movement.h
 *
 *  Created on: Jan 31, 2024
 *      Author: ctrinkle
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Timer.h"
#include <inc/tm4c123gh6pm.h>
#include "lcd.h"
#include "open_interface.h"

void collisionBumpLeft(oi_t *sensor_data);

void collisionBumpRight(oi_t *sensor_data);


double  move_forward (oi_t *sensor_data,   double distance_mm);


#endif /* MOVEMENT_H_ */
