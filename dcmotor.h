/*
 * dcmotor.h
 *
 *  Created on: Oct 14, 2023
 *      Author: hp
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define IN1 0
#define IN2 1
#define MotorPort PORTB

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum {
	OFF, CW, ACW
}DcMotor_State;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void DcMotor_init(void);
void DcMotor_rotate(DcMotor_State state, uint8 speed);
#endif /* DCMOTOR_H_ */
