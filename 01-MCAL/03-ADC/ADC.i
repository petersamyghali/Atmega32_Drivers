# 0 "ADC.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "ADC.c"






# 1 "../../00-LIB/Bit_Math.h" 1
# 8 "ADC.c" 2
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
# 9 "ADC.c" 2
# 1 "ADC.h" 1
# 13 "ADC.h"
typedef enum
{
 ADC_enuChannel0 = 0 ,
 ADC_enuChannel1 ,
 ADC_enuChannel2 ,
 ADC_enuChannel3 ,
 ADC_enuChannel4 ,
 ADC_enuChannel5 ,
 ADC_enuChannel6 ,
 ADC_enuChannel7 ,
 ADC_enuNumberOfChannels ,
}ADC_enuChannel_t;

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

typedef struct
{
 u8 Lenght ;
 u8 * ChannelsID;
 u8 * Result ;
 void (*EOJ)(void) ;
}ADC_Chain_t;






ADC_enuErrorStatus_t ADC_enuInit (void);






ADC_enuErrorStatus_t ADC_enuDisable (void);






ADC_enuErrorStatus_t ADC_enuGetChannelReading_SYNC (ADC_enuChannel_t Cpy_ChannelNum , u16 * Add_pu16ADCValue );






ADC_enuErrorStatus_t ADC_enuGetChannelReading_ASYNC (ADC_enuChannel_t Cpy_ChannelNum , void (*Cpy_pvADCINT)(void),u16 * Add_pu16ADCValue );






ADC_enuErrorStatus_t ADC_enuAutoTrigger (ADC_enuChannel_t Cpy_ChannelNum , ADC_enuAutoTrigger_t Cpy_Trigger_Source , void (*Cpy_pvADCINT)(void), u16 * Add_pu16ADCValue);






ADC_enuErrorStatus_t ADC_enuGetReading (u16 * Add_pu16ADCValue );





ADC_enuErrorStatus_t ADC_enuStart_Chain_Asynch (ADC_Chain_t * Add_puChain);
# 10 "ADC.c" 2
# 1 "ADC_Cfg.h" 1
# 11 "ADC.c" 2
# 1 "ADC_prv.h" 1
# 12 "ADC.c" 2




static void ADC_Start_Conv (ADC_enuChannel_t Cpy_ChannelNum);
static void (*ADC_INT_PTR)(void) =(void*)0;
static volatile u16 *ADC_pu16VALUE = (void*)0 ;
static u8 ADC_u8State = 0 ;
static u8 Glo_Cahin_Flag = 0 ;
static u8 Glo_SingleAsyn_Flag = 0 ;
static void (*ADC_Chain_EOJ)(void) = (void*)0 ;
static u8 Glo_Chain_Channel_Num[ADC_enuNumberOfChannels] = {0} ;
static u8 Glo_Chain_Result_Array[ADC_enuNumberOfChannels] = {0} ;
static u8 Glo_Chain_Lenght = 0;
static u8 Glo_Chain_Index = 0 ;





static ADC_enuErrorStatus_t LOC_Error_Status = ADC_enuNotOK ;
static u8 LOC_Buffer = 0 ;
static u16 LOC_TimeOut = 0 ;
ADC_enuErrorStatus_t ADC_enuInit (void)
{
 LOC_Error_Status = ADC_enuOK ;
 LOC_Buffer = *(( volatile u8 * )0x27) ;
 LOC_Buffer &= 0b00111111 ;





 LOC_Buffer |= 0b01000000 ;



 *(( volatile u8 * )0x27) = LOC_Buffer ;
 LOC_Buffer = 0 ;


 *(( volatile u8 * )0x27)|=(1<<5);
# 62 "ADC.c"
 LOC_Buffer = *(( volatile u8 * )0x26) ;
 LOC_Buffer &= 0b11111000 ;
# 77 "ADC.c"
 LOC_Buffer |=7;



 *(( volatile u8 * )0x26) = LOC_Buffer ;





 *(( volatile u8 * )0x26) &=~(1 << 3 );
# 96 "ADC.c"
 *(( volatile u8 * )0x26) &=~(1 << 5 );




 *(( volatile u8 * )0x26) |= (1 << 7);
 return LOC_Error_Status;
}


ADC_enuErrorStatus_t ADC_enuDisable (void)
{
 LOC_Error_Status = ADC_enuOK ;
 *(( volatile u8 * )0x26) &= ~(1 << 7);
 return LOC_Error_Status;
}


