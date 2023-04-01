/*
 * DIO_Cfg.c
 *
 * Created: 18/1/2023 7:06:48 PM
 *  Author: Peter_Ghali
 */ 
#include "DIO_Cfg.h"
#include "DIO.h"

 const DIO_strPinCfg_t DIO_strPinCfg [DIO_enuNumberofPins] =
{
	/*PORTA*/   /*Pin Direction*/    /*Pull_Up Pull_Down*/
	/*PIN0*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN1*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN2*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN3*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN4*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW},
	/*PIN5*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN6*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN7*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },

	/*PORTB*/   /*Pin Direction*/    /*Pull_Up Pull_Down*/
	/*PIN0*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN1*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN2*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN3*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN4*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN5*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN6*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN7*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },

	/*PORTC*/   /*Pin Direction*/    /*Pull_Up Pull_Down*/
	/*PIN0*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN1*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN2*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN3*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN4*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN5*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN6*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN7*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },

	/*PORTD*/   /*Pin Direction*/    /*Pull_Up Pull_Down*/
	/*PIN0*/	{DIO_DIR_INPUT,     DIO_INPUT_TRI_STATE },
	/*PIN1*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN2*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW},
	/*PIN3*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN4*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN5*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
	/*PIN6*/	{DIO_DIR_INPUT,     DIO_INPUT_PULL_UP },
	/*PIN7*/	{DIO_DIR_OUTPUT,     DIO_OUTPUT_LOW },
};