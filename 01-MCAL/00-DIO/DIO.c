//including the
#include "../../00-LIB/STD_TYPES.h"
#include "../../00-LIB/BIT_MATH.h"

#include "DIO.h"
#include "DIO_Prv.h"
#include "DIO_Cfg.h"


#define MAX_PIN_NUM		7	//pin 0 included
#define PINS_COUNT		8	//max number of pins in each port
#define ZERO			0
#define MAX_PORTS_NUM	3	//PORT 0 INCLUDED

DIO_tenuErrorStatus DIO_enuInit(void)
{
	u8 LocalCounter ;
	//a variable to hold the Port number
	u8 Local_u8PortNumber = ZERO ;
	//a variable to hold the PIN number
	u8 Local_u8PinNumber  = ZERO ;
	//a variable to hold the Error Status
	DIO_tenuErrorStatus Error_Status =  DIO_enuOK;
	

	
	for (LocalCounter = ZERO ; LocalCounter < DIO_enuNumberofPins ; LocalCounter++)
	{
		//AN EQUATION TO GET THE PORT (A / B / C / D )
		Local_u8PortNumber = LocalCounter / PINS_COUNT ;
		//AN EQUATION TO GET THE PIN NUMBER ( 0 ... 7 )
		Local_u8PinNumber  = LocalCounter % PINS_COUNT ;
		/*validating arguments */
		// if port number > MAX_PORTS_NUM
		if(Local_u8PortNumber > MAX_PORTS_NUM)
		{
			Error_Status = DIO_enuInavalidPortNum;
		}
		/*Verifying if Pin number is Out of Range */
		else if(Local_u8PinNumber >  MAX_PIN_NUM )
		{
			Error_Status = DIO_enuInavalidPinNum;
		}
		//if the Direction is not right
		else if(DIO_strPinCfg[LocalCounter].DIO_PinDirection != DIO_DIR_OUTPUT && DIO_strPinCfg[LocalCounter].DIO_PinDirection != DIO_DIR_INPUT)
		{
			Error_Status = DIO_enuInavalidMode;
		}
		// if the mode is not right
		else if(DIO_strPinCfg[LocalCounter].DIO_InputStatus != DIO_INPUT_PULL_UP && DIO_strPinCfg[LocalCounter].DIO_InputStatus != DIO_INPUT_TRI_STATE
		&& DIO_strPinCfg[LocalCounter].DIO_InputStatus != DIO_OUTPUT_HIGH && DIO_strPinCfg[LocalCounter].DIO_InputStatus != DIO_OUTPUT_LOW)
		{
			Error_Status = DIO_enuInavalidMode;
		}
		//else proceed the init function
		else {
			switch (Local_u8PortNumber) {
				//PORTA case
				case (DIO_PORTA):
				//if it was an output
				if (DIO_strPinCfg[LocalCounter].DIO_PinDirection == DIO_DIR_OUTPUT)
				{
					SET_BIT(DDRA_Register , Local_u8PinNumber);
					// if it was an output high
					if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_OUTPUT_HIGH)
					{
						
						SET_BIT(PORTA_Register , Local_u8PinNumber);
					}
					//if it was an output low
					else if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_OUTPUT_LOW)
					{
						
						CLR_BIT(PORTA_Register , Local_u8PinNumber);
					}
				}
				else
				{
					CLR_BIT(DDRA_Register , Local_u8PinNumber);
					if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_INPUT_PULL_UP)
					{
						SET_BIT(PORTA_Register , Local_u8PinNumber);
					}
					else if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_INPUT_TRI_STATE)
					{
						CLR_BIT(PORTA_Register , Local_u8PinNumber);
					}
					
				}
				break ;
				
				case (DIO_PORTB):
				//if it was an output
				if (DIO_strPinCfg[LocalCounter].DIO_PinDirection == DIO_DIR_OUTPUT)
				{
					SET_BIT(DDRB_Register , Local_u8PinNumber);
					// if it was an output high
					if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_OUTPUT_HIGH)
					{
						
						SET_BIT(PORTB_Register , Local_u8PinNumber);
					}
					//if it was an output low
					else if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_OUTPUT_LOW)
					{
						
						CLR_BIT(PORTB_Register , Local_u8PinNumber);
					}
				}
				else
				{
					CLR_BIT(DDRB_Register , Local_u8PinNumber);
					if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_INPUT_PULL_UP)
					{
						SET_BIT(PORTB_Register , Local_u8PinNumber);
					}
					else if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_INPUT_TRI_STATE)
					{
						CLR_BIT(PORTB_Register , Local_u8PinNumber);
					}
					
				}
				break ;
				
				case (DIO_PORTC):
				//if it was an output
				if (DIO_strPinCfg[LocalCounter].DIO_PinDirection == DIO_DIR_OUTPUT)
				{
					SET_BIT(DDRC_Register , Local_u8PinNumber);
					// if it was an output high
					if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_OUTPUT_HIGH)
					{
						
						SET_BIT(PORTC_Register , Local_u8PinNumber);
					}
					//if it was an output low
					else if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_OUTPUT_LOW)
					{
						
						CLR_BIT(PORTC_Register , Local_u8PinNumber);
					}
				}
				else
				{
					CLR_BIT(DDRC_Register , Local_u8PinNumber);
					if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_INPUT_PULL_UP)
					{
						SET_BIT(PORTC_Register , Local_u8PinNumber);
					}
					else if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_INPUT_TRI_STATE)
					{
						CLR_BIT(PORTC_Register , Local_u8PinNumber);
					}
					
				}
				break ;
				
				
				case (DIO_PORTD) :
				//if it was an output
				if (DIO_strPinCfg[LocalCounter].DIO_PinDirection == DIO_DIR_OUTPUT)
				{
					SET_BIT(DDRD_Register , Local_u8PinNumber);
					// if it was an output high
					if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_OUTPUT_HIGH)
					{
						
						SET_BIT(PORTD_Register , Local_u8PinNumber);
					}
					//if it was an output low
					else if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_OUTPUT_LOW)
					{
						
						CLR_BIT(PORTD_Register , Local_u8PinNumber);
					}
				}
				else
				{
					CLR_BIT(DDRD_Register , Local_u8PinNumber);
					if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_INPUT_PULL_UP)
					{
						SET_BIT(PORTD_Register , Local_u8PinNumber);
					}
					else if (DIO_strPinCfg[LocalCounter].DIO_InputStatus == DIO_INPUT_TRI_STATE)
					{
						CLR_BIT(PORTD_Register , Local_u8PinNumber);
					}
					
				}
				break ;
			}
			
		}
	}
	return Error_Status;
}

