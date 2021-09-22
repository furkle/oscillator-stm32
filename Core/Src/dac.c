/*
 * dac.c
 *
 *  Created on: Sep 19, 2021
 *      Author: furkle
 */

#include <math.h>
#include "dac.h"

#define FINE_TUNE 0.00f

const float PI = 2 * acos(0.0f);
const float twoPI = 2 * PI;

WaveType dac1_wave_type = Sine_Wave;
WaveType dac2_wave_type = Triangle_Wave;

float waveform_phase = 0.0f;
float last_output = 0.0f;

void render_waves() {
	render_wave(&hdac1, DAC_CHANNEL_1, dac1_wave_type);
	render_wave(&hdac1, DAC_CHANNEL_2, dac2_wave_type);
	render_pulse(GPIOA, GPIO_PIN_6);

	waveform_phase += phase_delta;
	while (waveform_phase >= twoPI) {
		waveform_phase -= twoPI;
	}
}

// from http://www.martin-finke.de/blog/articles/audio-plugins-018-polyblep-oscillator/
float poly_blep(float t)
{
    float dt = phase_delta / twoPI;
    // 0 <= t < 1
    if (t < dt) {
        t /= dt;
        return t+t - t*t - 1.0f;
    }
    // -1 < t < 0
    else if (t > 1.0f - dt) {
        t = (t - 1.0f) / dt;
        return t*t + t+t + 1.0f;
    }
    // 0 otherwise
    else return 0.0f;
}

void render_wave(DAC_HandleTypeDef* dac, uint8_t channel, WaveType wave_type) {
	float value = 0.0f;
    float t = waveform_phase / twoPI;

	switch (wave_type) {
		case Sine_Wave:
			value = fast_sine(waveform_phase - PI);
			break;

		case Sawtooth_Down_Wave:
			value = 1.0f - (2.0f * waveform_phase / twoPI);
	        value += poly_blep(t);
			break;

		case Sawtooth_Up_Wave:
			value = -1.0f + (2.0f * waveform_phase / twoPI);
	        value -= poly_blep(t);
			break;

		case Pulse_Wave:
			if (waveform_phase <= PI) {
				value = 1.0f;
			} else {
				value = -1.0f;
			}

	        value += poly_blep(t);
	        value -= poly_blep(fmod(t + 0.5f, 1.0f));
		case Triangle_Wave:
			if (waveform_phase <= PI) {
				value = 1.0f;
			} else {
				value = -1.0f;
			}

	        value += poly_blep(t);
	        value -= poly_blep(fmod(t + 0.5f, 1.0f));

			// Leaky integrator: y[n] = A * x[n] + (1 - A) * y[n-1]
			value = phase_delta * value + (1.0f - phase_delta) * last_output;
			last_output = value;

			break;
	}

	last_output = value;

	// Normalize above zero and then scale to fit the 12-bit ADC space.
	float dac_value = round((value + 1.0f) * ((DAC_OUTPUT_MAX + 1.0f) / 2));
	if (dac_value < 0) {
		dac_value = 0;
	} else if (dac_value > DAC_OUTPUT_MAX) {
		dac_value = DAC_OUTPUT_MAX;
	}

	HAL_DAC_SetValue(dac, channel, DAC_ALIGN_12B_R, (uint16_t)dac_value);
}

void render_pulse(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, waveform_phase / twoPI < pulse_width);
}

// from Approximating sin(x) to 5 ULP with Chebyshev polynomials, by Colin Wallace
float coeffs[6] = {
	-0.10132118f,          // x
	 0.0066208798f,        // x^3
	-0.00017350505f,       // x^5
	 0.0000025222919f,     // x^7
	-0.000000023317787f,   // x^9
	 0.00000000013291342f, // x^11
};

float pi_major = 3.1415927f;
float pi_minor = -0.00000008742278f;

float fast_sine(float x) {
	float x2 = x*x;
	float p11 = coeffs[5];
	float p9  = p11*x2 + coeffs[4];
	float p7  = p9*x2  + coeffs[3];
	float p5  = p7*x2  + coeffs[2];
	float p3  = p5*x2  + coeffs[1];
	float p1  = p3*x2  + coeffs[0];
	return (x - pi_major - pi_minor) *
			(x + pi_major + pi_minor) * p1 * x;
}
