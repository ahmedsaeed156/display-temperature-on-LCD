

#ifndef USART_H
#define USART_H
void USART_voidInit(void) ;

void USART_voidSend(uint16 u16Data ) ;
tenuErrorStatus USART_enuReceive(uint16 *pu16Data) ;

void USART_voidSendAsync(uint16 u16Data );
tenuErrorStatus USART_enuReceiveAsync(uint16 *pu16Data);


void USART_voidEnableIntRxComp(void);
void USART_voidDisableIntRxComp(void);
void USART_voidEnableIntTxComp(void);
void USART_voidDisableIntTxComp(void);
void USART_voidEnableIntTxEmpty(void);
void USART_voidDisableIntTxEmpty(void);
void USART_voidSetCallBackTxEmpty(pf pfCallCpy);

#endif