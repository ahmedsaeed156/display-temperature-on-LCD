/**************************************/
/* Description : DIO interface file   */
/* Author      : Abo elnour           */
/* Version     : 0.1v                 */
/* Date        : 26 Nov 2022          */
/* History     : 0.1v initial creation*/
/**************************************/
#ifndef DIO_H
#define DIO_H

#define DIO_LOW    0
#define DIO_HIGH   1


#define DIO_DEACTIVATE    0
#define DIO_ACTIVATE      1

#define DIO_PIN_NUM_0   0 
#define DIO_PIN_NUM_1   1 
#define DIO_PIN_NUM_2   2 
#define DIO_PIN_NUM_3   3 
#define DIO_PIN_NUM_4   4 
#define DIO_PIN_NUM_5   5 
#define DIO_PIN_NUM_6   6 
#define DIO_PIN_NUM_7   7 
#define DIO_PIN_NUM_8   8 
#define DIO_PIN_NUM_9   9 
#define DIO_PIN_NUM_10  10
#define DIO_PIN_NUM_11  11
#define DIO_PIN_NUM_12  12
#define DIO_PIN_NUM_13  13
#define DIO_PIN_NUM_14  14
#define DIO_PIN_NUM_15  15
#define DIO_PIN_NUM_16  16
#define DIO_PIN_NUM_17  17
#define DIO_PIN_NUM_18  18
#define DIO_PIN_NUM_19  19
#define DIO_PIN_NUM_20  20
#define DIO_PIN_NUM_21  21
#define DIO_PIN_NUM_22  22
#define DIO_PIN_NUM_23  23
#define DIO_PIN_NUM_24  24
#define DIO_PIN_NUM_25  25
#define DIO_PIN_NUM_26  26
#define DIO_PIN_NUM_27  27
#define DIO_PIN_NUM_28  28
#define DIO_PIN_NUM_29  29
#define DIO_PIN_NUM_30  30
#define DIO_PIN_NUM_31  31


void DIO_voidInit(void);

tenuErrorStatus DIO_enuWritePin(uint8 u8PinNumCpy,uint8 u8PinValueCpy);     

tenuErrorStatus DIO_enuReadPin(uint8 u8PinNumCpy ,uint8 * pu8PinValueCpy );          

tenuErrorStatus DIO_enuStatePullup(uint8 u8PinNumCpy, uint8 u8StateCpy);         

tenuErrorStatus DIO_enuWriteGroup(uint8 *pau8PinNumCpy,uint8 * pau8PinValueCpy , uint8 u8SizeCpy);     

#endif
