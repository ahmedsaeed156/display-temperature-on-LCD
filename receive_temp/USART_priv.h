

#ifndef USART_PRIV_H
#define USART_PRIV_H

#define USART_DATA_SIZE_5    0
#define USART_DATA_SIZE_6    1
#define USART_DATA_SIZE_7    2
#define USART_DATA_SIZE_8    3
#define USART_DATA_SIZE_9    7


#define USART_ASYNC      1
#define USART_SYNC       0 

#define USART_ONE_STOP   0
#define USART_TWO_STOP   1

#define USART_NO_PARITY     0
#define USART_EVEN_PARITY   1 
#define USART_ODD_PARITY    2


#define USART_SETUP_RISING    0 
#define USART_SETUP_FALLING   1


#define USART_BAUD_RATE_2400      207
#define USART_BAUD_RATE_4800      103
#define USART_BAUD_RATE_9600      51
#define USART_BAUD_RATE_14400     34


#define UCSRA *((volatile uint8 *) 0x2B )
#define UCSRB *((volatile uint8 *) 0x2A )
#define UCSRC *((volatile uint8 *) 0x40 )
#define UDR   *((volatile uint8 *) 0x2C )
#define UBBRH *((volatile uint8 *) 0x40 )
#define UBBRL *((volatile uint8 *) 0x29 )

#endif