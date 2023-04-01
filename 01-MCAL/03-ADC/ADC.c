/*
* ADC.c
*
* Created: 03-Feb-23 10:14:29 PM
*  Author: Peter Ghali
*/
#include "../../00-LIB/Bit_Math.h"
#include "../../00-LIB/STD_TYPES.h"
#include "ADC.h"
#include "ADC_Cfg.h"
#include "ADC_prv.h"
#include "DIO.h"

/********************************************************* VARIABLES *****************************************************/
static void ADC_Start_Conv (ADC_enuChannel_t Cpy_ChannelNum);
static void (*ADC_INT_PTR)(void) =NULL;
static volatile u16 *ADC_pu16VALUE = NULL ;
static u8 ADC_u8State = ADC_READY ;
static volatile u8 Glo_Cahin_Flag = 0 ;
static volatile u8 Glo_SingleAsyn_Flag = 0 ;
static void (*ADC_Chain_EOJ)(void) = NULL ;
static u8  * Glo_Chain_Channel_Num = NULL ;

static volatile u16 *Glo_Chain_Result_Array =NULL ;
static u8 Glo_Chain_Lenght = 0;
static volatile u8 Glo_Chain_Index = 0 ;

/********************************************************** MACROS ********************************************************/
#define ZERO			0
#define TIME_OUT_TRIALS 10000
#define AUTO_TRIG_MASK	0b11100000
static ADC_enuErrorStatus_t LOC_Error_Status = ADC_enuNotOK ;
static u8 LOC_Buffer = ZERO ;
static u16 LOC_TimeOut = ZERO ;
ADC_enuErrorStatus_t ADC_enuInit (void)
{
	LOC_Error_Status = ADC_enuOK ;
	LOC_Buffer = ADMUX ;
	LOC_Buffer &= ADC_REF_MASK ;
	#if ADC_REF == ADC_REF_AREF
	LOC_Buffer |= ADC_REF_AREF ;
	#elif ADC_REF == ADC_REF_INTERNAL
	LOC_Buffer |= ADC_REF_INTERNAL ;
	#elif ADC_REF == ADC_REF_AVCC
	LOC_Buffer |= ADC_REF_AVCC ;
	#else
	LOC_Error_Status = ADC_enuInavalidReference ;
	#endif
	ADMUX = LOC_Buffer ;
	LOC_Buffer = 0 ;
	
	#if ADC_LEF_ADJ == ENABLE
	ADMUX|=(ENABLE<<ADC_ADJUST_LEFT);
	#elif ADC_LEF_ADJ == DISABLE
	ADMUX &=~(ENABLE<<ADC_ADJUST_LEFT);
	#else
	LOC_Error_Status = ADC_enuNotOK ;
	#endif
	
	
	
	LOC_Buffer = ADCSRA ;
	LOC_Buffer &= ADC_PRE_SCALER_MASK ;
	#if ADC_PRE_SCALER == ADC_PRE_SCALER_2
	LOC_Buffer |=ADC_PRE_SCALER_2;
	#elif	ADC_PRE_SCALER == ADC_PRE_SCALER_4
	LOC_Buffer |=ADC_PRE_SCALER_4;
	#elif	ADC_PRE_SCALER == ADC_PRE_SCALER_8
	LOC_Buffer |=ADC_PRE_SCALER_8;
	#elif	ADC_PRE_SCALER == ADC_PRE_SCALER_16
	LOC_Buffer |=ADC_PRE_SCALER_16;
	#elif	ADC_PRE_SCALER == ADC_PRE_SCALER_32
	LOC_Buffer |=ADC_PRE_SCALER_32;
	#elif	ADC_PRE_SCALER == ADC_PRE_SCALER_64
	LOC_Buffer |=ADC_PRE_SCALER_64;
	#elif	ADC_PRE_SCALER == ADC_PRE_SCALER_128
	LOC_Buffer |=ADC_PRE_SCALER_128;
	#else
	LOC_Error_Status = ADC_enuInavalidPreScaler ;
	#endif
	ADCSRA = LOC_Buffer ;
	
	
	#if ADC_INTERRUPT == ENABLE
	ADCSRA |=(ENABLE << ADC_INTERRUPT_ENABLE );
	#elif ADC_INTERRUPT == DISABLE
	ADCSRA &=~(ENABLE << ADC_INTERRUPT_ENABLE );
	#elif
	LOC_Error_Status = ADC_enuInavalidMode ;
	#endif
	
	
	#if ADC_TRIGGER == ENABLE
	ADCSRA |=(ENABLE << ADC_AUTO_TRIGGER );
	#elif ADC_TRIGGER == DISABLE
	ADCSRA &=~(ENABLE << ADC_AUTO_TRIGGER );
	#elif
	LOC_Error_Status = ADC_enuInavalidMode ;
	#endif
	
	ADCSRA |= (ENABLE << ADC_ENABLE);
	return LOC_Error_Status;
}


