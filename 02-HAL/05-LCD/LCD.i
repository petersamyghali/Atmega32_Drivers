# 0 "LCD.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "LCD.c"






# 1 "../../00-LIB/STD_TYPES.h" 1
# 14 "../../00-LIB/STD_TYPES.h"
typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned int u32;
typedef unsigned long int u64;

typedef signed char s8;
typedef signed short int s16;
typedef signed int s32;
typedef signed long int s64;

typedef float f32;
typedef double f64;
# 8 "LCD.c" 2
# 1 "../../00-LIB/Bit_Math.h" 1
# 9 "LCD.c" 2

# 1 "LCD.h" 1
# 13 "LCD.h"
typedef enum
{
 LCDenuOK = 0,
 LCD_enuNOTK,
 LCD_enuNULLPtr

}LCD_enuErrorStatus_t;





LCD_enuErrorStatus_t LCD_enuInit (void);







LCD_enuErrorStatus_t LCD_enuSendData (u8 Copy_u8Data);






LCD_enuErrorStatus_t LCD_enuSendCommand (u8 Copy_u8Command);






LCD_enuErrorStatus_t LCD_enuGotoXY (u8 Copy_u8XPos, u8 Copy_u8YPos);






LCD_enuErrorStatus_t LCD_enuWriteSpecialPattern (u8* Add_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos, u8 Copy_u8YPos);






LCD_enuErrorStatus_t LCD_enuWriteString (char* Add_pchString);






LCD_enuErrorStatus_t LCD_enuWriteNumber (u16 Copy_u16Number);
# 11 "LCD.c" 2
# 1 "LCD_Cfg.h" 1
# 11 "LCD_Cfg.h"
# 1 "LCD_Prv.h" 1
# 12 "LCD_Cfg.h" 2
# 36 "LCD_Cfg.h"
extern u8 LCD_Data_PINS [8] ;
# 12 "LCD.c" 2




# 1 "../../01-MCAL/00-DIO/DIO.h" 1




# 1 "../../01-MCAL/00-DIO/../../00-LIB/STD_TYPES.h" 1
# 6 "../../01-MCAL/00-DIO/DIO.h" 2




typedef enum {

 DIO_enuPORTA_Pin0 = 0 ,
 DIO_enuPORTA_Pin1 ,
 DIO_enuPORTA_Pin2 ,
 DIO_enuPORTA_Pin3 ,
 DIO_enuPORTA_Pin4 ,
 DIO_enuPORTA_Pin5 ,
 DIO_enuPORTA_Pin6 ,
 DIO_enuPORTA_Pin7 ,

 DIO_enuPORTB_Pin0 ,
 DIO_enuPORTB_Pin1 ,
 DIO_enuPORTB_Pin2,
 DIO_enuPORTB_Pin3,
 DIO_enuPORTB_Pin4,
 DIO_enuPORTB_Pin5,
 DIO_enuPORTB_Pin6,
 DIO_enuPORTB_Pin7,

 DIO_enuPORTC_Pin0,
 DIO_enuPORTC_Pin1,
 DIO_enuPORTC_Pin2,
 DIO_enuPORTC_Pin3,
 DIO_enuPORTC_Pin4,
 DIO_enuPORTC_Pin5,
 DIO_enuPORTC_Pin6,
 DIO_enuPORTC_Pin7,

 DIO_enuPORTD_Pin0,
 DIO_enuPORTD_Pin1,
 DIO_enuPORTD_Pin2,
 DIO_enuPORTD_Pin3,
 DIO_enuPORTD_Pin4,
 DIO_enuPORTD_Pin5,
 DIO_enuPORTD_Pin6,
 DIO_enuPORTD_Pin7,

 DIO_enuNumberofPins,
}DIO_tenuPins;




typedef enum{
 DIO_enLow = 0 ,
 DIO_enuHigh
}DIO_tenuPinValue;




typedef enum
{
 DIO_enuOK = 0,
 DIO_enuNotOK,
 DIO_enuNullPointer,
 DIO_enuInavalidPortNum,
 DIO_enuInavalidPinNum,
 DIO_enuInavalidParametrs,
 DIO_enuInavalidMode,
}DIO_tenuErrorStatus;

typedef enum
{
 DIO_PORTA = 0,
 DIO_PORTB ,
 DIO_PORTC ,
 DIO_PORTD ,
}DIO_enuPorCfg_t;







DIO_tenuErrorStatus DIO_enuInit(void);







DIO_tenuErrorStatus DIO_enuSetPin( u8 Cpy_u8PinNumber);






DIO_tenuErrorStatus DIO_enuClearPin( u8 Cpy_u8PinNumber );






DIO_tenuErrorStatus DIO_enuGetPin(u8 Cpy_u8PinNumber, u8* Add_pu8PinValue);
# 17 "LCD.c" 2
# 33 "LCD.c"
LCD_enuErrorStatus_t LCD_enuInit (void )
{
 LCD_enuErrorStatus_t LOC_Error_Status = LCDenuOK ;


 LCD_enuSendCommand(0x38 );



 LCD_enuSendCommand(0x0C);
 LCD_enuSendCommand(0x01);
 LCD_enuSendCommand(0x06);


 return LOC_Error_Status ;
}

LCD_enuErrorStatus_t LCD_enuSendCommand (u8 Copy_u8Command)
{
 u8 LOC_Counter = 0 ,BIT = 0 ;
 LCD_enuErrorStatus_t LOC_Error_Status = LCDenuOK ;
 DIO_enuClearPin(DIO_enuPORTC_Pin0);
 DIO_enuClearPin(DIO_enuPORTC_Pin1);
 for ( LOC_Counter = 0 ; LOC_Counter< 8 ; LOC_Counter++)
 {
  (((Copy_u8Command) >> (LOC_Counter)) & 0x01);
  if (BIT)
  {
   DIO_enuSetPin(LCD_Data_PINS[LOC_Counter]);
  }
  else
  {
   DIO_enuClearPin(LCD_Data_PINS[LOC_Counter]);
  }
 }
 DIO_enuSetPin(DIO_enuPORTC_Pin2);
 _delay_ms(2);
 DIO_enuClearPin(DIO_enuPORTC_Pin2);
 _delay_ms(2);
 return LOC_Error_Status ;
}

LCD_enuErrorStatus_t LCD_enuSendData (u8 Copy_u8Data)
{
 u8 LOC_Counter = 0 ,BIT = 0 ;
 LCD_enuErrorStatus_t LOC_Error_Status = LCDenuOK ;
 DIO_enuSetPin(DIO_enuPORTC_Pin0);
 DIO_enuClearPin(DIO_enuPORTC_Pin1);
 for ( LOC_Counter= 0; LOC_Counter< 8 ; LOC_Counter++)
 {
  (((Copy_u8Data) >> (LOC_Counter)) & 0x01);
  if (BIT)
  {
   DIO_enuSetPin(LCD_Data_PINS[LOC_Counter]);
  }
  else
  {
   DIO_enuClearPin(LCD_Data_PINS[LOC_Counter]);
  }
 }
 DIO_enuSetPin(DIO_enuPORTC_Pin2);
 _delay_ms(2);
 DIO_enuClearPin(DIO_enuPORTC_Pin2);
 _delay_ms(2);
 return LOC_Error_Status ;
}
