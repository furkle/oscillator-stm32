/*
 * adc.h
 *
 *  Created on: Sep 19, 2021
 *      Author: furkle
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "main.h"
#include "dac.h"

const float PI;

extern ADC_HandleTypeDef hadc1;

float last_note_number;
float note_number;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void generate_buffer(uint16_t num_frames);

#endif /* INC_ADC_H_ */
