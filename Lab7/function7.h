/*
 * function7.h
 *
 *  Created on: Mar 21, 2024
 *      Author: ctrinkle
 */

#ifndef FUNCTION7_H_
#define FUNCTION7_H_

void avoid(oi_t *sensor_data, bool direction);

int auto_forward(oi_t *sensor_data, double distance_mm, int speed);

int auto_driving(int minAngle, oi_t *sensor_data, cyBOT_Scan_t *scan_data, int sml_obj);

#endif /* FUNCTION7_H_ */