DIO_tenuErrorStatus DIO_enuSetPin(u8 Cpy_u8PinNumber )
{
	//AN equation to get the port number [A / B / C / D ]
	u8 Local_u8PortNumber = Cpy_u8PinNumber / PINS_COUNT ;
	//AN equation to get the pin number [ 0 ... 7 ]
	u8 Local_u8PinNumber = Cpy_u8PinNumber %  PINS_COUNT ;
	//a variable to hold the Error status
	DIO_tenuErrorStatus Error_Status  = DIO_enuOK ;
	
	if (Cpy_u8PinNumber > DIO_enuNumberofPins)
	{
		Error_Status = DIO_enuInavalidPinNum ;
	}
	else
	{
		switch(Local_u8PortNumber)
		{
			case (DIO_PORTA):
			//SET_BIT(DDRA_Register , Local_u8PinNumber);
			SET_BIT(PORTA_Register , Local_u8PinNumber);
			break;
			
			
			case (DIO_PORTB):
			//SET_BIT(DDRB_Register , Local_u8PinNumber);
			SET_BIT(PORTB_Register , Local_u8PinNumber);
			break;
			
			case (DIO_PORTC):
			//SET_BIT(DDRC_Register , Local_u8PinNumber);
			SET_BIT(PORTC_Register , Local_u8PinNumber);
			break;
			
			case (DIO_PORTD):
			//SET_BIT(DDRD_Register , Local_u8PinNumber);
			SET_BIT(PORTD_Register , Local_u8PinNumber);
			break;
			
			default:
			Error_Status = DIO_enuNotOK;
		}
	}
	return Error_Status ;
}
//A function the Clear the Pin
DIO_tenuErrorStatus DIO_enuClearPin( u8 Cpy_u8PinNumber ){
	//An equation to get the required port 
	u8 Local_u8PortNumber = Cpy_u8PinNumber / PINS_COUNT ;
	//An equation to get the required pin
	u8 Local_u8PinNumber = Cpy_u8PinNumber  % PINS_COUNT ;
	DIO_tenuErrorStatus Error_Status  = DIO_enuOK ;
	//check if the user have sent an invalid Pin Number 
	if (Cpy_u8PinNumber > DIO_enuNumberofPins)
	{
		Error_Status = DIO_enuInavalidPinNum ;
	}
	//if the Pin number is correct 
	else
	{
		//switch for what is the port 
		switch(Local_u8PortNumber)
		{
			case (DIO_PORTA):
			
			
			CLR_BIT(PORTA_Register , Local_u8PinNumber);
			break;
			
			
			case (DIO_PORTB):
			
			
			CLR_BIT(PORTB_Register , Local_u8PinNumber);
			break;
			
			
			case (DIO_PORTC):
			
			
			CLR_BIT(PORTC_Register , Local_u8PinNumber);
			break;
			
			
			case (DIO_PORTD):
			
			
			CLR_BIT(PORTD_Register , Local_u8PinNumber);
			break;
			
			default:
			Error_Status = DIO_enuNotOK;
		}
	}
	return Error_Status;
}
//A function to check the PIN register values and puts that value in the giver address 
DIO_tenuErrorStatus DIO_enuGetPin (u8 Cpy_u8PinNumber, u8* Add_pu8PinValue)
{
	//A couple of equation in order to know the PIN and PORT values 
	u8 Local_u8PortNumber = Cpy_u8PinNumber / PINS_COUNT ;
	u8 Local_u8PinNumber = Cpy_u8PinNumber %  PINS_COUNT ;
	DIO_tenuErrorStatus Error_Status  = DIO_enuOK ;
	//check if the pointer is pointing to null 
	if (Add_pu8PinValue == NULL)
	{
		Error_Status = DIO_enuNullPointer ;
	}
	
//check if the user have sent an invalid Pin Number 
	else if (Cpy_u8PinNumber > DIO_enuNumberofPins)
	{
		Error_Status = DIO_enuInavalidPinNum ;
	}
	//if the givern parameter is valid 
	else
	{
		switch (Local_u8PortNumber)
		{
			case (DIO_PORTA) :
			*Add_pu8PinValue = GET_BIT ( PINA_Register , Local_u8PinNumber );
			break ;
			
			case (DIO_PORTB) :
			*Add_pu8PinValue = GET_BIT ( PINB_Register  , Local_u8PinNumber );
			break ;
			
			case (DIO_PORTC) :
			*Add_pu8PinValue = GET_BIT ( PINC_Register  , Local_u8PinNumber );
			break ;
			
			case (DIO_PORTD) :
			*Add_pu8PinValue = GET_BIT ( PIND_Register  , Local_u8PinNumber );
			break ;
			
			default:
			Error_Status = DIO_enuNotOK;
		}
	}
	return Error_Status;
	
}