/*
 * GccApplication1.c
 *
 * Created: 3/9/2018 12:23:33 PM
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

char clinet_code[5][10]={"moatasem","kosta","mohamed","ahmed","ali"};
char id_code[5][5]={"0xf1","0xf2","0xf3","0xf4","0xf5"};
	char code_recv[6];
	char list[5][10];	
	unsigned char find,abss;
	char*find_lcd, *abss_lcd;
int i,j;
int flag=0;
void attendance_1();
void attendance_2();
void attendance_3(); 
void attendance_4();
void display_list();
void intr_init();
#define    ISR_INT0_PD2    INT0_vect


ISR( ISR_INT0_PD2 ){
	
  display_list();
  
}
ISR(INT2_vect){
	static int cnt=0;
	if(cnt==0){
		lcd_delete();
		  lcd_out(0,0,"attendance num");
		  
		  find_lcd=convertData(find);
		  lcd_out(1,1,find_lcd);
		  _delay_ms(500);
			lcd_delete();
		  abss=4-find;
		  abss_lcd=convertData(abss);
		  lcd_out(0,0,"absent num");
		  lcd_out(1,1,abss_lcd);
		  find=0;
		  abss=0;
		  cnt++;}
}
int main(void)
{
	lcd_init();
	UART_INIT();
	
	CLR_BIT(DDRD,7);
	CLR_BIT(DDRD,2);
		CLR_BIT(DDRB,2);
	SET_BIT(PORTB,2);
 intr_init();
    while(1)
    {
	start :
		j=0;flag =0;

lcd_out(1,1,"ener ID");

		for (i=0;i<5;i++)
		{ code_recv[i]=UART_Read();}
			if((strlen(code_recv)!=5)){goto start;} 

			 	attendance_1();	
				 attendance_2();
				  attendance_3();
				   attendance_4();	
				 /*if(flag!=4)
				 {LCD_Clear();lcd_out(1,1,"tryagin");}*/
				   
				 
				   }				
				
			//lcd_out(0,0,code_recv);
						 
				
	
		

		
	
		
 
}

void display_list(){
		lcd_delete();
		  lcd_out(0,0,"first one");
		  lcd_out(1,1,list[0]);
		  _delay_ms(1000);
		  LCD_Clear();
		  lcd_out(0,0,"second one");
		  lcd_out(1,1,list[1]);
		  _delay_ms(1000);
		  LCD_Clear();
		  lcd_out(0,0,"third one");
		  lcd_out(1,1,list[2]);
		  _delay_ms(1000);
		  LCD_Clear();
		  lcd_out(0,0,"fourth one");
		  lcd_out(1,1,list[3]);
		  _delay_ms(100);
	
}
void attendance_1(){
	 _delay_ms(100);
		lcd_delete();
	flag=0;
		for (i=0;i<5;i++)
		{
			if(code_recv[i]==id_code[0][i])
			{
				flag++;
			}}
			if (flag==4 &&find==0){
				lcd_out(0,1,clinet_code[0]);
				for (i=0;i<sizeof(clinet_code[0]);i++){
				list[0][i]=clinet_code[0][i];}
			find++;
			}
			flag=0;
}
void attendance_2(){
	_delay_ms(100);
		lcd_delete();
	flag=0;
	for (i=0;i<5;i++)
	{
		if(code_recv[i]==id_code[1][i])
		{
			flag++;
		}}
		if (flag==4&&find==1){
			lcd_out(0,1,clinet_code[1]);
			for (i=0;i<sizeof(clinet_code[1]);i++){
			list[1][i]=clinet_code[1][i];}
		find++;
		}flag=0;
	}
	void attendance_3(){
		_delay_ms(100);
			lcd_delete();
		flag=0;
		for (i=0;i<5;i++)
		{
			if(code_recv[i]==id_code[2][i])
			{
				flag++;
			}}
			if (flag==4&&find==2){
				lcd_out(0,1,clinet_code[2]);
				for (i=0;i<sizeof(clinet_code[2]);i++){
				list[2][i]=clinet_code[2][i];}
			find++;
			}flag=0;
		}
		void attendance_4(){
			_delay_ms(100);
			lcd_delete();
			flag=0;
			for (i=0;i<5;i++)
			{
				if(code_recv[i]==id_code[3][i])
				{
					flag++;
				}}
				if (flag==4&&find==3){
					lcd_out(0,1,clinet_code[3]);
				for (i=0;i<sizeof(clinet_code[3]);i++){
				list[3][i]=clinet_code[3][i];}
				find++;
				}flag=0;
				  
			}
			void intr_init(){
					MCUCR |= (1<<1)|(1<<0); // falling edge
					GICR |=(1<<6)|(1<<5); // enable INT0 set pin6
					SREG |=(1<<7); // set GIE pin7
			}
			void lcd_delete(){
				lcd_out(0,0,"                    ");
					lcd_out(0,1,"                    ");
				
				
			}