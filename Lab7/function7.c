/*
 * function7.c
 *
 *  Created on: Mar 21, 2024
 *      Author: ctrinkle
 */

#include "movement.h"
#include "open_interface.h"
#include "cyBot_Scan.h"
#include "function7.h"


    void avoid(oi_t *sensor_data, bool direction){
        move_backward(sensor_data, 150); //75
        if(!direction){
            turn_right(sensor_data, 90);
            move_forward(sensor_data, 250); //75
            turn_left(sensor_data, 90);
        }
        if(direction){
             turn_left(sensor_data, 90);
             move_forward(sensor_data, 250); //75
             turn_right(sensor_data, 90);
        }
        move_forward(sensor_data, 150); //75
        oi_setWheels(0,0);
    }

    int auto_forward(oi_t *sensor_data, double distance_mm, int speed){
        int reset = 0;
        double sum = 0;
        while(sum < distance_mm){
//            if(command_flag_toggle == 1){
//                command_falg_toggle = 0;
//                return 1;
      //      }

            oi_setWheels(speed,speed);
            oi_update(sensor_data);
            if(sensor_data->bumpLeft){
                avoid(sensor_data, 0);
                reset = 0;
            }
            else if(sensor_data->bumpRight){
                avoid(sensor_data, 1);
                reset = 2;
            }
            else{
                sum += abs(sensor_data->distance);
            }
        }
        oi_setWheels(0,0);
        return reset;
    }

    int auto_driving(int minAngle, oi_t *sensor_data, cyBOT_Scan_t *scan_data, int minAngleDist){
        int mid_angle = minAngle; //self -> obj_mid_angle[sml_obj]
        if(mid_angle > 92){
            turn_left(sensor_data, mid_angle - 90);
        }
        else if(mid_angle > 88){
            turn_right(sensor_data, 90 - mid_angle);
        }
        int tog = 0;
        tog = auto_forward(sensor_data, (10*((minAngleDist) -15)), 75);
        if(tog == 1){
            return 0;
        }
        if(tog == 2){
            scan_path(scan_data, sensor_data);
            scan_obj_2(scan_data, sensor_data);
            int sml_obj_2 = 0;
            sml_obj_2 = smallest_obj(sensor_data, scan_data);
            controlled_driving(sensor_data, scan_data, sml_obj_2);
        }
        return 0;
    }
