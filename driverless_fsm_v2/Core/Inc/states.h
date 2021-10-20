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
	bool MANUAL_MISSION;		// sw0 <> PA0 <> GPIO 0
	bool AUTONOMOUS_MISSION;	// sw1 <> PA1 <> GPIO 1
	bool ASMS;					// sw2 <> PA3 <> GPIO 3
	bool BRAKE_RELEASED;		// sw3 <> PA4 <> GPIO 4
	bool Delay_5s;				// sw4 <> PA11<> GPIO 11
	bool GO;					// sw5 <> PB5 <> GPIO 5
	bool MISSION_FINISHED;		// sw6 <> PA7 <> GPIO 7
	bool V0;					// sw7 <> PA2 <> GPIO 2
	bool RES;					// sw8 <> PA8 <> GPIO 8

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
