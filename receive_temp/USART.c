#include "STD_Types.h"
#include "BIT_Math.h"

#include "USART.h"
#include "USART_cfg.h"
#include "USART_priv.h"

pf    USART_pfCallTxComp;
uint16 USART_u16ReceivedValue = 0 ;
uint16 USART_u16TransmitValue = 0 ;

void USART_voidInit(void) 
{
uint8 u8TempBLoc = 0b00011000 ;  /* Enabel TX and RX by set bit 3 and 4*/
uint8 u8TempCLoc = 0b10000000 ;  /* Set the URSEL bit number 7 by 1 to configure read or write from UCSRC */
/* shoose number of bits to be send or recieve in data */
#if   USART_FRAME_DATA_SIZE ==     USART_DATA_SIZE_5 
CLR_BIT(u8TempCLoc,1);
CLR_BIT(u8TempCLoc,2);
CLR_BIT(u8TempBLoc,2);

#elif USART_FRAME_DATA_SIZE ==     USART_DATA_SIZE_6 
SET_BIT(u8TempCLoc,1);
CLR_BIT(u8TempCLoc,2);
CLR_BIT(u8TempBLoc,2);

#elif USART_FRAME_DATA_SIZE ==     USART_DATA_SIZE_7 
CLR_BIT(u8TempCLoc,1);
SET_BIT(u8TempCLoc,2);
CLR_BIT(u8TempBLoc,2);
#elif USART_FRAME_DATA_SIZE ==     USART_DATA_SIZE_8 
SET_BIT(u8TempCLoc,1);
SET_BIT(u8TempCLoc,2);
CLR_BIT(u8TempBLoc,2);
#else    /*USART_DATA_SIZE_9  */
SET_BIT(u8TempCLoc,1);
SET_BIT(u8TempCLoc,2);
SET_BIT(u8TempBLoc,2);
#endif
/* select if sync or async */
#if USART_MODE  ==   USART_ASYNC
CLR_BIT(u8TempCLoc,6);
#else
SET_BIT(u8TempCLoc,6);	
#endif

/*configure the stope bits in frame (2 or 1) */
#if USART_STOP_BITS_SIZE == USART_ONE_STOP 
CLR_BIT(u8TempCLoc,3);	
#else
SET_BIT(u8TempCLoc,3);	
#endif	


#if USART_PARITY_TYPE == USART_EVEN_PARITY
CLR_BIT(u8TempCLoc,4);	
SET_BIT(u8TempCLoc,5);	
#elif USART_PARITY_TYPE == USART_ODD_PARITY
SET_BIT(u8TempCLoc,4);	
SET_BIT(u8TempCLoc,5);
#else   /* no parity */
CLR_BIT(u8TempCLoc,4);	
CLR_BIT(u8TempCLoc,5);	
#endif
/* configere send data at rising or falling with respect to clock*/
#if USART_CLK_POLARITY ==  USART_SETUP_RISING
CLR_BIT(u8TempCLoc,0);	
#else
SET_BIT(u8TempCLoc,0);	
#endif
/* load in UBBRH and UBBRL with 51 to operate at baud rate 9600*/
/*USART_SPEED is a macros which is congigured in congif file to be 51 */ 

UBBRH = ((USART_SPEED>>8)&0x0F) ; /*make bit 0,1,2,3 in  UBBRH reg with ones to store in UBBRH last four bits in USART_SPEED  */
UBBRL = (uint8)USART_SPEED ;      /*stor in UBBRL reg first 8 bits in USART_SPEED*/
UCSRB = u8TempBLoc ;
UCSRC = u8TempCLoc ;	
	
}

void USART_voidSend(uint16 u16Data ) 
{
	
	while (GET_BIT(UCSRA , 5)!= 1);  /* pooling on the flag bit to make sure that UDR reg is ready and to recieve new data*/
	#if USART_FRAME_DATA_SIZE ==  USART_DATA_SIZE_9
	/* bit 0 in UCSRB reg used to store bit number 8 in the recieved data in case of 9 bit mode */
		if (GET_BIT(u16Data,8)== 0)
		{
			CLR_BIT(UCSRB,0); /* if bit 8 in data is 0 then store zero in bit 0 in USCRB reg */
		}
		else
		{
		   SET_BIT(UCSRB,0);  /* if bit 8 in data is 1 then store zero in bit 1 in USCRB reg */
		}	
	#endif
	/* store first 8 bits from data in UDR reg */
	UDR = u16Data ;
    
	
}

