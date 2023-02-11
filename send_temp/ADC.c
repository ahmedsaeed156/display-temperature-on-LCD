/**************************************/
/* Description : ADC program file     */
/* Author      : Ahmed Saeed          */
/* Version     : 0.1v                 */
/* Date        : 23 Dec 2022          */
/* History     : 0.1v initial creation*/
/**************************************/
#include "STD_Types.h"
#include "BIT_Math.h"

#include "ADC.h"
#include "ADC_cfg.h"
#include "ADC_priv.h"



pf ADC_pfCall = NULL_PTR ;
uint16 ADC_u16ReadValue ;

void ADC_voidInit(void)
{
#if ADC_RES_MODE  ==  ADC_8BIT
	SET_BIT(ADCMUX , 5 ) ;
#else 
	CLR_BIT(ADCMUX , 5 ) ;
#endif 
	
#if  ADC_VOLTAGE_REF == ADC_AREF
	CLR_BIT(ADCMUX , 6 ) ;
	CLR_BIT(ADCMUX , 7 ) ;
#elif  ADC_VOLTAGE_REF == ADC_AVCC_REF
	SET_BIT(ADCMUX , 6 ) ;
	CLR_BIT(ADCMUX , 7 ) ;
#else 
	SET_BIT(ADCMUX , 6 ) ;
	SET_BIT(ADCMUX , 7 ) ;
	
#endif

ADCSRA &= 0b11111000;
ADCSRA |=ADC_PRESCALLER ;

#if ADC_TRIGGER_MODE ==ADC_SGL_MODE
    CLR_BIT(ADCSRA , 5) ;
#else 
	SET_BIT(ADCSRA , 5) ;
	SFIOR &=0b00011111;
	SFIOR |=ADC_TRIGGER_MODE<<5;
#endif
	


}
void ADC_voidEnable(void)
{
	
	SET_BIT(ADCSRA , 7);
}
void ADC_voidDisable(void)
{
	CLR_BIT(ADCSRA , 7);
}
void ADC_voidEnableInterrupt(void)
{
	SET_BIT(ADCSRA , 3);
}
void ADC_voidDisableInterrupt(void)
{
	CLR_BIT(ADCSRA , 3);
}
void ADC_voidSetCallback(pf pfCallbackCpy)
{
	ADC_pfCall = pfCallbackCpy ;
}
void ADC_voidStartConversion(uint8 u8ChannelNbCpy)
{
	ADCMUX &= 0b11100000  ;
	ADCMUX |= u8ChannelNbCpy ;
	SET_BIT(ADCSRA , 6) ;
}
void ADC_voidChangeMode(uint8 u8ModeCpy)
{
	if (u8ModeCpy < ADC_SGL_MODE )
	{
		SET_BIT(ADCSRA , 5) ;
		SFIOR &=0b00011111;
		SFIOR |=u8ModeCpy<<5;
	}
	else if (u8ModeCpy == ADC_SGL_MODE)
	{
		CLR_BIT(ADCSRA , 5) ;
	}
	else
	{
		
	}
}
/* polling */
uint16 ADC_u16ReadSync(uint8 u8ChannelNbCpy)
{
	uint16 u16ReadValueLoc ;
	ADC_voidStartConversion(u8ChannelNbCpy);
	/*wait conversion till finish*/
	while (GET_BIT(ADCSRA , 4) == 0);
	/*Clear Flag bit*/
	SET_BIT(ADCSRA , 4);
	
	#if ADC_RES_MODE == ADC_8BIT
	u16ReadValueLoc = ADCH ;
	#else
	u16ReadValueLoc = ADCL;
    u16ReadValueLoc |= (ADCH<<8) ;
	#endif
	
	return u16ReadValueLoc ;
	
}
uint16 ADC_u16ReadAsync(void)
{
	return ADC_u16ReadValue ;
}

void __vector_16 (void) __attribute__((signal ,used));
void __vector_16 (void) 
{
	if (ADC_pfCall != NULL_PTR)
	{
		ADC_pfCall();
	}
	#if ADC_RES_MODE == ADC_8BIT
	ADC_u16ReadValue = ADCH ;
	#else
	ADC_u16ReadValue = ADCL;
    ADC_u16ReadValue |= (ADCH<<8) ;
	#endif
	

}

