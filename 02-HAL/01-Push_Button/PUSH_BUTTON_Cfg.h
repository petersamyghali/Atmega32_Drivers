
#ifndef PUSH_BUTTON_CFG_H_
#define PUSH_BUTTON_CFG_H_

#define HIGH				1
#define	LOW					0

typedef enum {
	
	PushButton_enu_PushButton0 = 0 ,
	PushButton_enu_PushButton1 ,
	PushButton_Numbers ,
}PushButton_tenuPushButtonNumber;

typedef enum
{
	PushButton_enuActiveHigh = 0  ,
	PushButton_enuActiveLow ,
	
}PushButton_tenuPushButtonType;

typedef struct
{
	PushButton_tenuPushButtonType PushButton_Type ;
	PushButton_tenuPushButtonNumber PushButton_PIN ;
}PushButton_strPushButtonCfg_t;



extern const PushButton_strPushButtonCfg_t PushButton_strPushButtonCfg [PushButton_Numbers];

#endif