/*
 * selections.c
 *
 * Created: 3/10/2018 4:10:28 PM
 *  Author: M
 */ 



#define F_CPU 8000000UL
#include <avr/io.h>
#include "macros.h"
#include "AVR_UART.h"
#include "lcd.h"
#include <string.h>
#include <util/delay.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
//----------------------------------------
int buffer_1,buffer_2,buffer_3;
//---------------------------------------
void recv_1();
void recv_2();
void recv_3();
void read();
void decider();
void select_output();
int main(void)
{
	
	UART_INIT();
	select_output();
	
    while(1)
    {
		if(GET_BIT(PINC,0)==1){UART_Transmit('a');}
				if(GET_BIT(PINC,1)==1){UART_Transmit('b');}
						if(GET_BIT(PINC,2)==1){UART_Transmit('c');}
								if(GET_BIT(PINC,3)==1){UART_Transmit('d');}
										if(GET_BIT(PINC,4)==1){UART_Transmit('e');}
												if(GET_BIT(PINC,5)==1){UART_Transmit('f');}
		
        //TODO:: Please write your application code 
    }
}
void select_output(){
DDRC=0x00;
}
