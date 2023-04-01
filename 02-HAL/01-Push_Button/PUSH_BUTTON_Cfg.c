#include "PUSH_BUTTON_Cfg.h"
#include "../../01-MCAL/00-DIO/DIO.h"
const PushButton_strPushButtonCfg_t PushButton_strPushButtonCfg [PushButton_Numbers] =
{			
	[PushButton_enu_PushButton0] = {
		.PushButton_PIN = DIO_enuPORTC_Pin0 , 
		.PushButton_Type = PushButton_enuActiveLow ,
	} , 
	
	[PushButton_enu_PushButton1] = {
		.PushButton_PIN = DIO_enuPORTC_Pin1 ,
		.PushButton_Type = PushButton_enuActiveLow ,
	} ,
	
	/*PushButton_Type*/			/*PushButton_Number*/
		//	 {PushButton_enuActiveHigh	,	DIO_enuPORTB_Pin0},
//	/*PushButton1*/{PushButton_enuActiveHigh	,	DIO_enuPORTB_Pin1},
};