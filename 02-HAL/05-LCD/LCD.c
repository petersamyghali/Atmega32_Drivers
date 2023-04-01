/*
* LCD.c
*
* Created: 10-Feb-23 2:52:25 PM
*  Author: Peter Ghali
*/
#include "../../00-LIB/STD_TYPES.h"
#include "../../00-LIB/Bit_Math.h"

#include "LCD.h"
#include "LCD_Cfg.h"
#include "LCD_Prv.h"



#include "../../01-MCAL/00-DIO/DIO.h"

#include <util/delay.h>


/********************************** Macros *********************************************/

#define LCD_ENTRY_MODE			0x06          // shift cursor from left to right on read/write
#define LCD_FUNCTION_Set8bit	0x38          // 8-bit data, 2-line display, 5 x 7 font
#define LCD_4BIT				0x02
#define LCD_FUNCTION_Set4bit	0x28          // 4-bit data, 2-line display, 5 x 7 font
#define	ROW_0_POS				0x00
#define	ROW_1_POS				0x40
#define SET_DDRAM_ADDRESS		0x80
#define SET_CGRAM_ADDRESS		0x40
#define LCD_Argument_Check		0x00
#define LCD_Argument_Check_EQ	0x00
#define BLOCK_SIZE				8
#define COMMAND_4_BIT_MASK		0x

/****************************************** IMPLEMENTATION ******************************************************************/
LCD_enuErrorStatus_t LCD_enuInit (void)
{
	LCD_enuErrorStatus_t  LOC_Error_Status = LCDenuOK ;
	_delay_ms(20);
	#if LCD_BIT_MODE == LCD_8BIT_MODE
	LCD_enuSendCommand(LCD_FUNCTION_Set8bit);
	#elif LCD_BIT_MODE == LCD_4BIT_MODE
	LCD_enuSendCommand(LCD_4BIT);
	LCD_enuSendCommand(LCD_FUNCTION_Set4bit);
	#endif
	_delay_ms(2);
	LCD_enuSendCommand(LCD_DISPLAY_ON);
	_delay_ms(2);
	LCD_enuSendCommand(LCD_CLEAR);
	_delay_ms(2);
	LCD_enuSendCommand(LCD_ENTRY_MODE);
	_delay_ms(2);
	LCD_enuSendCommand(LCD_HOME);
	_delay_ms(2);
	return LOC_Error_Status ;
}

LCD_enuErrorStatus_t LCD_enuSendCommand (u16 Copy_u8Command)
{
	u8 LOC_Counter = 0 ,BIT = 0 ;
	LCD_enuErrorStatus_t  LOC_Error_Status = LCDenuOK ;
	DIO_enuClearPin(LCD_RS_PIN);/*As I am sending a command*/
	DIO_enuClearPin(LCD_RW_PIN);/*As I am writing to the LCd*/
	#if LCD_BIT_MODE == LCD_8BIT_MODE
	for ( LOC_Counter = 0 ; LOC_Counter< LCD_BIT_MODE ; LOC_Counter++)
	{
		BIT= GET_BIT(Copy_u8Command,LOC_Counter);
		if (BIT == 1 )
		{
			DIO_enuSetPin(LCD_Data_PINS[LOC_Counter]);
		}
		else
		{
			DIO_enuClearPin(LCD_Data_PINS[LOC_Counter]);
		}
	}
	DIO_enuSetPin(LCD_E_PIN);
	_delay_ms(2);
	DIO_enuClearPin(LCD_E_PIN);
	#elif LCD_BIT_MODE == LCD_4BIT_MODE
	//sending the four MSB in the Command first
	for (LOC_Counter = 4 ; LOC_Counter < 8 ; LOC_Counter++)
	{
		BIT= GET_BIT(Copy_u8Command,LOC_Counter);
		if (BIT == 1 )
		{
			DIO_enuSetPin(LCD_Data_PINS[LOC_Counter-4]);
		}
		else
		{
			DIO_enuClearPin(LCD_Data_PINS[LOC_Counter-4]);
		}
	}
	DIO_enuSetPin(LCD_E_PIN);
	_delay_ms(2);
	DIO_enuClearPin(LCD_E_PIN);
	for (LOC_Counter = 0 ; LOC_Counter < 4 ; LOC_Counter++)
	{
		BIT= GET_BIT(Copy_u8Command,LOC_Counter);
		if (BIT == 1 )
		{
			DIO_enuSetPin(LCD_Data_PINS[LOC_Counter]);
		}
		else
		{
			DIO_enuClearPin(LCD_Data_PINS[LOC_Counter]);
		}
	}
	DIO_enuSetPin(LCD_E_PIN);
	_delay_ms(2);
	DIO_enuClearPin(LCD_E_PIN);
	#endif
	

	return LOC_Error_Status ;
}

