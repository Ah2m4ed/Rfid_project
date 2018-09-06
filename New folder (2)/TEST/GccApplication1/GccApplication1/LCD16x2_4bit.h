/*
 * LCD16x2_4bit.h
 *
 * 
 */ 


#ifndef LCD16X2_4BIT_H_
#define LCD16X2_4BIT_H_
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define LCD_DPRT PORTA
#define LCD_DDDR DDRA
#define ctrl PORTD
#define LCD_RS 4
#define LCD_EN 3

void lcdcommand(unsigned char cmnd);
void lcddata(unsigned char data);
void lcdinit();
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_print(char *str);
void lcd_clear();




#endif /* LCD16X2_4BIT_H_ */