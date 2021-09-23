/*
 * states.h
 *
 *  Created on: Jul 30, 2021
 *      Author: Junqi
 */

#ifndef SRC_STATES_H_
#define SRC_STATES_H_

#include <stdio.h>

void sys_init();
void AS_OFF_Handler();
void AS_Ready_Handler();
void AS_Driving_Handler();
void AS_Emergency_Handler();
void AS_Finished_Handler();
void Manual_Driving_Handler();
void run();

typedef enum {
	AS_Off,
	AS_Ready,
	Manual_Driving,
	AS_Driving,
	AS_Emergency,
	AS_Finished
} autonomousSystemStates;

typedef enum {
	ts_on,
	ts_off
} TS_state;

typedef enum {
	r2d_on,
	r2d_off
} R2D_state;

typedef enum {
	sa_avaliable,
	sa_unavaliable
} SA_state;

typedef enum {
	sb_engaged,
	sb_avaliable,
	sb_unavaliable
} SB_state;

typedef enum {
	ebs_armed,
	ebs_unavaliable,
	ebs_activated
} EBS_state;

typedef enum {
	assi_OFF,
	assi_yellow_cont,
	assi_yellow_flash,
	assi_blue_cont,
	assi_blue_flash
} ASSI_state;

#endif /* SRC_STATES_H_ */
