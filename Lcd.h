#ifndef LCD_H
#define LCD_H

#define D4  RD5
#define D5  RD4
#define D6  RC5
#define D7  RD3
#define RS  RD7
#define EN  RD6

void LCD_Intial(void);
void LCD_Data(unsigned char mode, unsigned char data);
void LCD_Word(const char *word);
void LCD_Display_2Digit(int value);
void LCD_Display_3Digit(int value);
void LCD_Display_4Digit(int value);
void LCD_Set_Cursor(char row, char col);

#endif
