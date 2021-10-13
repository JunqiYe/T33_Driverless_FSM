/*
 * states.h
 *
 *  Created on: Jul 30, 2021
 *      Author: Junqi
 */

#ifndef SRC_STATES_H_
#define SRC_STATES_H_

#include <stdio.h>
#include <stdbool.h>

void sys_init();
void AS_OFF_Handler();
void AS_Ready_Handler();
void AS_Driving_Handler();
void AS_Emergency_Handler();
void AS_Finished_Handler();
void Manual_Driving_Handler();
void run();
void updateInput(int pin);


// init element in struct to gpio input
typedef struct {
	bool MANUAL_MISSION;		// sw0 <> PA2
	bool AUTONOMOUS_MISSION;	// sw1 <> PA7
	bool ASMS;					// sw2 <> PA6
	bool BRAKE_RELEASED;		// sw3 <> PA5
	bool Delay_5s;				// sw4 <> PA4
	bool GO;					// sw6 <> PA3
	bool MISSION_FINISHED;		// sw7 <> PA1
	bool V0;					// sw8 <> PA0
	bool RES;					// sw9 <> PA8

}externInput;


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
