/***************************************/
/* Description : LCD config header File*/
/* Author      : kpit                  */
/* Version     : 0.1V                  */
/* Date        : 13:45:20  03 Dec 2022 */
/* History     : 0.1V Initial Creation */
/***************************************/
#include "STD_Types.h"

#include "DIO.h"
#include "LCD_cfg.h"
#include "LCD_priv.h"


tstrLcdConfigset  LCD_astrConfigSet[LCD_MAX_NUM]=
{
	/* Configuration for LCD 0     */
	{
		/* Hw config configuration */
		{
			LCD_8BIT_MODE  ,  LCD_TWO_LINES  , LCD_FONT_5X7 ,
			LCD_DISPLAY_ON ,  LCD_CURSOR_OFF , LCD_CURSOR_BLINK_OFF ,
			LCD_LTR        ,  LCD_SHIFT_OFF
		}
		,
		/* connection configuration */
		{
				/* Rs             Rw                En      */
				DIO_PIN_NUM_29 , DIO_PIN_NUM_30 , DIO_PIN_NUM_31   ,
				
				/*Data array*/
				{
					/* D0             D1            D2            D3          */
					DIO_PIN_NUM_16 , DIO_PIN_NUM_17 ,DIO_PIN_NUM_18,DIO_PIN_NUM_19,
					
					/* D4             D5               D6             D7         */
					DIO_PIN_NUM_20, DIO_PIN_NUM_21,DIO_PIN_NUM_22,DIO_PIN_NUM_23
				}
			
			
		}
	}
	
};















