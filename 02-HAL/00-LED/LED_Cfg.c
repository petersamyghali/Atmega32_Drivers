#include "LED.h"
#include "LED_Cfg.h"

#include "DIO.h"
//An array of struct(LED_Type & LED_PIN) for each pin 
const LED_strLEDCfg_t LED_strLEDCfg [NUMBER_OF_LEDS] =
{
	[LED0 ] ={
		.LED_Type = LED_enuActiveHigh , 
		.LED_PIN = DIO_enuPORTA_Pin0,
	},
	
	[LED1 ] ={
		.LED_Type = LED_enuActiveHigh ,
		.LED_PIN = DIO_enuPORTA_Pin1,
	},
	
	[LED2] ={
		.LED_Type = LED_enuActiveHigh ,
		.LED_PIN = DIO_enuPORTA_Pin2,
	},
	/*
	[LED_enu_LED3 ] ={
		.LED_Type = LED_enuActiveHigh ,
		.LED_PIN = DIO_enuPORTA_Pin3,
	},
	
	[LED_enu_LED4 ] ={
		.LED_Type = LED_enuActiveHigh ,
		.LED_PIN = DIO_enuPORTA_Pin4,
	},
	
	[LED_enu_LED5 ] ={
		.LED_Type = LED_enuActiveHigh ,
		.LED_PIN = DIO_enuPORTA_Pin5,
	},
	
	[LED_enu_LED6 ] ={
		.LED_Type = LED_enuActiveHigh ,
		.LED_PIN = DIO_enuPORTA_Pin6,
	},
	
	[LED_enu_LED7 ] ={
		.LED_Type = LED_enuActiveHigh ,
		.LED_PIN = DIO_enuPORTA_Pin7,
	},
	
	*/
	
};