/*
 * main.c
 *
 *  Created on: Dec 23, 2022
 *      Author: Ahmed Saeed
 */
#include "STD_Types.h"
#include "BIT_Math.h"
#include <util/delay.h>

#include "DIO.h"
#include "ADC.h"
#include"USART.h"


void main(void)
{
	uint16 u16ReadLoc = 0;

	uint16 u16AnalogValue = 0;

	DIO_voidInit();
	ADC_voidInit();

	ADC_voidEnable();
	USART_voidInit();


	while(1)
	{

        //SADC_voidStartConversion(ADC_CHANNEL_0);
		u16ReadLoc = ADC_u16ReadSync(ADC_CHANNEL_0);

		//		//u16AnalogValue = (u16ReadLoc*500)/265;

		u16AnalogValue = (u16ReadLoc*500)/1024;
		_delay_ms(200);

		USART_voidSend(u16AnalogValue);
		_delay_ms(200);




		/* 1 2 3*/

	}
}
