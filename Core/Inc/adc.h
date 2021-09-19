/*
 * adc.h
 *
 *  Created on: Sep 19, 2021
 *      Author: furkle
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "main.h"

extern ADC_HandleTypeDef hadc1;

extern float dac_value;
extern float dac_delta;
extern float pulse_width;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

#endif /* INC_ADC_H_ */
