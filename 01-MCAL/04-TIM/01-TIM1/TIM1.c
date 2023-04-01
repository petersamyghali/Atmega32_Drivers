/*
* TIM1.c
*
* Created: 26-Feb-23 1:24:29 PM
*  Author: Peter Ghali
*/
#include "STD_TYPES.h"
#include "Bit_Math.h"

#include "TIM1.h"
#include "TIM1_Cfg.h"
#include "TIM1_Prv.h"

//static
/*
typedef void (*TIM1_void_call_Back)(void) ;

void TIM1_void_call_Back_CTCA	(void){}
void TIM1_void_call_Back_CTCB	(void)
{

}
void TIM1_void_call_Back_OVF	(void){}
void TIM1_void_call_Back_ICU   	(void){}


static TIM1_void_call_Back  TIM1_CALL_BACK[4]=
{

TIM1_void_call_Back_CTCA,
TIM1_void_call_Back_CTCB,
TIM1_void_call_Back_OVF ,
TIM1_void_call_Back_ICU
};

*/
static void (*TIM1_void_call_Back_CTCA)(void)= NULL;
static void (*TIM1_void_call_Back_CTCB)(void)= NULL;
static void (*TIM1_void_call_Back_OVF)(void)= NULL;
static void (*TIM1_void_call_Back_ICU)(void)= NULL;

static  volatile  int Timer1_Overflow_Counts  = 0;

static u8 CLK_Global = 0 ;

#define MAX_TIM1_VALUE				65535
#define CLK_CLR_MSK					0b11111000

#define		WGM10_POS				0
#define		WGM11_POS				1
#define		WG_TCCRA_CLR_MASK		0b11111100
#define		WG_TCCRA_GET_MASK		0b00000011
#define		COM1A_TCCRA_CLR_MASK	0b00111111

#define		WGM12_POS				3
#define		WGM13_POS				4
#define		WG_TCCRB_CLR_MASK		0b11100111
#define		WG_TCCRB_GET_MASK		0b00001100
#define		WG_TCCRB_GET			2
#define		COM1B_MIN_VALUE			16
#define		COM1B_TCCRA_CLR_MASK	0b11001111



TIM1_Error_Status_t TIM1_enuSet_Mode (TIM1_Modes_t CPY_Mode)
{
	u8 WG_TCCR1A = 0 , WG_TCCR1B = 0 ;
	u8 Temp_Reg = 0 ;
	TIM1_Error_Status_t  Error_Status = TIM1_OK ;
	WG_TCCR1A = CPY_Mode & WG_TCCRA_GET_MASK ;
	WG_TCCR1B= (CPY_Mode & WG_TCCRB_GET_MASK )>>WG_TCCRB_GET ;
	
	Temp_Reg = TCCR1A ;
	Temp_Reg &= WG_TCCRA_CLR_MASK;
	Temp_Reg |= (WG_TCCR1A<< WGM10_POS);
	TCCR1A |= Temp_Reg ;
	
	
	Temp_Reg = TCCR1B ;
	Temp_Reg &= WG_TCCRB_CLR_MASK;
	Temp_Reg |= WG_TCCR1B<< WGM12_POS;
	TCCR1B |= Temp_Reg ;
	
	return Error_Status ;
}

TIM1_Error_Status_t TIM1_enuSetC_OC1_Pin (TIM1_OC1_t Cpy_Mode)
{
	TIM1_Error_Status_t Error_Status = TIM1_OK ;
	u8 Temp_Reg = TCCR1A ;
	if (Cpy_Mode >=COM1B_MIN_VALUE)
	{
		
		Temp_Reg |=Cpy_Mode ;
		
	}
	else
	{
		Temp_Reg&=COM1A_TCCRA_CLR_MASK;
		Temp_Reg |=Cpy_Mode ;
	}
	
	TCCR1A = Temp_Reg ;
	return Error_Status ;
}

