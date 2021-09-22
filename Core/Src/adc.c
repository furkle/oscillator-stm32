/*
 * adc.c
 *
 *  Created on: Sep 19, 2021
 *      Author: furkle
 */

#include <math.h>
#include "adc.h"

#define FINE_TUNE 0.00f

float phase_delta = 0.0f;
float note_number = -1.0f;
float target_frequency = -1.0f;
float pulse_width = 0.5f;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	if (hadc->Instance == ADC1) {
		last_note_number = note_number;
		note_number = (float)HAL_ADC_GetValue(hadc) / 32.0f;
		target_frequency = 440.0f * pow(2.0f + FINE_TUNE, (note_number - 69.0f) / 12.0f);
		phase_delta = target_frequency * twoPI / SAMPLE_RATE; // (DAC_OUTPUT_MAX + 1.0f) * target_frequency / SAMPLE_RATE;
	} else if (hadc->Instance == ADC2) {
		pulse_width = (float)HAL_ADC_GetValue(hadc) / DAC_OUTPUT_MAX;
		if (pulse_width < 0.025f) {
			pulse_width = 0.0f;
		} else if (pulse_width > 0.975f) {
			pulse_width = 1.0f;
		}
	}
}
