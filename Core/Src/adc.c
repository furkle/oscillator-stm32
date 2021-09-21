/*
 * adc.c
 *
 *  Created on: Sep 19, 2021
 *      Author: furkle
 */

#include <math.h>
#include "adc.h"
#include "dac.h"

#define FINE_TUNE -0.00f

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	if (hadc->Instance == ADC1) {
		float note_number = (float)HAL_ADC_GetValue(hadc) / 32.0f;
		float target_frequency = 440.0f * pow(2.0f + FINE_TUNE, (note_number - 69.0f) / 12.0f);
		dac_phase_delta = (DAC_OUTPUT_MAX + 1.0f) * target_frequency / SAMPLE_RATE;
	} else if (hadc->Instance == ADC2) {
		pulse_width = HAL_ADC_GetValue(hadc) / DAC_OUTPUT_MAX;
	}
}
