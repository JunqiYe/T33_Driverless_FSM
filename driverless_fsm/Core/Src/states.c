/*
 * states.c
 *
 *  Created on: Jul 30, 2021
 *      Author: Junqi
 */

#include "states.h"
#define MANUAL_MISSION 0
#define AUTONOMOUS_MISSION 0
#define ASMS 0
#define BRAKE_RELEASED 0
#define Delay_5s 0
#define GO 0
#define MISSION_FINISHED 0
#define V0 0
#define RES 0

typedef struct {
	TS_state ts;
	R2D_state r2d;
	SA_state sa;
	SB_state sb;
	EBS_state ebs;
	ASSI_state assi;
} autonomousSystem;

extern autonomousSystem topLevel;

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

			if (MANUAL_MISSION && topLevel.ebs == ebs_unavaliable && ASMS && topLevel.ts == ts_on) {
				nextState = Manual_Driving;
			}

			if (AUTONOMOUS_MISSION && topLevel.ebs == ebs_armed && ASMS && topLevel.ts == ts_on) {
				nextState = AS_Ready;
			}
			break;

		case AS_Ready:
			if (ASMS && BRAKE_RELEASED) {
				nextState = AS_Off;
			}
			if (Delay_5s && GO) {
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
			if (MISSION_FINISHED && V0) {
				nextState = AS_Finished;
			}
			if (topLevel.ebs == ebs_activated) {
				nextState = AS_Emergency;
			}
			break;

		case AS_Emergency:
			if (topLevel.ebs == ebs_activated && ASMS && BRAKE_RELEASED) {
				nextState = AS_Off;
			}
			break;

		case AS_Finished:
			if (ASMS && BRAKE_RELEASED) {
				nextState = AS_Off;
			}
			if (RES) {
				nextState = AS_Emergency;
			}
			break;


		}
		currentState = nextState;
	}

}
