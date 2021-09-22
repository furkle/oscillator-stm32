/*
 * comp.h
 *
 *  Created on: Sep 20, 2021
 *      Author: furkle
 */

#ifndef INC_COMP_H_
#define INC_COMP_H_

#include "main.h"
#include "adc.h"

void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp);
void hard_sync();
void soft_sync();

SyncType sync_type;

#endif /* INC_COMP_H_ */
