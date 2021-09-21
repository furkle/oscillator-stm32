/*
 * dac.h
 *
 *  Created on: Sep 19, 2021
 *      Author: furkle
 */

#ifndef INC_DAC_H_
#define INC_DAC_H_

#include "main.h"

#define SAMPLE_RATE 48000.0f
#define DAC_OUTPUT_MAX 4095.0f

typedef enum WaveType {
	Triangle_Wave,
	Sawtooth_Up_Wave,
	Sawtooth_Down_Wave,
	Sine_Wave
} WaveType;

typedef enum SyncType {
	Hard_Sync_Rising,
	Hard_Sync_Falling,
	Hard_Sync_Both,
	Soft_Sync_Rising,
	Soft_Sync_Falling,
	Soft_Sync_Both
} SyncType;

void render_waves();
void render_wave(DAC_HandleTypeDef* dac, uint8_t channel, WaveType wave_type, float value, float delta);
void render_pulse(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, float value);

extern DAC_HandleTypeDef hdac1;

WaveType dac1_wave_type;
WaveType dac2_wave_type;

float dac_phase_increment;
float dac_phase_delta;
float pulse_width;

#endif /* INC_DAC_H_ */
