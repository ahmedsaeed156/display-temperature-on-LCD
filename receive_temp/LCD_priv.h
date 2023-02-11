/**************************************/
/* Description : LCD private c File   */
/* Author      : kpit                 */
/* Version     : 0.1V                 */
/* Date        : 13:45:20  03 Dec 2022*/
/* History     : 0.1V Initial Creation*/
/**************************************/
#ifndef LCD_PRIV_H
#define LCD_PRIV_H

#define LCD_4BIT_MODE   0
#define LCD_8BIT_MODE   1

#define LCD_ONE_LINE    0
#define LCD_TWO_LINES   1

#define LCD_FONT_5X7    0
#define LCD_FONT_5X11   1

#define LCD_DISPLAY_OFF 0
#define LCD_DISPLAY_ON  1

#define LCD_CURSOR_OFF       0
#define LCD_CURSOR_ON        1


#define LCD_CURSOR_BLINK_OFF       0
#define LCD_CURSOR_BLINK_ON        1

#define LCD_RTL        0
#define LCD_LTR        1

#define LCD_SHIFT_OFF      0
#define LCD_SHIFT_ON       1





typedef struct 
{
	uint8 u8Mode      :1;
	uint8 u8UsedLines:1;
	uint8 u8CharFont :1;
	uint8 u8DisplayState:1 ;
	uint8 u8CursorState  :1;
	uint8 u8CursorBlinkState  :1;
	uint8 u8IncrementMode:1 ;
	uint8 u8ShiftMode:1 ;
	
}tstrLcdHwCfg;

typedef struct 
{
	uint8 u8Rs ;
	uint8 u8Rw ;
	uint8 u8En ;
    uint8 u8Data[8] ;

}tstrLcdConnectionCfg;

typedef struct 
{
	tstrLcdHwCfg           strLcdHwCfg ; 
	tstrLcdConnectionCfg   strLcdConnectionCfg ;
	
}tstrLcdConfigset;


extern tstrLcdConfigset  LCD_astrConfigSet[LCD_MAX_NUM] ;


static void voidWriteCmd(uint8 u8LcdIndxCpy , uint8 u8CmdCpy);

static void voidLcdHelper(uint8 u8LcdIndxCpy , uint8 u8CmdDataCpy);




#endif