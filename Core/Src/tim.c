/*
 * tim.c
 *
 *  Created on: Sep 19, 2021
 *      Author: furkle
 */

#include "tim.h"
#include "dac.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM16) {
		render_wave(&hdac1, DAC_CHANNEL_1, dac1_wave_type, &dac_value, &dac_delta);
		render_wave(&hdac1, DAC_CHANNEL_2, dac2_wave_type, &dac_value, &dac_delta);
		render_pulse(GPIOA, GPIO_PIN_6, &dac_value, &dac_delta);
	}
}
