/*
* KeyPad_Cfg.c
*
* Created: 21-Jan-23 9:03:45 AM
*  Author: Peter Ghali
*/
#include "../../00-LIB/STD_TYPES.h"

#include "KeyPad.h"
#include "KeyPad_Cfg.h"


#include "../../01-MCAL/00-DIO/DIO.h"


u8 KeyPad_LookUpTable [NUMBER_OF_ROWS] [NUMBER_OF_COLMUNS]  = {
			/*Col0*/ /*Col1*/ /*Col2*/ /*Col3*/
	/*Row0*/{	7	,	8	,	9	,	16	},
	/*Row1*/{	4	,	5	,	6	,	15	},
	/*Row2*/{	1	,	2	,	3	,	14	},
	/*Row3*/{	10	,	11	,	12	,	13	}
};

/*
	An Array with the Rows Pins (The input pins )
*/
const u8 KeyPad_ArrRowsCfg [NUMBER_OF_ROWS] =
{
	/*ROW0*/ DIO_enuPORTA_Pin0,
	/*ROW1*/ DIO_enuPORTA_Pin1,
	/*ROW2*/ DIO_enuPORTA_Pin2,
	/*ROW3*/ DIO_enuPORTA_Pin3
};
/*
	An Array with the Cols Pins (The output pins )
*/
const u8 KeyPad_ArrColsCfg [ NUMBER_OF_COLMUNS] =
{
	/*COL0*/ DIO_enuPORTA_Pin4,
	/*COL1*/ DIO_enuPORTA_Pin5,
	/*COL2*/ DIO_enuPORTA_Pin6,
	/*COL3*/ DIO_enuPORTA_Pin7

};