TIM1_Error_Status_t TIM1_enuICU_Trigger(TIM1_enuICU_Trigger_t Cpy_ICE_Trigger)
{
	TIM1_Error_Status_t Error_Status = TIM1_OK ;

	if (Cpy_ICE_Trigger ==ICU_Trigger_Falling_Edge)
	{
	CLR_BIT(TCCR1B, TCCR1B_ICES1) ;
	}
	else if (Cpy_ICE_Trigger == ICU_Trigger_Rising_Edge)
	{
	SET_BIT(TCCR1B, TCCR1B_ICES1) ;
	}
	else 
	{
		Error_Status  = TIM1_Not_Ok ; 
	}

	return Error_Status ;
}

TIM1_Error_Status_t TIM1_enuSetCLK (TIM1_Clock_t Cpy_CLK)
{
	TIM1_Error_Status_t Error_Status = TIM1_OK ;
	CLK_Global= Cpy_CLK ;
	return Error_Status ;
}

TIM1_Error_Status_t TIM1_enuSet_Timer_Value (u16 Cpy_Value )
{
	TIM1_Error_Status_t Error_Status = TIM1_OK ;
	if (Cpy_Value > MAX_TIM1_VALUE)
	{
		Error_Status = TIM1_Not_Ok ;
	}
	else
	{
		TCNT1= Cpy_Value ;
	}

	return Error_Status ;
}
TIM1_Error_Status_t TIM1_enuGet_Timer_ICR_Value (u16 *Cpy_Value )
{
	TIM1_Error_Status_t Error_Status = TIM1_OK ;
	if (Cpy_Value == NULL)
	{
		Error_Status = TIM1_Not_Ok ;
	}
	else
	{
		*Cpy_Value = ICR1 ;
	}
	return Error_Status ;
}

void TIM1_enuSet_Timer_OVFs_Count (u16  Cpy_Value)
{
	 Timer1_Overflow_Counts = Cpy_Value  ;
}

TIM1_Error_Status_t TIM1_enuGet_Timer_OVFs_Count ( volatile u16 * Cpy_Value)
{
	TIM1_Error_Status_t Error_Status = TIM1_OK ;
	if (Cpy_Value == NULL)
	{
		Error_Status = TIM1_NULL_PTR ;
	}
	else
	{
		*Cpy_Value  = Timer1_Overflow_Counts ;
	}
	return Error_Status ;
}
TIM1_Flag TIM1_enuGet_Timer_Flag  (TIM1_INT_EN_t Cpy_Flag)
{
	return (GET_BIT(TIFR,Cpy_Flag));
}
TIM1_Error_Status_t TIM1_enuGet_Timer_Value (u16 *  Cpy_Value )
{
	TIM1_Error_Status_t Error_Status = TIM1_OK ;
	if (Cpy_Value == NULL)
	{
		Error_Status = TIM1_NULL_PTR ;
	}
	else
	{
		*Cpy_Value  = TCNT1 ;
	}
	return Error_Status ;
}


void TIM1_enuStart(void)
{
	
	u8 Temp_Reg = 0 ;
	Temp_Reg=TCCR1B;
	Temp_Reg&=CLK_CLR_MSK;
	Temp_Reg|=CLK_Global;
	TCCR1B = Temp_Reg ;
}

void TIM1_vidSetPreloadValue(u16 Copy_u8Preload)
{
	TCNT1 = Copy_u8Preload ;
}

void TIM1_enuSet_OCA_Value (u16 Cpy_u16Value)
{
	OCR1A =Cpy_u16Value ;
}

void TIM1_enuSet_OCB_Value (u16 Cpy_u16Value)
{
	OCR1B =Cpy_u16Value ;
	
}
void TIM1_enuSet_ICR_Value (u16 Cpy_u16Value)
{
	ICR1=Cpy_u16Value ;
}

TIM1_Error_Status_t TIM_enuRegisterCallback_OVF( void (*TIM0cbf_t)(void))
{

	TIM1_Error_Status_t Error_Status = TIM1_OK ;

	SET_BIT(TIMSK,TIMSK_TOIE1);


	if(TIM0cbf_t != NULL)
	{
		TIM1_void_call_Back_OVF = TIM0cbf_t ;
	}
	else
	{
		Error_Status = TIM1_NULL_PTR ;
	}
	return Error_Status ;
}


