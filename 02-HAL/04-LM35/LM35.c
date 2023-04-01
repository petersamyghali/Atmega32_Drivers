
/*
* LM35.c
*
* Created: 08-Feb-23 2:14:54 AM
*  Author: Peter Ghali
*/
#include "../../00-LIB/Bit_Math.h"
#include "../../00-LIB/STD_TYPES.h"
#include "../../01-MCAL/03-ADC/ADC.h"
#include "LM35.h"
void LM35_init(void)
{
	ADC_enuInit();
}

void LM35_GET_Reading (ADC_enuChannel_t Cpy_ChannelNum , u16 * Add_pu16ADCValue)
{
	ADC_enuGetChannelReading_SYNC(Cpy_ChannelNum,Add_pu16ADCValue);
	#if ADC_RESOLUTION == ADC_8BITS
	*Add_pu16ADCValue =(u16)(((u32)*Add_pu16ADCValue*5000UL/*to convert it to mVolt*/)/256UL)/10;
	#elif ADC_RESOLUTION == ADC_10BITS
	*Add_pu16ADCValue =(u16)(((u32)*Add_pu16ADCValue*5000UL/*to convert it to mVolt*/)/1023UL)/10;
	#endif
	
}