#define en 3
#define RW PB1
#define RS 4
#define PORT_data PORTA
#define PORT_CONT PORTD
#define F_CPU 8000000UL


#include <avr/io.h>
#include "macros.h"
#include <avr/delay.h>
#include <util/delay.h>
	
void lcd_send_command(uint8_t cmd ){
	PORT_data =cmd;
	
	// disabled RW
	CLR_BIT(PORT_CONT,RW);
	// enabel rs
	CLR_BIT(PORT_CONT,RS);
	
	//adjust enable 
	CLR_BIT(PORT_CONT,en);
	_delay_us(1);
	SET_BIT(PORT_CONT,en);
	_delay_us(1);
	
	//let lcd execute command
	_delay_ms(10);
	
}
void lcd_init(){
	// data on portb are output
	DDRA=0xff;
	PORTA=0;
	//control pins are output 
	SET_BIT(DDRD,en);
	SET_BIT(DDRD,RW);
	SET_BIT(DDRD,RS);
	// active enable 
	SET_BIT(PORT_CONT,en);
	
	//lcd_init 8bit mode
	lcd_send_command(0x38);
	//lcd on cursor off
	lcd_send_command(0x0c);
}

void LCD_SendData(unsigned char data)
{
	// Put Data on Port
	PORTA = data;
	// Set R/W to W
	CLR_BIT(PORT_CONT,RW);
	// Set RS to Data
	SET_BIT(PORT_CONT,RS);

//adjust enable
	CLR_BIT(PORT_CONT,en);
	_delay_us(1);
	SET_BIT(PORT_CONT,en);
	_delay_us(1);
	
	// Delay to let LCD Display Data
	_delay_ms(10);
}

void LCD_SET_CURSOR (unsigned char x, unsigned char y)
{
	if(y == 0)
	{
		lcd_send_command(0x80 + x);
	}
	else
	{
		lcd_send_command(0xC0+ x);
	}
}

void LCD_SendString(char *str)
{
	while(*str != '\0')
	{
		LCD_SendData(*str);
		str++;
	}
}
void LCD_Clear(void)
{
	// Send Clr command to LCD
lcd_send_command(0x01);
}

void lcd_out( unsigned char x, unsigned char y,char *str)
{
	LCD_SET_CURSOR(x, y);
	LCD_SendString(str);
}
char* convertData(unsigned int var)
{
	static char data[17];
	char* arr = &data[16];

	*arr = '\0';
if(var==0) return "zero";
else 

	while(var != 0)
	{
		arr--;
		*arr = (var%10) + '0';
		var = var / 10;
	}
	return arr;
}

void lcd_delete(){
	lcd_out(0,0,"                  ");
	lcd_out(0,1,"                  ");
	
	
}