TIM1_Error_Status_t TIM1_enuRegisterCallback_CTC_A( void (*TIM1cbf_t)(void))
{

	TIM1_Error_Status_t Error_Status = TIM1_OK ;

	SET_BIT(TIMSK,TIMSK_OCIE1A);
	if(TIM1cbf_t != NULL)
	{
		TIM1_void_call_Back_CTCA = TIM1cbf_t ;
	}
	else
	{
		Error_Status = TIM1_NULL_PTR ;
	}
	return Error_Status;
}

TIM1_Error_Status_t TIM1_enuRegisterCallback_CTC_B( void (*TIM1cbf_t)(void))
{
	TIM1_Error_Status_t Error_Status = TIM1_OK ;

	SET_BIT(TIMSK,TIMSK_OCIE1B);
	if(TIM1cbf_t != NULL)
	{
		TIM1_void_call_Back_CTCB = TIM1cbf_t ;
	}
	else
	{
		Error_Status = TIM1_NULL_PTR ;
	}
	return Error_Status;
}

TIM1_Error_Status_t TIM1_enuRegisterCallback_OVF( void (*TIM1cbf_t)(void))
{
	TIM1_Error_Status_t Error_Status = TIM1_OK ;

	SET_BIT(TIMSK,TIMSK_TICIE1);
	if(TIM1cbf_t != NULL)
	{
		TIM1_void_call_Back_OVF = TIM1cbf_t ;
	}
	else
	{
		Error_Status = TIM1_NULL_PTR ;
	}
	return Error_Status ;
}

TIM1_Error_Status_t TIM1_enuRegisterCallback_ICU ( void (*TIM1cbf_t)(void))
{
	TIM1_Error_Status_t Error_Status = TIM1_OK ;

	SET_BIT(TIMSK,TIMSK_TICIE1);
	if(TIM1cbf_t != NULL)
	{
		TIM1_void_call_Back_ICU = TIM1cbf_t ;
	}
	else
	{
		Error_Status = TIM1_NULL_PTR ;
	}
	return Error_Status;
}
TIM1_Error_Status_t TIM1_enuClearINT_Flag(TIM1_INT_EN_t Cpy_INT)
{
	TIM1_Error_Status_t Error_Status = TIM1_OK ;
	if (Cpy_INT>	MAX_TIM1_INT)

	{
		Error_Status = TIM1_Not_Ok ;
	}
	else {
		SET_BIT(TIFR , Cpy_INT);
	}
	
	return Error_Status;
}

TIM1_Error_Status_t TIM1_enuEnableINT(TIM1_INT_EN_t Cpy_INT)
{
	TIM1_Error_Status_t Error_Status = TIM1_OK ;
	if (Cpy_INT>	MAX_TIM1_INT)

	{
		Error_Status = TIM1_Not_Ok ;
	}
	else {
		SET_BIT(TIMSK , Cpy_INT);
	}
	
	return Error_Status;
}


INTERRUPT_SERVICE_ROUTINE_(6)
{
	SET_BIT(TIFR,TIFR_ICF1);

	if (TIM1_void_call_Back_ICU != NULL)
	{
		TIM1_void_call_Back_ICU();
	}
	else
	{

	}
}
INTERRUPT_SERVICE_ROUTINE_(7)
{
	SET_BIT(TIFR,TIFR_OCF1A);

	if (TIM1_void_call_Back_CTCA!= NULL)
	{
		TIM1_void_call_Back_CTCA();
	}
	else
	{

	}

}
INTERRUPT_SERVICE_ROUTINE_(8)
{
	SET_BIT(TIFR,TIFR_OCF1B);


	if (TIM1_void_call_Back_CTCB!= NULL)
	{
		TIM1_void_call_Back_CTCB();
	}
	else
	{

	}
}

INTERRUPT_SERVICE_ROUTINE_(9)
{
	SET_BIT(TIFR,TIFR_TOV1);
	Timer1_Overflow_Counts++ ;
	if (TIM1_void_call_Back_OVF != NULL)
	{
		TIM1_void_call_Back_OVF();
	}
	else
	{

	}
}