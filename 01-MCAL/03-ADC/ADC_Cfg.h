/*
 * ADC_Cfg.h
 *
 * Created: 03-Feb-23 10:14:58 PM
 *  Author: Peter Ghali
 */ 


#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/*
to define what is Reference of the ADC
options :ADC_REF_MASK	
		 ADC_REF_AREF	
		 ADC_REF_AVCC	
		 ADC_REF_INTERNAL
*/
#define ADC_REF			ADC_REF_AVCC
/*
to enable or disable the left Adjust in the ADC 
options : ENABLE
		  DISABLE
*/
#define ADC_LEF_ADJ		ENABLE

/*
to define the resolution of the ADC 
options : ADC_8BITS
		  ADC_10BITS

*/
#define ADC_RESOLUTION  ADC_8BITS
/*
to define the ADC pre_scaler 
options : ADC_PRE_SCALER_2	
		  ADC_PRE_SCALER_4	
		  ADC_PRE_SCALER_8	
		  ADC_PRE_SCALER_16
		  ADC_PRE_SCALER_32
		  ADC_PRE_SCALER_64
		  ADC_PRE_SCALER_128
*/
#define ADC_PRE_SCALER	ADC_PRE_SCALER_128
/*
to enable or disable the interrupt in the ADC 
options : ENABLE
		  DISABLE
*/
#define ADC_INTERRUPT	DISABLE

/*
to enable or disable the trigger in the ADC 
options : ENABLE
		  DISABLE
*/
#define ADC_TRIGGER		DISABLE

#endif /* ADC_CFG_H_ */