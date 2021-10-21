/*
 * states.c
 *
 *  Created on: Jul 30, 2021
 *      Author: Junqi
 */

#include "states.h"
#include <stdbool.h>
#include "LCD16x2.h"
#include "cmsis_os.h"

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
	xi.ASMS = false;
	xi.AUTONOMOUS_MISSION = false;

	topLevel.ts = ts_on;
	topLevel.r2d = r2d_off;
	topLevel.sa = sa_unavaliable;
	topLevel.sb = sb_unavaliable;
	topLevel.assi = assi_OFF;
	topLevel.ebs = ebs_armed;
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

// Need to be atomic
void update_EXIT(int pin, bool state) {

	taskENTER_CRITICAL();

	switch (pin) {
	case 0:
		xi.MANUAL_MISSION = state;
		break;
	case 1:
		xi.AUTONOMOUS_MISSION = state;
		break;
	case 2:
		xi.V0 = state;
		break;
	case 3:
		xi.ASMS = state;
		break;
	case 4:
		xi.BRAKE_RELEASED = state;
		break;
	case 5:
		xi.GO = state;
		break;
	case 7:
		xi.MISSION_FINISHED = state;
		break;
	case 8:
		xi.RES = state;
		break;
	case 11:
		xi.Delay_5s = state;
		break;
	}

	taskEXIT_CRITICAL();
}

void updateInput(int pin) {

//	LCD_Clear();
//	LCD_Set_Cursor(1, 1);
//	LCD_Write_String("pin");
//	LCD_Set_Cursor(1, 5);
//	LCD_Write_Char('0' + pin%10);
//	if (pin > 10) {
//		LCD_Set_Cursor(1, 6);
//		LCD_Write_Char('0' + pin/10);
//	}

}
void LCD_Print_current_state (autonomousSystemStates currentState) {
	LCD_Clear();
	LCD_Set_Cursor(1, 1);

	switch (currentState) {
	case AS_Off:
		LCD_Write_String("OFF");
		break;
	case AS_Ready:
		LCD_Write_String("Ready");
		break;
	case Manual_Driving:
		LCD_Write_String("Manual");
		break;
	case AS_Driving:
		LCD_Write_String("Driving");
		break;
	case AS_Emergency:
		LCD_Write_String("Emergency");
		break;
	case AS_Finished:
		LCD_Write_String("Finished");
		break;
	}
}

void run() {
	sys_init();
	autonomousSystemStates currentState;
	autonomousSystemStates nextState = AS_Off;


	while (1) {
//		if (xi.MANUAL_MISSION == false) {
//			LCD_Clear();
//			LCD_Set_Cursor(1, 1);
//			LCD_Write_String("manual false");
//		} else {
//			LCD_Clear();
//			LCD_Set_Cursor(1, 1);
//			LCD_Write_String("manual true");
//		}
		LCD_Print_current_state(currentState);

		switch (currentState) {
		case AS_Off:

			if (xi.MANUAL_MISSION && topLevel.ebs == ebs_unavaliable && xi.ASMS && topLevel.ts == ts_on) {
				nextState = Manual_Driving;
			}

			if (xi.AUTONOMOUS_MISSION && topLevel.ebs == ebs_armed && xi.ASMS && topLevel.ts == ts_on) {
				nextState = AS_Ready;
			}
			break;

		case AS_Ready:
			if (!xi.ASMS && xi.BRAKE_RELEASED) {
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
		osDelay(100);
	}

}
