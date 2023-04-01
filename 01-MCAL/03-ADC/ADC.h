/*
* ADC.h
*
* Created: 03-Feb-23 10:14:47 PM
*  Author: Peter Ghali
*/


#ifndef ADC_H_
#define ADC_H_

//An enum datatype to hold the Channel numbers
typedef enum
{
	ADC_enuChannel0 = 0 ,
	ADC_enuChannel1  ,
	ADC_enuChannel2  ,
	ADC_enuChannel3  ,
	ADC_enuChannel4  ,
	ADC_enuChannel5  ,
	ADC_enuChannel6  ,
	ADC_enuChannel7  ,
	ADC_enuNumberOfChannels ,
}ADC_enuChannel_t;
//An enum data type to hold the errors that mauy occurs in any of the follwoing functions 
typedef enum
{
	ADC_enuOK = 0,
	ADC_enuNotOK,
	ADC_enuNullPointer,
	ADC_enuInavalidPinNum,
	ADC_enuInavalidReference,
	ADC_enuInavalidMode,
	ADC_enuInavalidPreScaler ,
	ADC_enuTimeOut,
	ADC_enuWrong_Channel,
	ADC_enuBusy
}ADC_enuErrorStatus_t;
//An enum data type to hold the Trigger modes in the ADC 
typedef enum
{
	ADC_enuTrigger_FreeRunning = 0 ,
	ADC_enuTrigger_Analog_Comp,
	ADC_enuTrigger_EXTI0,
	ADC_enuTrigger_TIM0_CompMatch,
	ADC_enuTriggerTIM0_OVF,
	ADC_enuTriggerTIM0_CompMatchB,
	ADC_enuTriggerTIM1_OVF,
	ADC_enuTriggerTIM1_CAPture_Event,
	ADC_enuTrigger_Sources,
}ADC_enuAutoTrigger_t;
// A struct data type to hold the variables when declaring a chain
typedef struct
{
	u8 Lenght ;
	u8 * ChannelsID;
	u16 * Result ;
	void (*EOJ)(void) ;
}ADC_Chain_t;

/*
Function to init the ADC based on the Cfg
Input : void
Return : Error Status
*/
ADC_enuErrorStatus_t ADC_enuInit (void);

/*
Function to Disable the ADC Peripheral
Input : void
Return : Error Status
*/
ADC_enuErrorStatus_t ADC_enuDisable (void);

/*
Function to Read the ADC value on specific Channel and waits till the conversion is done
Input : The Channel number  (ADC_enuChannelX) & An address to a variable to hold the ADC value
Return : Error Status
*/
ADC_enuErrorStatus_t ADC_enuGetChannelReading_SYNC (ADC_enuChannel_t Cpy_ChannelNum , u16 * Add_pu16ADCValue );
/*
Function to Read the ADC value on specific Channel and handles the ADC AFter
Input : The Channel number  (ADC_enuChannelX) , An address to a variable to hold the ADC value 
& A function to be implemented when ADC conversion is done 
Return : Error Status
*/
ADC_enuErrorStatus_t ADC_enuGetChannelReading_ASYNC (ADC_enuChannel_t Cpy_ChannelNum , void (*Cpy_pvADCINT)(void),u16 * Add_pu16ADCValue );

/*
Function to Set the Auto Trigger option on specific Channel
Input : The Channel number  (ADC_enuChannelX) & The trigger Source (ADC_enuTriggerX)
Return : Error Status
*/
ADC_enuErrorStatus_t ADC_enuAutoTrigger (ADC_enuChannel_t Cpy_ChannelNum  , ADC_enuAutoTrigger_t Cpy_Trigger_Source , void (*Cpy_pvADCINT)(void), u16 * Add_pu16ADCValue);

/*
Function to get the the last vale the ADC have
Input : An address to a variable to hold the aDC value
Return : Error Status
*/
ADC_enuErrorStatus_t ADC_enuGetReading (u16 * Add_pu16ADCValue );
/*
Function to start and read a chain of ADC values 
Input : An address to a variable to hold the aDC value
Return : Error Status
*/
ADC_enuErrorStatus_t ADC_enuStart_Chain_Asynch (ADC_Chain_t * Add_puChain);


#endif /* ADC_H_ */