ADC_enuErrorStatus_t ADC_enuDisable (void)
{
	LOC_Error_Status = ADC_enuOK ;
	ADCSRA &= ~(ENABLE << ADC_ENABLE);
	return LOC_Error_Status;
}


ADC_enuErrorStatus_t ADC_enuGetChannelReading_SYNC (ADC_enuChannel_t Cpy_ChannelNum , u16 * Add_pu16ADCValue )
{
	LOC_Error_Status = ADC_enuOK ;
	if (ADC_u8State == ADC_READY)
	{
		LOC_TimeOut = 0 ;
		if (Add_pu16ADCValue == NULL )
		{
			LOC_Error_Status = ADC_enuNullPointer ;
		}
		else
		{
			ADC_u8State = ADC_BUSY ;
			LOC_Buffer = ADMUX ;
			LOC_Buffer &= ADC_MUX_CLAER_MASK ;
			LOC_Buffer |= Cpy_ChannelNum ;
			ADMUX = LOC_Buffer ;
			ADCSRA|=(ENABLE << ADC_START_CONVERSION);
			while ( GET_BIT(ADCSRA,ADC_INTERRUPT_FLAG) == DISABLE && LOC_TimeOut < TIME_OUT_TRIALS)
			{
				LOC_TimeOut++;
			}
			if (GET_BIT(ADCSRA,ADC_INTERRUPT_FLAG) == ENABLE)
			{
				
				SET_BIT(ADCSRA,ADC_INTERRUPT_FLAG);
				#if ADC_RESOLUTION == ADC_8BITS
				#if ADC_LEF_ADJ == ENABLE
				*Add_pu16ADCValue = ADCH ;
				#elif ADC_LEF_ADJ == DISABLE
				*Add_pu16ADCValue = ((ADCL>>2))|(ADCH<<6) ;
				#endif
				#elif ADC_RESOLUTION == ADC_10BITS
				#if ADC_LEF_ADJ == ENABLE
				*Add_pu16ADCValue = ADC_VALUE ;
				#elif ADC_LEF_ADJ = DISABLE
				*Add_pu16ADCValue = ADC_VALUE;
				#endif
				#else
				LOC_Error_Status = ADC_enuInavalidMode ;
				#endif
				ADC_u8State  = ADC_READY ;
				
			}
			else
			{
				
				LOC_Error_Status = ADC_enuTimeOut;
			}
			
		}
	}
	
	else
	{
		LOC_Error_Status = ADC_enuBusy ;
	}
	
	return LOC_Error_Status;
}


ADC_enuErrorStatus_t ADC_enuGetChannelReading_ASYNC (ADC_enuChannel_t Cpy_ChannelNum , void (*Cpy_pvADCINT)(void), u16 * Add_pu16ADCValue )
{
	LOC_Error_Status = ADC_enuOK ;
	if (ADC_u8State == ADC_READY)
	{
		LOC_TimeOut = 0 ;
		if (Add_pu16ADCValue == NULL || Cpy_pvADCINT == NULL)
		{
			LOC_Error_Status = ADC_enuNullPointer ;
		}
		else
		{
			ADC_u8State = ADC_BUSY ;
			LOC_Buffer = ADMUX ;
			LOC_Buffer &= ADC_MUX_CLAER_MASK ;
			LOC_Buffer |= Cpy_ChannelNum ;
			ADMUX = LOC_Buffer ;
			ADC_INT_PTR  = Cpy_pvADCINT;
			ADC_pu16VALUE = Add_pu16ADCValue ;
			SET_BIT(ADCSRA,ADC_INTERRUPT_ENABLE);
			
			ADCSRA|=(ENABLE << ADC_START_CONVERSION);
			Glo_SingleAsyn_Flag = ENABLE ;
			
		}
	}
	else
	{
		LOC_Error_Status = ADC_enuBusy ;
	}
	
	return LOC_Error_Status;

}

ADC_enuErrorStatus_t ADC_enuAutoTrigger (ADC_enuChannel_t Cpy_ChannelNum  , ADC_enuAutoTrigger_t Cpy_Trigger_Source , void (*Cpy_pvADCINT)(void), u16 * Add_pu16ADCValue)
{
	u8 LOC_REG = 0 ;
	LOC_Error_Status = ADC_enuOK ;
	if (GET_BIT(ADCSRA,ADC_AUTO_TRIGGER) == 0)
	{
		LOC_Error_Status = ADC_enuInavalidMode ;
	}
	if (Add_pu16ADCValue == NULL || Cpy_pvADCINT == NULL)
	{
		LOC_Error_Status = ADC_enuNullPointer ;
	}
	else
	{
		if (Cpy_Trigger_Source > ADC_enuTrigger_Sources)
		{
			LOC_Error_Status =	 ADC_enuInavalidMode ;
		}
		else
		{
			LOC_REG = SFIOR ;
			LOC_REG &=~(AUTO_TRIG_MASK);
			LOC_REG = (Cpy_Trigger_Source << ADC_AUTO_TRIGGER);
			SFIOR = LOC_REG ;
			ADC_INT_PTR  = Cpy_pvADCINT;
			ADC_pu16VALUE = Add_pu16ADCValue ;
		}
	}
	
	return LOC_Error_Status ;
}



