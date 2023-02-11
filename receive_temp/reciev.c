#include "STD_Types.h"
#include "BIT_Math.h"
#include "DIO.h"
#include "LCD.h"
#include "USART.h"
#include "util/delay.h"

void main (void)
{
	uint16 u16DataLoc;
	//uint8 u8CountLoc=0;
	DIO_voidInit();
	LCD_voidInit();
	USART_voidInit();
	LCD_voidWriteCmd(0 , 0x80);

	while(1)
	{
		USART_enuReceive(&u16DataLoc);
		LCD_voidDisplayChar(0,'T');
		LCD_voidDisplayChar(0,'E');
		LCD_voidDisplayChar(0,'M');
		LCD_voidDisplayChar(0,'P');
		LCD_voidDisplayChar(0,'=');
		LCD_voidDisplayChar(0,' ');




		LCD_voidDisplayChar(0,(u16DataLoc/100) +0x30);
		LCD_voidDisplayChar(0,((u16DataLoc%100)/10) +0x30);
		LCD_voidDisplayChar(0,(u16DataLoc%10)+0x30);
		_delay_ms(200);
		LCD_voidWriteCmd(0,0x01);


	}


}




