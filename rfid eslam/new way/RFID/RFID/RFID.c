/*
 * RFID.c
 *
 * Created: 3/10/2018 12:32:07 AM
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
#define    ISR_INT0_PD2    INT0_vect
//-----------------------------------------------------
char clinet_code[5][10]={"moatasem","kosta","mohamed","ahmed","ali"};
char id_code[5][5]={"2014","2015","2016","2017","2018"};
	char code_recv[6];
	char list[5][10];	

//-----------------------------------------------------

//-----------------------------------------------------
char* Read_val;
char*find_lcd,*abss_lcd;
//flags/counters----------------------------------
int flag,i,j,attendance=10,cnt,cnt2,cnt3,cnt4,find ,abss;
//----------------------prototypes functions
char* Read();
int compare();
void display_attendance(int);
void intr_init();
void display_list();
void 	num_attend();
//----------------------------------

ISR( INT2_vect){
	
	num_attend();
	
}

ISR( ISR_INT0_PD2 ){
	
	display_list();
	
}
int main(void)
{
	lcd_init();
	UART_INIT();
	intr_init();
    while(1)
    {
		
		lcd_out(0,0,"please enter id");
      do { Read_val=Read(); 
	       _delay_ms(1);
       }while ((strlen(Read_val))!=5);
	   
	    attendance=compare(Read_val);
	
		display_attendance(attendance);
		
		
    }
}
char* Read(){
	
		for (i=0;i<5;i++)
	{ _delay_ms(1);
		code_recv[i]=UART_Read();
	
	}
	return code_recv;
	
	

}

int compare(char*read_val){
	flag=0;
	for(j=0;j<5;j++)
	{
		 for(i=0;i<5;i++)
	          {
				  if(read_val[i]==id_code[j][i] )
	                {_delay_ms(1);
		              flag++;
	                }  
			   	
			   }
	
	if(flag==4) return j ;
	 flag=0;
		
	}
	
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
void display_attendance(int var){
	
	switch (var)
	{
		case 0: lcd_delete(); lcd_out(0,0,"first student");lcd_out(1,1,clinet_code[0]);_delay_ms(500);lcd_delete();
		cnt++; if(cnt==1){
			for (i=0;i<sizeof(clinet_code[0]);i++){
                            list[0][i]=clinet_code[0][i];}}break;
							
		case 1: lcd_delete(); lcd_out(0,0,"second student");lcd_out(1,1,clinet_code[1]);_delay_ms(500);lcd_delete();++cnt2; if(cnt2==1){	
			for (i=0;i<sizeof(clinet_code[1]);i++){
		list[1][i]=clinet_code[1][i];}}
		break;
		
		case 2: lcd_delete(); lcd_out(0,0,"third student");lcd_out(1,1,clinet_code[2]);_delay_ms(500);lcd_delete();++cnt3; 
		if(cnt3==1){	for (i=0;i<sizeof(clinet_code[2]);i++){
		list[2][i]=clinet_code[2][i];}}
		break;
		
		case 3: lcd_delete(); lcd_out(0,0,"fourth student");lcd_out(1,1,clinet_code[3]);_delay_ms(500);lcd_delete();cnt4++; 
		if(cnt4==1){	for (i=0;i<sizeof(clinet_code[3]);i++){
		list[3][i]=clinet_code[3][i];}}break;
		
		default:lcd_out(0,0,"welcome enter id");_delay_ms(100);lcd_delete();break;
	}
}
	void intr_init(){
			CLR_BIT(DDRD,7);
			CLR_BIT(DDRD,2);
			CLR_BIT(DDRB,2);
			SET_BIT(PORTB,2);
		MCUCR |= (1<<1)|(1<<0); // falling edge
		GICR |=(1<<6)|(1<<5); // enable INT0 set pin6
		SREG |=(1<<7); // set GIE pin7
	}
	void num_attend(){
		
		static int cntt=0;
		if(cntt==0){
			if(cnt==1){find++;}
				if(cnt2==1){find++;}
					if(cnt3==1){find++;}
						if(cnt4==1){find++;}
				
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
			cntt++;
	}}