ADC_enuErrorStatus_t ADC_enuGetReading (u16 * Add_pu16ADCValue )
{
	LOC_Error_Status = ADC_enuOK ;
	LOC_TimeOut = 0 ;
	if (Add_pu16ADCValue == NULL )
	{
		LOC_Error_Status = ADC_enuNullPointer ;
	}
	else
	{
		SET_BIT(ADCSRA,ADC_INTERRUPT_FLAG);
		#if ADC_RESOLUTION == ADC_8BITS
		#if ADC_LEF_ADJ == ENABLE
		*Add_pu16ADCValue = ADCH ;
		#elif ADC_LEF_ADJ == DISABLE
		*Add_pu16ADCValue = ((ADCL>>2))|(ADCH<<6) ;
		#endif
		
		#elif ADC_RESOLUTION == ADC_10BITS
		#if ADC_LEF_ADJ == ENABLE
		*Add_pu16ADCValue = ADC_VALUE ;
		#elif ADC_LEF_ADJ = DISABLE
		*Add_pu16ADCValue = ADC_VALUE;
		#endif
		
		#else
		LOC_Error_Status = ADC_enuInavalidMode ;
		#endif
		
	}

	return LOC_Error_Status;
}
ADC_enuErrorStatus_t ADC_enuStart_Chain_Asynch (ADC_Chain_t * Add_puChain)
{
	if (ADC_u8State == ADC_BUSY )
	{
		
	}
	else if (ADC_u8State == ADC_READY )
	{
		ADC_u8State = ADC_BUSY ;
		Glo_Chain_Index = 0 ;
		LOC_Error_Status = ADC_enuOK ;

		ADC_Chain_EOJ = Add_puChain->EOJ;

		Glo_Chain_Result_Array = Add_puChain->Result;
		Glo_Chain_Lenght = Add_puChain->Lenght;
		Glo_Cahin_Flag = ENABLE ;
		Glo_Chain_Channel_Num = Add_puChain->ChannelsID;
		SET_BIT(ADCSRA,ADC_INTERRUPT_ENABLE);
		ADC_Start_Conv(Glo_Chain_Channel_Num[Glo_Chain_Index]) ;

		
		
		
		
	}
	return LOC_Error_Status;
	
}

void ADC_Start_Conv (ADC_enuChannel_t Cpy_ChannelNum)
{
	
	LOC_Buffer = ADMUX ;
	LOC_Buffer &= ADC_MUX_CLAER_MASK ;
	LOC_Buffer |= Cpy_ChannelNum ;
	ADMUX = LOC_Buffer ;
	ADCSRA|=(ENABLE << ADC_START_CONVERSION);
}


INTERRUPT_SERVICE_ROUTINE_(16)
{

	if (Glo_SingleAsyn_Flag)
	{
		
		if (ADC_INT_PTR != NULL && ADC_pu16VALUE != NULL)
		{
			#if ADC_RESOLUTION == ADC_10BITS
			*ADC_pu16VALUE = ADC_VALUE ;
			#elif ADC_RESOLUTION == ADC_8BITS
			#if ADC_LEF_ADJ == ENABLE
			*ADC_pu16VALUE = ADCH ;
			#elif ADC_LEF_ADJ == DISABLE
			*ADC_pu16VALUE = ((ADCL>>2))|(ADCH<<6) ;
			#endif
			#endif
			ADC_u8State = ADC_READY ;
			Glo_SingleAsyn_Flag = DISABLE ;
		}
		else
		{
			
		}
		
	}
	else if (Glo_Cahin_Flag)
	{
		
		if (Glo_Chain_Index == Glo_Chain_Lenght)
		{
			
			ADC_Chain_EOJ();
			Glo_Cahin_Flag = DISABLE ;
			ADC_u8State = ADC_READY ;
			//Glo_Chain_Index=0;
		}
		else
		{
			
			#if ADC_RESOLUTION == ADC_10BITS
			Glo_Chain_Result_Array[Glo_Chain_Index] = ADC_VALUE ;
			#elif ADC_RESOLUTION == ADC_8BITS
			#if ADC_LEF_ADJ == ENABLE
			Glo_Chain_Result_Array[Glo_Chain_Index] =  ADCH;
			#elif ADC_LEF_ADJ == DISABLE
			Glo_Chain_Result_Array[Glo_Chain_Index] = ((ADCL>>2))|(ADCH<<6) ;
			#endif
			#endif
			
			
			Glo_Chain_Index++;
			ADC_Start_Conv(Glo_Chain_Channel_Num[Glo_Chain_Index]);
			
		}
	}
	else
	{
		
	}
	
	
}