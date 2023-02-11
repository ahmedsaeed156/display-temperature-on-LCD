/**************************************/
/* Description : LCD header File      */
/* Author      : Aboelno              */
/* Version     : 0.1V                 */
/* Date        : 13:45:20  03 Dec 2022*/
/* History     : 0.1V Initial Creation*/
/**************************************/
#ifndef LCD_H
#define LCD_H

void LCD_voidInit(void);

void LCD_voidWriteCmd(uint8 u8LcdIndxCpy , uint8 u8CmdCpy);

void LCD_voidDisplayChar(uint8 u8LcdIndxCpy , uint8 u8CharCpy);

#endif





