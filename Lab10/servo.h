/*
 * servo.h
 *
 *  Created on: Apr 1, 2024
 *      Author: ctrinkle
 */

#ifndef SERVO_H_
#define SERVO_H_

volatile signed pulse_width;

void servo_init(void);

void servo_move(float);


#endif /* SERVO_H_ */
