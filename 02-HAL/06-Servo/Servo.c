/*
* Servo.c
*
* Created: 09-Mar-23 5:52:53 PM
*  Author: Peter Ghali
*/
#include "Bit_Math.h"
#include "STD_TYPES.h"
#include "Servo.h"
#include "../../01-MCAL/04-TIM/01-TIM1/TIM1.h"

#define SERVO_0				750	
#define SERVO_180			2500
#define SERVO_RATIO			10

Servo_enuErrorStatus_t Servo_Init(void)
{
	Servo_enuErrorStatus_t  Error_Status = Servo_Ok ;

	TIM1_enuSet_Mode(TIM1_Fast_PWM_Top_ICR1);
	TIM1_enuSetCLK(TIM1_Pre_Scaler_8);
	TIM1_enuSet_ICR_Value(20000);
	TIM1_enuSetC_OC1_Pin(Clear_OC1A_on_compare_match_set_OC1A_at_BOTTOM);
	TIM1_enuStart();
	return Error_Status ;

}

Servo_enuErrorStatus_t Servo_SetDegree(u8 Cpy_Degree)
{
	Servo_enuErrorStatus_t  Error_Status = Servo_Ok ;
	u16 Degree = 0 ;
	Degree  = SERVO_0+(Cpy_Degree*SERVO_RATIO) ; 
	TIM1_enuSet_OCA_Value(Degree);
	return Error_Status ;
}