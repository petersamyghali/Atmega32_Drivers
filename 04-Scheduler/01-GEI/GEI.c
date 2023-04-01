// /*
// * GEI.c
// *
// * Created: 24-Jan-23 9:40:54 PM
// *  Author: Peter Ghali
// */
// #include "../../00-LIB/STD_TYPES.h"
// #include "../../00-LIB/Bit_Math.h"
// 
// #include "GEI.h"
// #include "GEI_Cfg.h"
// #include "GEI_Prv.h"
// //Setting the I_Bit to one 
// GEI_tenuErrorStatus GEI_enuEnable(void)
// {
// 	GEI_tenuErrorStatus Error_Status = GEI_enuOK ;
// 	SET_BIT(SREG_REGISTER , I_BIT);
// 	
// 	return Error_Status ;
// 	
// }
// //Clearing the I_Bit to zero 
// GEI_tenuErrorStatus GEI_enuDisable(void)
// {
// 	GEI_tenuErrorStatus Error_Status = GEI_enuOK ;
// 	CLR_BIT(SREG_REGISTER , I_BIT);
// 	return Error_Status ;
// }