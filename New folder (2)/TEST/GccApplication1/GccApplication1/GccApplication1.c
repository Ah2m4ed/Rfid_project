#define F_CPU 8000000UL
#include <avr/io.h>
#include <string.h>
#include "lcd.h"
#include "USART_RS232_H_file.h"	
#include "LCD16x2_4bit.h"		
#include <util/delay.h>

int main()
{
	char RFID[15];
	USART_Init(9600);			
	lcd_init();					
	lcd_clear();			
	lcd_out(0,0,"RFID:");
	while(1)
	{	
		for (int i=0;i<12;i++)
		{
			RFID[i]=USART_RxChar();
		}
		_delay_us(10);
		lcd_out(0,1,RFID);		/* print 12 digit tag number on LCD */
	}  
return 0;
}