LCD_enuErrorStatus_t LCD_enuSendData (u8 Copy_u8Data)
{
	
	u8 LOC_Counter = 0 ,BIT = 0 ;
	LCD_enuErrorStatus_t  LOC_Error_Status = LCDenuOK ;
	DIO_enuSetPin(LCD_RS_PIN);
	DIO_enuClearPin(LCD_RW_PIN);
	#if LCD_BIT_MODE == LCD_8BIT_MODE
	for ( LOC_Counter= 0; LOC_Counter< LCD_BIT_MODE ; LOC_Counter++)
	{
		BIT = GET_BIT(Copy_u8Data,LOC_Counter);
		if (BIT == 1 )
		{
			DIO_enuSetPin(LCD_Data_PINS[LOC_Counter]);
		}
		else
		{
			DIO_enuClearPin(LCD_Data_PINS[LOC_Counter]);
		}
	}
	DIO_enuSetPin(LCD_E_PIN);
	_delay_ms(2);
	DIO_enuClearPin(LCD_E_PIN);
	#elif LCD_BIT_MODE == LCD_4BIT_MODE
	for (LOC_Counter = 4 ; LOC_Counter < 8 ; LOC_Counter++)
	{
		BIT= GET_BIT(Copy_u8Data,LOC_Counter);
		if (BIT == 1 )
		{
			DIO_enuSetPin(LCD_Data_PINS[LOC_Counter-4]);
		}
		else
		{
			DIO_enuClearPin(LCD_Data_PINS[LOC_Counter-4]);
		}
	}
	DIO_enuSetPin(LCD_E_PIN);
	_delay_ms(2);
	DIO_enuClearPin(LCD_E_PIN);
	for (LOC_Counter = 0 ; LOC_Counter < 4 ; LOC_Counter++)
	{
		BIT= GET_BIT(Copy_u8Data,LOC_Counter);
		if (BIT == 1 )
		{
			DIO_enuSetPin(LCD_Data_PINS[LOC_Counter]);
		}
		else
		{
			DIO_enuClearPin(LCD_Data_PINS[LOC_Counter]);
		}
	}
	for (LOC_Counter = 4 ; LOC_Counter < LCD_8BIT_MODE ; LOC_Counter++)
	{
		BIT= GET_BIT(Copy_u8Data,LOC_Counter);
		if (BIT == 1 )
		{
			DIO_enuSetPin(LCD_Data_PINS[LOC_Counter]);
		}
		else
		{
			DIO_enuClearPin(LCD_Data_PINS[LOC_Counter]);
		}
	}
	DIO_enuSetPin(LCD_E_PIN);
	_delay_ms(2);
	DIO_enuClearPin(LCD_E_PIN);
	#endif
	return LOC_Error_Status ;
}

