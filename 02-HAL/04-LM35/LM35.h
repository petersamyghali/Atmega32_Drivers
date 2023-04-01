/*
 * LM35.h
 *
 * Created: 08-Feb-23 2:15:25 AM
 *  Author: Peter Ghali
 */ 


#ifndef LM35_H_
#define LM35_H_


void LM35_init(void);

void LM35_GET_Reading (ADC_enuChannel_t Cpy_ChannelNum , u16 * Add_pu16ADCValue);


#endif /* LM35_H_ */