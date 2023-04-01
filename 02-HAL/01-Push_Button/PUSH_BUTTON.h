
#ifndef PUSH_BUTTON_H_
#define PUSH_BUTTON_H_

#include "PUSH_BUTTON.h"
#include "PUSH_BUTTON_Cfg.h"
#include "../../00-LIB/STD_TYPES.h"

#define BUTTON_PULL_UP   0
#define BUTTON_PULL_DOWN 1

typedef enum{
	PushButton_enuOk = 0,
	PushButton_enuNotOk,
	PushButton_enuNullPtr,
	PushButton_enuInvalidMode , 
	PushButton_enuInvalidPINNumber,
}PushButton_enuErrorStatus;

typedef enum{
	
PushButton_Pressed , 
PushButton_Not_Pressed 
}PushButton_t;

extern PushButton_tenuPushButtonNumber ; 

PushButton_enuErrorStatus PushButton_enuInit(void);

PushButton_enuErrorStatus PushButton_enuGetState(PushButton_tenuPushButtonNumber Cpy_u8Pin, PushButton_t* Add_u8ButtonVal);

#endif /* Switch_H_ */