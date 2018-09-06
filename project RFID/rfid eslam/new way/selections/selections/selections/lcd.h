#include "macros.h"
#include <avr/io.h>

void lcd_send_command(uint8_t cmd );

void lcd_init();


void LCD_SendData(unsigned char data);
	void lcd_delete();


void LCD_SET_CURSOR (unsigned char x, unsigned char y);


void LCD_SendString(char *str);

void LCD_Clear(void);


void lcd_out( unsigned char x, unsigned char y,char *str);

char* convertData(unsigned int var);
