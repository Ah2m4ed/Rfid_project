/*
 * reci.c
 *
 * Created: 3/10/2018 5:14:19 PM
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
int cnt,cnt2,cnt3;
char*cnt_lcd,*cnt2_lcd,*cnt3_lcd;
int main(void)
{
UART_INIT();
lcd_init();	
    while(1)
    { char recv=UART_Read();
		_delay_ms(10);
		switch (recv)
		
		{
			case 'a':lcd_delete();_delay_ms(1);lcd_out(0,0,"yes"); _delay_ms(1); cnt++;if(cnt==2){cnt=1;}break;
				case 'b':lcd_delete();_delay_ms(1);lcd_out(0,0,"no");_delay_ms(1);cnt2++; if(cnt2==2){cnt2=1;} break;
					case 'c':lcd_delete();_delay_ms(1);lcd_out(0,0,"null");_delay_ms(1);cnt3++; if(cnt3==2){cnt3=1;} break;
						case 'd':lcd_delete();_delay_ms(1);lcd_out(0,0,"yes");_delay_ms(1);cnt++; if(cnt==3){cnt=2;} break;
							case 'e':lcd_delete();_delay_ms(1);lcd_out(0,0,"no");_delay_ms(1);cnt2++; if(cnt2==3){cnt2=2;} break;
								case 'f':lcd_delete();_delay_ms(1);lcd_out(0,0,"null");_delay_ms(1);cnt3++; if(cnt3==3){cnt3=2;} break;
		
		case 'm':
		cnt_lcd=convertData(cnt);
		cnt2_lcd=convertData(cnt2);	
		cnt3_lcd=convertData(cnt3);
		lcd_delete();
		lcd_out(0,0,"number of yes");
		lcd_out(1,1,cnt_lcd);
		lcd_delete();
		lcd_out(0,0,"number of no");
		lcd_out(1,1,cnt2_lcd);
		lcd_delete();
		lcd_out(0,0,"number of null");
		lcd_out(1,1,cnt3_lcd);break;				
		}
		
		
        //TODO:: Please write your application code 
    
}