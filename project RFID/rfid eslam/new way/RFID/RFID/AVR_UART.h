/*
 * AVR_UART.h
 *
 * Created: 6/7/2016 3:13:41 PM
 *  Author: Ahmed
 */ 


#ifndef AVR_UART_H_
#define AVR_UART_H_

#include<avr/io.h>
#include "UART_Confg.h"

#define MYUBRR FOSC/16/BAUD-1

void UART_INIT(void);
void UART_Transmit(uint8_t data);
uint8_t UART_Read(void);
void UART_Transmit_string (char * str);


#endif /* AVR_UART_H_ */