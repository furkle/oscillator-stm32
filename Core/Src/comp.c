/*
 * comp.c
 *
 *  Created on: Sep 20, 2021
 *      Author: furkle
 */

#include "comp.h"
#include "dac.h"

SyncType sync_type = Soft_Sync_Falling;

void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp) {
	if (HAL_COMP_GetOutputLevel(hcomp) == COMP_OUTPUT_LEVEL_LOW) {
		if (sync_type == Hard_Sync_Both || sync_type == Hard_Sync_Falling) {
			hard_sync(&dac_phase_increment);
		} else if (sync_type == Soft_Sync_Both || sync_type == Soft_Sync_Falling) {
			soft_sync(&dac_phase_increment);
		}
	} else {
		if (sync_type == Hard_Sync_Both || sync_type == Hard_Sync_Rising) {
			hard_sync(&dac_phase_increment);
		} else if (sync_type == Soft_Sync_Both || sync_type == Soft_Sync_Rising) {
			soft_sync(&dac_phase_increment);
		}
	}
}

// Reset the phase increment back to the "zero"-crossing point.
void hard_sync(float* phase_inc) {
	*phase_inc = (DAC_OUTPUT_MAX + 1.0f) / 2.0f;
}

// "Reverse" the phase of the wave, or in other terms, mirror the position
// around the "zero"-crossing point.
void soft_sync(float* phase_inc) {
	*phase_inc = DAC_OUTPUT_MAX - *phase_inc;
}
