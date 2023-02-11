/**************************************/
/* Description : ADC interface file   */
/* Author      : Abo elnour           */
/* Version     : 0.1v                 */
/* Date        : 23 Dec 2022          */
/* History     : 0.1v initial creation*/
/**************************************/
#ifndef  ADC_H
#define  ADC_H

#define ADC_CHANNEL_0   0
#define ADC_CHANNEL_1   1
#define ADC_CHANNEL_2   2
#define ADC_CHANNEL_3   3
#define ADC_CHANNEL_4   4
#define ADC_CHANNEL_5   5
#define ADC_CHANNEL_6   6
#define ADC_CHANNEL_7   7
#define ADC_CH0_CH0_G10 8
#define ADC_CH1_CH0_G10 9


#define ADC_SGL_MODE        8
#define ADC_FREE_RUN_MODE   0
#define ADC_ANALOG_CMP_MODE 1
#define ADC_EXTINT0_MODE    2

void ADC_voidInit(void);
void ADC_voidEnable(void);
void ADC_voidDisable(void);
void ADC_voidEnableInterrupt(void);
void ADC_voidDisableInterrupt(void);
void ADC_voidSetCallback(pf pfCallbackCpy);
void ADC_voidStartConversion(uint8 u8ChannelNbCpy);
void ADC_voidChangeMode(uint8 u8ModeCpy);

uint16 ADC_u16ReadSync(uint8 u8ChannelNbCpy);
uint16 ADC_u16ReadAsync(void);



#endif

