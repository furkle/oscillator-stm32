/*
 * adc.c
 *
 *  Created on: Sep 19, 2021
 *      Author: furkle
 */

#include <math.h>
#include "adc.h"
#include "dac.h"

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	if (hadc->Instance == ADC1) {
		float note_number = HAL_ADC_GetValue(hadc) / 32;
		float target_frequency = 440 * pow(2, (note_number - 69) / 12);
		float delta = (DAC_OUTPUT_MAX + 1) * target_frequency / SAMPLE_RATE / 2;
		dac_delta = delta;
		HAL_ADC_Start_IT(&hadc1);
	} else if (hadc->Instance == ADC2) {
		pulse_width = HAL_ADC_GetValue(hadc) / DAC_OUTPUT_MAX;
	}
}
