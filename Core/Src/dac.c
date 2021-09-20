/*
 * dac.c
 *
 *  Created on: Sep 19, 2021
 *      Author: furkle
 */

#include <math.h>
#include "dac.h"
#include "sine_lut.h"

WaveType dac1_wave_type = Triangle_Wave;
WaveType dac2_wave_type = Sine_Wave;

float dac_value = 0;
float dac_delta = 1;
float pulse_width = 0.5;

void render_wave(DAC_HandleTypeDef* dac, uint8_t channel, WaveType wave_type, float* value, float* delta) {
	float out;

	*value += *delta;
	if (*value > DAC_OUTPUT_MAX) {
		*value = 0.0f;
	}

	if (wave_type == Triangle_Wave) {
		if (*value < (DAC_OUTPUT_MAX + 1.0f) / 2.0f) {
			out = *value * 2;
		} else {
			out = DAC_OUTPUT_MAX - (*value - DAC_OUTPUT_MAX / 2.0f) * 2.0f;
		}
	} else if (wave_type == Sawtooth_Down_Wave) {
		out = DAC_OUTPUT_MAX - *value - 1.0f;
	} else if (wave_type == Sawtooth_Up_Wave) {
		out = *value;
	} else if (wave_type == Sine_Wave) {
		out = sine_lut[(uint16_t)*value];
	}

	HAL_DAC_SetValue(dac, channel, DAC_ALIGN_12B_R, (uint16_t)round(out));
}

void render_pulse(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, float* value, float* delta) {
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, *value / DAC_OUTPUT_MAX < pulse_width);
}