ADC_enuErrorStatus_t ADC_enuGetChannelReading_SYNC (ADC_enuChannel_t Cpy_ChannelNum , u16 * Add_pu16ADCValue )
{
 LOC_Error_Status = ADC_enuOK ;
 if (ADC_u8State == 0)
 {
  LOC_TimeOut = 0 ;
  if (Add_pu16ADCValue == (void*)0 )
  {
   LOC_Error_Status = ADC_enuNullPointer ;
  }
  else
  {
   ADC_u8State = 1 ;
   LOC_Buffer = *(( volatile u8 * )0x27) ;
   LOC_Buffer &= 0b1110000 ;
   LOC_Buffer |= Cpy_ChannelNum ;
   *(( volatile u8 * )0x27) = LOC_Buffer ;
   *(( volatile u8 * )0x26)|=(1 << 6);
   while ( (((*(( volatile u8 * )0x26)) >> (4)) & 0x01) == 0 && LOC_TimeOut < 10000)
   {
    LOC_TimeOut++;
   }
   if ((((*(( volatile u8 * )0x26)) >> (4)) & 0x01) == 1)
   {

    (*(( volatile u8 * )0x26)) |= (1<<(4));


    *Add_pu16ADCValue = 10 ;
# 155 "ADC.c"
    ADC_u8State = 0 ;
    *Add_pu16ADCValue=17;
   }
   else
   {
    *Add_pu16ADCValue=15 ;
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
 if (ADC_u8State == 0)
 {
  LOC_TimeOut = 0 ;
  if (Add_pu16ADCValue == (void*)0 || Cpy_pvADCINT == (void*)0)
  {
   LOC_Error_Status = ADC_enuNullPointer ;
  }
  else
  {
   ADC_u8State = 1 ;
   LOC_Buffer = *(( volatile u8 * )0x27) ;
   LOC_Buffer &= 0b1110000 ;
   LOC_Buffer |= Cpy_ChannelNum ;
   *(( volatile u8 * )0x27) = LOC_Buffer ;
   ADC_INT_PTR = Cpy_pvADCINT;
   ADC_pu16VALUE = Add_pu16ADCValue ;
   (*(( volatile u8 * )0x26)) |= (1<<(3));

   *(( volatile u8 * )0x26)|=(1 << 6);

  }
 }
 else
 {
  LOC_Error_Status = ADC_enuBusy ;
 }

 return LOC_Error_Status;

}

ADC_enuErrorStatus_t ADC_enuAutoTrigger (ADC_enuChannel_t Cpy_ChannelNum , ADC_enuAutoTrigger_t Cpy_Trigger_Source , void (*Cpy_pvADCINT)(void), u16 * Add_pu16ADCValue)
{
 u8 LOC_REG = 0 ;
 LOC_Error_Status = ADC_enuOK ;
 if ((((*(( volatile u8 * )0x26)) >> (5)) & 0x01) == 0)
 {
  LOC_Error_Status = ADC_enuInavalidMode ;
 }
 if (Add_pu16ADCValue == (void*)0 || Cpy_pvADCINT == (void*)0)
 {
  LOC_Error_Status = ADC_enuNullPointer ;
 }
 else
 {
  if (Cpy_Trigger_Source > ADC_enuTrigger_Sources)
  {
   LOC_Error_Status = ADC_enuInavalidMode ;
  }
  else
  {
   LOC_REG = *(( volatile u8 * )0x50) ;
   LOC_REG &=~(0b11100000);
   LOC_REG = (Cpy_Trigger_Source << 5);
   *(( volatile u8 * )0x50) = LOC_REG ;
   ADC_INT_PTR = Cpy_pvADCINT;
   ADC_pu16VALUE = Add_pu16ADCValue ;
  }
 }

 return LOC_Error_Status ;
}



ADC_enuErrorStatus_t ADC_enuGetReading (u16 * Add_pu16ADCValue )
{
 LOC_Error_Status = ADC_enuOK ;
 LOC_TimeOut = 0 ;
 if (Add_pu16ADCValue == (void*)0 )
 {
  LOC_Error_Status = ADC_enuNullPointer ;
 }
 else
 {
  (*(( volatile u8 * )0x26)) |= (1<<(4));


  *Add_pu16ADCValue = *(( volatile u8 * )0x25) ;
# 273 "ADC.c"
 }

 return LOC_Error_Status;
}
ADC_enuErrorStatus_t ADC_enuStart_Chain_Asynch (ADC_Chain_t * Add_puChain)
{
 LOC_Error_Status = ADC_enuOK ;
 u8 Loc_Counter = 0 ;
 (*(( volatile u8 * )0x26)) |= (1<<(3));
 *(( volatile u8 * )0x26)|=(1 << 6);
 ADC_Chain_EOJ = Add_puChain->EOJ;
 DIO_enuSetPin(DIO_enuPORTA_Pin7);

 for (Loc_Counter = 0 ; Loc_Counter < Add_puChain->Lenght ; Loc_Counter++)
 {
  Glo_Chain_Channel_Num[Loc_Counter] = Add_puChain -> ChannelsID[Loc_Counter];
 }
 Glo_Chain_Lenght = Add_puChain->Lenght;
 Glo_Cahin_Flag = 1 ;

 return LOC_Error_Status;


}

void ADC_Start_Conv (ADC_enuChannel_t Cpy_ChannelNum)
{
 ADC_u8State = 1 ;
 LOC_Buffer = *(( volatile u8 * )0x27) ;
 LOC_Buffer &= 0b1110000 ;
 LOC_Buffer |= Cpy_ChannelNum ;
 *(( volatile u8 * )0x27) = LOC_Buffer ;
 *(( volatile u8 * )0x26)|=(1 << 6);
}



void __vector_16 (void) __attribute__ ((signal));void __vector_16 (void)
{
   DIO_enuSetPin(DIO_enuPORTA_Pin6);
 if (Glo_SingleAsyn_Flag)
 {
  if (ADC_INT_PTR != (void*)0 && ADC_pu16VALUE != (void*)0)
  {
   ADC_INT_PTR();
# 327 "ADC.c"
   ADC_u8State = 0 ;
  }
  else
  {

  }

 }
 else if (Glo_Cahin_Flag)
 {

  if (Glo_Chain_Index < Glo_Chain_Lenght)
  {
# 349 "ADC.c"
   ADC_u8State = 0 ;
   Glo_Chain_Index++;
   ADC_Start_Conv(Glo_Chain_Channel_Num[Glo_Chain_Index]);


  }
  else if (Glo_Chain_Index == Glo_Chain_Lenght)
  {
   ADC_Chain_EOJ();

  }
 }
 else
 {

 }
}
