/**************************************/
/* Description : DIO program file     */
/* Author      : Abo elnour           */
/* Version     : 0.1v                 */
/* Date        : 2 Dec 2022           */
/* History     : 0.1v initial creation*/
/**************************************/
#include "STD_Types.h"
#include "BIT_Math.h"


#include "DIO.h"
#include "DIO_cfg.h"
#include "DIO_priv.h"


void DIO_voidInit(void)
{
   DDRA = CONC(DIO_PIN_DIR_7 ,DIO_PIN_DIR_6 ,DIO_PIN_DIR_5 ,DIO_PIN_DIR_4 ,DIO_PIN_DIR_3 ,DIO_PIN_DIR_2 ,DIO_PIN_DIR_1 ,DIO_PIN_DIR_0 );
   DDRB = CONC(DIO_PIN_DIR_15,DIO_PIN_DIR_14,DIO_PIN_DIR_13,DIO_PIN_DIR_12,DIO_PIN_DIR_11,DIO_PIN_DIR_10,DIO_PIN_DIR_9 ,DIO_PIN_DIR_8 );
   DDRC = CONC(DIO_PIN_DIR_23,DIO_PIN_DIR_22,DIO_PIN_DIR_21,DIO_PIN_DIR_20,DIO_PIN_DIR_19,DIO_PIN_DIR_18,DIO_PIN_DIR_17,DIO_PIN_DIR_16);
   DDRD = CONC(DIO_PIN_DIR_31,DIO_PIN_DIR_30,DIO_PIN_DIR_29,DIO_PIN_DIR_28,DIO_PIN_DIR_27,DIO_PIN_DIR_26,DIO_PIN_DIR_25,DIO_PIN_DIR_24);

}

tenuErrorStatus DIO_enuWritePin(uint8 u8PinNumCpy,uint8 u8PinValueCpy)
{
	
	tenuErrorStatus enuReturnStateLoc = EOK ;
	if (u8PinNumCpy >= DIO_PIN_NUM_0 && u8PinNumCpy <= DIO_PIN_NUM_7)
	{
		switch (u8PinValueCpy)
		{
			case DIO_LOW :
			 CLR_BIT (ODRA ,  u8PinNumCpy);
			break;
			case DIO_HIGH :
			 SET_BIT(ODRA , u8PinNumCpy);
			break ;
			default :
			enuReturnStateLoc = PARAM_OUT_RANGE ;
		}
	}
	else if (u8PinNumCpy >= DIO_PIN_NUM_8 && u8PinNumCpy <= DIO_PIN_NUM_15)
	{
		switch (u8PinValueCpy)
		{
			case DIO_LOW :
			 CLR_BIT (ODRB ,  u8PinNumCpy%8);
			break;
			case DIO_HIGH :
			 SET_BIT(ODRB , u8PinNumCpy%8);
			break ;
			default :
			enuReturnStateLoc = PARAM_OUT_RANGE ;
		}
	}
	else if (u8PinNumCpy >= DIO_PIN_NUM_16 && u8PinNumCpy <= DIO_PIN_NUM_23)
	{
		switch (u8PinValueCpy)
		{
			case DIO_LOW :
			 CLR_BIT (ODRC ,  u8PinNumCpy%8);
			break;
			case DIO_HIGH :
			 SET_BIT(ODRC , u8PinNumCpy%8);
			break ;
			default :
			enuReturnStateLoc = PARAM_OUT_RANGE ;
		}
	}
	else if (u8PinNumCpy >= DIO_PIN_NUM_24 && u8PinNumCpy <= DIO_PIN_NUM_31)
	{
		switch (u8PinValueCpy)
		{
			case DIO_LOW :
			 CLR_BIT (ODRD ,  u8PinNumCpy%8);
			break;
			case DIO_HIGH :
			 SET_BIT(ODRD , u8PinNumCpy%8);
			break ;
			default :
			enuReturnStateLoc = PARAM_OUT_RANGE ;
		}
	}
	else
	{
		enuReturnStateLoc = PARAM_OUT_RANGE ;
	}
	
	return enuReturnStateLoc ;
	
}     

tenuErrorStatus DIO_enuReadPin(uint8 u8PinNumCpy ,uint8 * pu8PinValueCpy )
{
	tenuErrorStatus  enuReturnStateLoc = EOK;
	
	if (pu8PinValueCpy != NULL_PTR)
	{
		//IDR
		if (u8PinNumCpy >= DIO_PIN_NUM_0 && u8PinNumCpy <= DIO_PIN_NUM_7)
		{
			*pu8PinValueCpy  = GET_BIT(IDRA , u8PinNumCpy);
		}
		else if (u8PinNumCpy >= DIO_PIN_NUM_8 && u8PinNumCpy <= DIO_PIN_NUM_15)
		{
			*pu8PinValueCpy  = GET_BIT(IDRB , u8PinNumCpy%8);		
		}
		else if (u8PinNumCpy >= DIO_PIN_NUM_16 && u8PinNumCpy <= DIO_PIN_NUM_23)
		{
			*pu8PinValueCpy  = GET_BIT(IDRC , u8PinNumCpy%8);
		}
		else if (u8PinNumCpy >= DIO_PIN_NUM_24 && u8PinNumCpy <= DIO_PIN_NUM_31)
		{
			*pu8PinValueCpy  = GET_BIT(IDRD , u8PinNumCpy%8);
		}
		else
		{
			enuReturnStateLoc = PARAM_OUT_RANGE ;
		}
	}
	else
	{
		enuReturnStateLoc = PARAM_NULL_PTR ;
	}
	
	return enuReturnStateLoc ;
	
}          

tenuErrorStatus DIO_enuStatePullup(uint8 u8PinNumCpy, uint8 u8StateCpy)        
{
   return DIO_enuWritePin(u8PinNumCpy,u8StateCpy);	
}

tenuErrorStatus DIO_enuWriteGroup(uint8 *pau8PinNumCpy,uint8 * pau8PinValueCpy , uint8 u8SizeCpy)
{
	tenuErrorStatus enuReturnStateLoc = EOK ;
	uint8 u8CntrLoc ;
	for (u8CntrLoc = 0 ; u8CntrLoc< u8SizeCpy ; u8CntrLoc++)
	{
		enuReturnStateLoc = DIO_enuWritePin(pau8PinNumCpy[u8CntrLoc],pau8PinValueCpy[u8CntrLoc]);
		if (enuReturnStateLoc !=EOK)
		{
			break;
		}
	}
}