LCD_enuErrorStatus_t LCD_enuSendString (const u8* Add_pchString)
{
	LCD_enuErrorStatus_t  LOC_Error_Status = LCDenuOK ;
	u8 LOC_Counter = 0 ,LOC_u8NEXT_Row_Flag = 0;
	if (Add_pchString == NULL)
	{
		LOC_Error_Status = LCD_enuNULLPtr ;
	}
	else
	{
		while (Add_pchString[LOC_Counter] != '\0')
		{
			LCD_enuSendData(Add_pchString[LOC_Counter]);
			LOC_Counter++;
			if (LOC_u8NEXT_Row_Flag == 0)
			{
				if (LOC_Counter >= NUMBER_OF_COLMUNS)
				{
					LCD_enuGotoXY(1,0);
					LOC_u8NEXT_Row_Flag = 1 ;
				}
			}
			
		}
	}
	
	return LOC_Error_Status ;
}

LCD_enuErrorStatus_t LCD_enuGotoXY (u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	u8 LOC_u8Address = 0 ;
	LCD_enuErrorStatus_t  LOC_Error_Status = LCDenuOK ;
	if (Copy_u8XPos >= NUMBER_OF_ROWS || Copy_u8YPos >= NUMBER_OF_COLMUNS)
	{
		LOC_Error_Status = LCD_enuWrong_Parameters ;
	}
	if (Copy_u8XPos == 0 )
	{
		LOC_u8Address = Copy_u8YPos + ROW_0_POS;
	}
	else if  (Copy_u8XPos == 1 )
	{
		LOC_u8Address = Copy_u8YPos + ROW_1_POS;
	}
	//Oring the address of the CGRAM with the need position
	LCD_enuSendCommand(LOC_u8Address | SET_DDRAM_ADDRESS);
	return LOC_Error_Status ;
}

LCD_enuErrorStatus_t LCD_enuWriteSpecialPattern  (const u8* Add_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	LCD_enuErrorStatus_t  LOC_Error_Status = LCDenuOK ;
	u8 Loc_u8CGRAMAdd =0 ,Loc_u8Counter = 0 ;
	/*Calculate the CGRAM address whose each block is 8 bytes */
	Loc_u8CGRAMAdd = Copy_u8BlockNum *BLOCK_SIZE ;
	/*Send the CG RAM address to the LCD */
	LCD_enuSendCommand(Loc_u8CGRAMAdd | SET_CGRAM_ADDRESS);
	/*write the pattern into the CG RAM*/
	for (Loc_u8Counter = 0 ; Loc_u8Counter < BLOCK_SIZE ; Loc_u8Counter++)

	{
		LCD_enuSendData(Add_pu8Pattern[Loc_u8Counter]);
	}
	LCD_enuSendCommand(SET_DDRAM_ADDRESS);
	LCD_enuGotoXY(Copy_u8XPos,Copy_u8YPos);
	/*Go back to the DD RAM to display the pattern*/
	LCD_enuSendData(Copy_u8BlockNum);
	/*Display the pattern */
	return LOC_Error_Status ;
}
LCD_enuErrorStatus_t LCD_enuWriteNumber (u32 Copy_u16Number)
{
	LCD_enuErrorStatus_t  LOC_Error_Status = LCDenuOK ;
	u8 Loc_u8Counter = 0 ,Loc_u8Counter2 = 0 ;
	u8 LOC_u8ARR[NUMBER_OF_COLMUNS] = {0};
	while (Copy_u16Number)
	{
		LOC_u8ARR[Loc_u8Counter] = Copy_u16Number%10;
		//	LOC_u8ARR[Loc_u8Counter]
		Copy_u16Number/=10;
		Loc_u8Counter++;
	}
	for (Loc_u8Counter2 = Loc_u8Counter-1 ; Loc_u8Counter2 > 0 ; Loc_u8Counter2--)
	{
		LCD_enuSendData(LOC_u8ARR[Loc_u8Counter2]+'0');
	}
	LCD_enuSendData(LOC_u8ARR[0]+'0');
	return LOC_Error_Status ;
}