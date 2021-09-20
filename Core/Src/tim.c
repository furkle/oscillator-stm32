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
		render_waves();
	}
}
