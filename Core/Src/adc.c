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
		float note_number = (float)HAL_ADC_GetValue(hadc) / 32.0f;
		float target_frequency = 440.0f * pow(2.0f, (note_number - 69.0f) / 12.0f);
		dac_delta = (DAC_OUTPUT_MAX + 1) * target_frequency / SAMPLE_RATE / 4.0f;
	} else if (hadc->Instance == ADC2) {
		// pulse_width = HAL_ADC_GetValue(hadc) / DAC_OUTPUT_MAX;
	}
}
