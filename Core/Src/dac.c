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
WaveType dac2_wave_type = Sawtooth_Down_Wave;

// Start at the "zero" crossing point, rather than the bottom.
float dac_phase_increment = (DAC_OUTPUT_MAX + 1.0f) / 2.0f;
float dac_phase_delta = 1;
float pulse_width = 0.5;

void render_waves() {
	render_wave(&hdac1, DAC_CHANNEL_1, dac1_wave_type, dac_phase_increment, dac_phase_delta);
	render_wave(&hdac1, DAC_CHANNEL_2, dac2_wave_type, dac_phase_increment, dac_phase_delta);
	render_pulse(GPIOA, GPIO_PIN_6, dac_phase_increment);

	dac_phase_increment += dac_phase_delta;
	if (dac_phase_increment > DAC_OUTPUT_MAX) {
		dac_phase_increment = 0.0f;
	}
}

void render_wave(DAC_HandleTypeDef* dac, uint8_t channel, WaveType wave_type, float phase_inc, float phase_delta) {
	float out;

	if (wave_type == Triangle_Wave) {
		if (phase_inc < (DAC_OUTPUT_MAX + 1.0f) / 2.0f) {
			out = phase_inc * 2.0f;
		} else {
			out = DAC_OUTPUT_MAX - (phase_inc - DAC_OUTPUT_MAX / 2.0f) * 2.0f;
		}
	} else if (wave_type == Sawtooth_Down_Wave) {
		out = DAC_OUTPUT_MAX - phase_inc;
	} else if (wave_type == Sawtooth_Up_Wave) {
		out = phase_inc;
	} else if (wave_type == Sine_Wave) {
		out = sine_lut[(uint16_t)phase_inc];
	}

	HAL_DAC_SetValue(dac, channel, DAC_ALIGN_12B_R, (uint16_t)round(out));
}

void render_pulse(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, float value) {
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, value / DAC_OUTPUT_MAX < pulse_width);
}
