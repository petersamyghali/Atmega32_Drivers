/*
* Servo.h
*
* Created: 09-Mar-23 5:53:11 PM
*  Author: Peter Ghali
*/


#ifndef SERVO_H_
#define SERVO_H_


typedef enum
{
	Servo_Ok,
	Servo_Not_Ok ,
	Servo_Wrong_Degree ,
}Servo_enuErrorStatus_t;

Servo_enuErrorStatus_t Servo_Init(void);

/*
From 0 to 180
*/
Servo_enuErrorStatus_t Servo_SetDegree(u8 Cpy_Degree);

#endif /* SERVO_H_ */