tenuErrorStatus USART_enuReceive(uint16 *pu16Data) 
{
	tenuErrorStatus enuReturnLoc =EOK ;
	uint8 u8StatusLoc = 0;
	uint8 u8NineBitLoc = 0 ;
	uint8 u8DataLoc = 0;
	while (GET_BIT(UCSRA , 7 ) ==0);  /* pooling on the flag bit to make sure that UDR reg recieved the data*/
	u8StatusLoc = UCSRA&0b00011100; /* check if ther are errors (frame ,parity,data over run errors*/
	u8NineBitLoc = GET_BIT(UCSRB,1); /* store bit number 8 */
	u8DataLoc = UDR ;                /* store first 8 bits from UDR */
	if (u8StatusLoc!=0)
	{
		enuReturnLoc = ENOK ;
	}
	else 
	{
		#if USART_FRAME_DATA_SIZE ==     USART_DATA_SIZE_9
		*pu16Data = u8NineBitLoc<<8 | u8DataLoc ;
		#else 
		*pu16Data =  u8DataLoc ;
		#endif
	}
	return enuReturnLoc ;
	
}


void USART_voidSendAsync(uint16 u16Data )
{
	USART_u16TransmitValue = u16Data ;
}

tenuErrorStatus USART_enuReceiveAsync(uint16 *pu16Data)
{
	tenuErrorStatus enuReturnLoc =EOK ;
	if (GET_BIT(USART_u16ReceivedValue , 15)!=0)
	{
		enuReturnLoc = ENOK ;
	}
	else 
	{
		*pu16Data = USART_u16ReceivedValue ;
	}
	return enuReturnLoc ;
}

void USART_voidEnableIntRxComp(void)
{
	SET_BIT(UCSRB,7);
}
void USART_voidDisableIntRxComp(void)
{
	CLR_BIT(UCSRB,7);	
}
void USART_voidEnableIntTxComp(void)
{
	SET_BIT(UCSRB,6);	
}
void USART_voidDisableIntTxComp(void)
{
	CLR_BIT(UCSRB,6);	
}
void USART_voidEnableIntTxEmpty(void)
{
	SET_BIT(UCSRB,5);
}
void USART_voidDisableIntTxEmpty(void)
{
	CLR_BIT(UCSRB,5);
}


/*Rx Complete ISR */
void __vector_13 (void) __attribute__ ((signal,used));
void __vector_13 (void)
{
	uint16 u16ResLoc = 0 ;
	uint8 u8StatusLoc = UCSRA&0b00011100;
	uint8 u8NineBitLoc = GET_BIT(UCSRB,1);
	uint8 u8DataLoc = UDR ;
	if (u8StatusLoc!=0)
	{
		SET_BIT(u16ResLoc,15);
	}
	else 
	{
		#if USART_FRAME_DATA_SIZE ==     USART_DATA_SIZE_9
		u16ResLoc = u8NineBitLoc<<8 | u8DataLoc ;
		#else 
		u16ResLoc =  u8DataLoc ;
		#endif
	}
	USART_u16ReceivedValue = u16ResLoc ;
	
}

void USART_voidSetCallBackTxComp(pf pfCallCpy)
{
	USART_pfCallTxComp = pfCallCpy ;
}

void __vector_15 (void) __attribute__ ((signal,used));
void __vector_15 (void)
{
	USART_pfCallTxComp();
}

void __vector_14 (void) __attribute__ ((signal,used));
void __vector_14 (void)
{
	uint16 u16Data = USART_u16TransmitValue;
	
	
	#if USART_FRAME_DATA_SIZE ==  USART_DATA_SIZE_9
		if (GET_BIT(u16Data,8)== 0)
		{
			CLR_BIT(UCSRB,0);
		}
		else
		{
		   SET_BIT(UCSRB,0);
		}	
	#endif
	UDR = u16Data ;
	
}
