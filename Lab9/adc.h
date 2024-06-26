/*
 * adc.h
 *
 *  Created on: Mar 19, 2024
 *      Author: ctrinkle
 */

#ifndef ADC_H_
#define ADC_H_

#include "Timer.h"
#include <stdint.h>
#include <stdbool.h>
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

   void adc_init(void);

   int adc_read(void);

#endif /* ADC_H_ */
