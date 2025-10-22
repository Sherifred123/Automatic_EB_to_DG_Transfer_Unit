//LCD.C
#include <xc.h>
#include "main.h"
#include "SystemConfig.h"
#include "Timer.h"
#include "Lcd.h"
#include "Ac_Calculation.h"
#include "EEPROM.h"

void pulse ()
{
    EN=ON;
    __delay_ms(10);
    EN=OFF;
    __delay_ms(10);
}

void send_nibble(unsigned char nibble)
{
    D4 = (nibble >> 0) & 1;
    D5 = (nibble >> 1) & 1;
    D6 = (nibble >> 2) & 1;
    D7 = (nibble >> 3) & 1;
}

void LCD_Data(unsigned char mode, unsigned char data)
{
    RS = mode;
    send_nibble(data >> 4);
    pulse();
    send_nibble(data & 0x0F);
    pulse();
}

void LCD_Word(const char *word)
{
    while(*word) 
    LCD_Data(1, *word++);
}

void LCD_Display_2Digit(int value)
{
      LCD_Data(1, ((value / 10) % 10) + '0');
    LCD_Data(1, (value % 10) + '0');
}

void LCD_Display_3Digit(int value)
{
    LCD_Data(1, ((value / 100) % 10) + '0');
    LCD_Data(1, ((value / 10) % 10) + '0');
    LCD_Data(1, (value % 10) + '0');
}


void LCD_Display_4Digit(int value)
{
    LCD_Data(1, ((value / 1000) % 10) + '0');
    LCD_Data(1, ((value / 100) % 10) + '0');
    LCD_Data(1, ((value / 10) % 10) + '0');
    LCD_Data(1, (value % 10) + '0');
}

void LCD_Set_Cursor(char row, char col)
{
    char address = (row == 1) ? (0x80 + col - 1) : (0xC0 + col - 1);
    LCD_Data(0, address);
}

void LCD_Intial(void)
{
    LCD_Data(0, 0x02);
    LCD_Data(0, 0x28);
    LCD_Data(0, 0x0C);
    LCD_Data(0, 0x06);
    LCD_Data(0, 0x01);
}
