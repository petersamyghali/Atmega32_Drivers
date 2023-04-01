
#ifndef LED_CFG_H
#define LED_CFG_H

#include "../../../../00-LIB/STD_TYPES.h"

#define NUMBER_OF_LEDS	8
#define HIGH	1
#define	LOW		0

typedef enum
{
	LED_enuActiveHigh = 0  ,
	LED_enuActiveLow ,
}LED_tenuLEDType;

typedef struct
{
	LED_tenuLEDType LED_Type ; 
	LED_tenuLEDNumber LED_Number ; 
}LED_strLEDCfg_t;

extern const LED_strLEDCfg_t LED_strLEDCfg [NUMBER_OF_LEDS];
#endif