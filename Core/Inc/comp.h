/*
 * comp.h
 *
 *  Created on: Sep 20, 2021
 *      Author: furkle
 */

#ifndef INC_COMP_H_
#define INC_COMP_H_

#include "main.h"
#include "dac.h"

void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp);
void hard_sync(float *phase_inc);
void soft_sync(float* phase_inc);

extern SyncType sync_type;
extern float dac_phase_increment;

#endif /* INC_COMP_H_ */
