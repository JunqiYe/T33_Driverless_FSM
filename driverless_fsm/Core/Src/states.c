/*
 * states.c
 *
 *  Created on: Jul 30, 2021
 *      Author: Junqi
 */

#include "states.h"
#include <stdbool.h>

// init element in struct to gpio input
typedef struct {
	bool MANUAL_MISSION;
	bool AUTONOMOUS_MISSION;
	bool ASMS;
	bool BRAKE_RELEASED;
	bool Delay_5s;
	bool GO;
	bool MISSION_FINISHED;
	bool V0;
	bool RES;

}externInput;

typedef struct {
	TS_state ts;
	R2D_state r2d;
	SA_state sa;
	SB_state sb;
	EBS_state ebs;
	ASSI_state assi;
} autonomousSystem;

autonomousSystem topLevel = {0};
externInput xi = {0};

void sys_init() {
	topLevel.ts = ts_off;
	topLevel.r2d = r2d_off;
	topLevel.sa = sa_unavaliable;
	topLevel.sb = sb_unavaliable;
	topLevel.assi = assi_OFF;
}

// TODO: best to make EBS and RES interrupt based

void AS_OFF_Handler() {

}

void AS_Ready_Handler() {

}

void AS_Driving_Handler() {

}

void AS_Emergency_Handler() {

}

void AS_Finished_Handler() {

}

void Manual_Driving_Handler() {

}

void run() {
	sys_init();
	autonomousSystemStates currentState;
	autonomousSystemStates nextState = AS_Off;


	while (1) {
		switch (nextState) {
		case AS_Off:

			if (xi.MANUAL_MISSION && topLevel.ebs == ebs_unavaliable && xi.ASMS && topLevel.ts == ts_on) {
				nextState = Manual_Driving;
			}

			if (xi.AUTONOMOUS_MISSION && topLevel.ebs == ebs_armed && xi.ASMS && topLevel.ts == ts_on) {
				nextState = AS_Ready;
			}
			break;

		case AS_Ready:
			if (xi.ASMS && xi.BRAKE_RELEASED) {
				nextState = AS_Off;
			}
			if (xi.Delay_5s && xi.GO) {
				nextState = AS_Driving;
			}
			if (topLevel.ebs == ebs_activated) {
				nextState = AS_Emergency;
			}
			break;

		case Manual_Driving:
			if (topLevel.ts == ts_off) {
				nextState = AS_Off;
			}
			break;

		case AS_Driving:
			if (xi.MISSION_FINISHED && xi.V0) {
				nextState = AS_Finished;
			}
			if (topLevel.ebs == ebs_activated) {
				nextState = AS_Emergency;
			}
			break;

		case AS_Emergency:
			if (topLevel.ebs == ebs_activated && xi.ASMS && xi.BRAKE_RELEASED) {
				nextState = AS_Off;
			}
			break;

		case AS_Finished:
			if (xi.ASMS && xi.BRAKE_RELEASED) {
				nextState = AS_Off;
			}
			if (xi.RES) {
				nextState = AS_Emergency;
			}
			break;


		}
		currentState = nextState;
		HAL_Delay(100);
	}

}
