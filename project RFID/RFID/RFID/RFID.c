/*
 * RFID.c
 *
 * Created: 3/10/2018 12:32:07 AM
 *  Author: ahmed
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include "macros.h"
#include "AVR_UART.h"
#include "lcd.h"
#include "USART_RS232_H_file.h"
#include <string.h>
#include <util/delay.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#define    ISR_INT0_PD2    INT0_vect
//-----------------------------------------------------
char clinet_code[10][12]={"Fawzy","Hendawy","Eslam","Abdallah","Abdelfatah"};
char id_code[5][30]={"14006D4F784E","14006D595D7D","14006DEE9205","14006DE81B8A","14006D60756C"};
	char code_recv[30];
	char list[10][12];

//-----------------------------------------------------

//-----------------------------------------------------
char* Read_val;
char*find_lcd,*abss_lcd;
//flags/counters----------------------------------
int flag,i,j,attendance=10,cnt,cnt2,cnt3,cnt4,cnt5,cnt6,cnt7,find ,abss,k;
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
	CLR_BIT(DDRA,7);
	lcd_init();
	//UART_INIT();
	USART_Init(9600);
	intr_init();
	k=1;
    while(1)
    {
		
		if (GET_BIT(PINA,7)==1)
		{lcd_delete();
		lcd_out(0,0,"please enter ID");
      do { Read_val=Read();
	       _delay_ms(1);
       }while ((strlen(Read_val))!=12);
	  // while ((strlen(Read_val))!=13);

	    attendance=compare(Read_val);

		display_attendance(attendance);

	   }        
	}	
}
char* Read(){
   while(USART_RxChar()!=2);
	
		//for (i=0;i<13;i++)
		for (i=0;i<12;i++)
	{ 
		code_recv[i]=USART_RxChar();
		
	}_delay_ms(1);
	lcd_delete();
	lcd_out(0,0,"CODE is:");
	_delay_ms(500);
    lcd_delete();
	lcd_out(0,0,code_recv);
	_delay_ms(500);

	return code_recv;
	   


}

int compare(char*read_val){
	flag=0;
	for(j=0;j<5;j++)
	{
		// for(i=0;i<13;i++)
		for(i=0;i<12;i++)
	          {
				  if(read_val[i]==id_code[j][i] )
	                {_delay_ms(1);
		              flag++;
	                }

			   }

	if(flag==12) return j ;
	 flag=0;

	}

}
void display_list(){
	static int con=0;
	if (con==0)
	{
	if (cnt||cnt2||cnt3||cnt4||cnt5)
	{
	lcd_delete();
	lcd_out(0,0,"first one");
	_delay_ms(500);
	lcd_delete();
	lcd_out(0,0,list[0]);
	_delay_ms(500);
	LCD_Clear();
	lcd_out(0,0,"second one");
	_delay_ms(500);
	lcd_delete();
	lcd_out(0,0,list[1]);
	_delay_ms(500);
	LCD_Clear();
	lcd_out(0,0,"third one");
	_delay_ms(500);
	lcd_delete();
	lcd_out(0,0,list[2]);
	_delay_ms(500);
	LCD_Clear();
	lcd_out(0,0,"fourth one");
	_delay_ms(500);
	lcd_delete();
	lcd_out(0,0,list[3]);
	_delay_ms(500);
	LCD_Clear();
	lcd_out(0,0,"fifth one");
	_delay_ms(500);
	lcd_delete();
	lcd_out(0,0,list[4]);
	_delay_ms(500);
	}
	con++;
	}		
	/*LCD_Clear();
	lcd_out(0,0,"sixth one");
	lcd_out(1,1,list[5]);
	_delay_ms(500);
	LCD_Clear();
	lcd_out(0,0,"seventh one");
	lcd_out(1,1,list[6]);
	_delay_ms(500);*/

}
void display_attendance(int var){

	switch (var)
	{
		case 0: lcd_delete(); SET_BIT(DDRA,0); SET_BIT(PORTA,0);lcd_out(0,0,"first student");_delay_ms(500);lcd_delete();lcd_out(0,0,clinet_code[0]);_delay_ms(500); CLR_BIT(PORTA,0);lcd_delete();
		if(cnt!=1){cnt++;} if(cnt==1){
			for (i=0;i<sizeof(clinet_code[0]);i++){
                            list[0][i]=clinet_code[0][i];}}break;

		case 1: lcd_delete();SET_BIT(DDRA,0); SET_BIT(PORTA,0); lcd_out(0,0,"second student");_delay_ms(500);lcd_delete();lcd_out(0,0,clinet_code[1]);_delay_ms(500);CLR_BIT(PORTA,0);lcd_delete();if(cnt2!=1){++cnt2;} if(cnt2==1){
			for (i=0;i<sizeof(clinet_code[1]);i++){
		list[1][i]=clinet_code[1][i];}}
		break;

		case 2: lcd_delete();SET_BIT(DDRA,0); SET_BIT(PORTA,0); lcd_out(0,0,"third student");_delay_ms(500);lcd_delete();lcd_out(0,0,clinet_code[2]);_delay_ms(500);CLR_BIT(PORTA,0);lcd_delete();if(cnt3!=1){++cnt3;}
		if(cnt3==1){	for (i=0;i<sizeof(clinet_code[2]);i++){
		list[2][i]=clinet_code[2][i];}}
		break;

		case 3: lcd_delete(); SET_BIT(DDRA,0); SET_BIT(PORTA,0);lcd_out(0,0,"fourth student");_delay_ms(500);lcd_delete();lcd_out(0,0,clinet_code[3]);_delay_ms(500);CLR_BIT(PORTA,0);lcd_delete();if(cnt4!=1){cnt4++;}
		if(cnt4==1){	for (i=0;i<sizeof(clinet_code[3]);i++){
		list[3][i]=clinet_code[3][i];}}
		break;
		
		case 4: lcd_delete(); SET_BIT(DDRA,0); SET_BIT(PORTA,0);lcd_out(0,0,"fifth student");_delay_ms(500);lcd_delete();lcd_out(0,0,clinet_code[4]);_delay_ms(500);CLR_BIT(PORTA,0);lcd_delete();if(cnt5!=1){cnt5++;}
		if(cnt5==1){	for (i=0;i<sizeof(clinet_code[4]);i++){
		list[4][i]=clinet_code[4][i];}}
		break;
		
		/*case 5: lcd_delete(); SET_BIT(DDRA,0); SET_BIT(PORTA,0);lcd_out(0,0,"sixth student");lcd_out(1,1,clinet_code[5]);_delay_ms(500);CLR_BIT(PORTA,0);lcd_delete();if(cnt6!=1){cnt6++;}
		if(cnt6==1){	for (i=0;i<sizeof(clinet_code[5]);i++){
		list[5][i]=clinet_code[5][i];}}
		break;
		
		case 6: lcd_delete(); SET_BIT(DDRA,0); SET_BIT(PORTA,0);lcd_out(0,0,"seventh student");lcd_out(1,1,clinet_code[6]);_delay_ms(500);CLR_BIT(PORTA,0);lcd_delete();if(cnt7!=1){cnt7++;}
		if(cnt7==1){	for (i=0;i<sizeof(clinet_code[6]);i++){
		list[6][i]=clinet_code[6][i];}}
		break;*/

		default:lcd_delete(); SET_BIT(DDRA,1); SET_BIT(PORTA,1);lcd_out(0,0,"wrong id");_delay_ms(500);CLR_BIT(PORTA,1);lcd_delete();break;
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
		if (k)
		{
		if (cnt||cnt2||cnt3||cnt4||cnt5)
		{
		static int cntt=0;
		if(cntt==0){
		if(cnt==1){find++;}
		if(cnt2==1){find++;}
		if(cnt3==1){find++;}
		if(cnt4==1){find++;}
		if(cnt5==1){find++;}
		/*if(cnt6==1){find++;}
		if(cnt7==1){find++;}*/

			lcd_delete();
			lcd_out(0,0,"attendance num");

			find_lcd=convertData(find);
			_delay_ms(500);lcd_delete();
			lcd_out(0,0,find_lcd);
			_delay_ms(500);
			lcd_delete();
			abss=5-find;
			abss_lcd=convertData(abss);
			lcd_out(0,0,"absent num");
			_delay_ms(500);lcd_delete();
			lcd_out(0,0,abss_lcd);
			find=0;
			abss=0;
			cntt++;
		}			
	}
	else{
		lcd_delete();
		lcd_out(0,0,"attendance num");
		_delay_ms(500);
		lcd_delete();
		lcd_out(0,0,"zero");
		_delay_ms(500);
		lcd_delete();
		lcd_out(0,0,"absent num");
		_delay_ms(500);lcd_delete();
		lcd_out(0,0,"5");
		
	}
		}	
	}
