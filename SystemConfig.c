
//SYSTEM.C
#include<xc.h>
#include "main.h"
#include "SystemConfig.h"
#include "Timer.h"
#include "Lcd.h"
#include "Ac_Calculation.h"
#include "EEPROM.h"




extern uint8_t Set,Crank_Count,Crank_Sec,Crank_Interval,Warm_Up_Time,Cool_Down_Time,Mains_Healthy;

void System_Initialize(void)
{
    // PORT CONFIGURATION
    PORTA = 0x1E; TRISA = 0X1F;   // BAT,BUTTON,RLY6 AND OSCILLATOR
    PORTB = 0x00; TRISB = 0x3F;   // ADC INPUT[EB=3 AND DG=3]] AND PROGRAMMING PINS
    PORTC = 0x00; TRISC = 0x80;   // RELAY,LCD LED ON,I2C,LCD DATA PIN AND UART [Ob1000 0000]
    PORTD = 0x00; TRISD = 0x00;   // LCD PINS
    PORTE = 0x00; TRISE = 0x04;   // SENSOR, RELAY AND NTC SENSOR

    // ANALOG SETTINGS
    ANSEL  = 0x01;   // AN0
    ANSELH = 0x3F;   // AN12,AN10,AN8,AN9,AN11,AN13
//0b11 1111
}

void ADC_Intial(void)
{
    ADCON0 = 0x41;  // Channel 0, ADC enabled
    ADCON1 = 0x80;  // Right justified, Fosc/32
}

unsigned int ADC_Read(unsigned char channel)
{    
    ADCON0 = (channel << 2);   // Select channel bits
    ADCON0 |= 0x41;            // Turn on ADC
    __delay_us(5); 

    GO = 1;               // Start conversion
    while(GO);            // Wait till done

    return ((ADRESH << 8) + ADRESL); // 10-bit result
}



void Setting_Parameter()
{
     if (SW1 == PULLUP_ON && SW2 == PULLUP_ON)
        {
            Set = OPTION_1;
            LCD_Set_Cursor(1,1);
            LCD_Word("SETTINGS....");
            __delay_ms(400);
            LCD_Data(0, 0x01);
            while(SW1 == PULLUP_ON || SW2 == PULLUP_ON);

            // ===============================
            // SETTINGS SEQUENCE
            // ===============================

            // OPTION 1 - CRANK COUNT
            Adjust_Setting(&Crank_Count, CRANK_COUNT_MIN, CRANK_COUNT_MAX, "CRANK COUNT");
            LCD_Set_Cursor(2,1);
            LCD_Word("=====SETTED=====");
            __delay_ms(2000);
            LCD_Data(0, 0x01);

            // OPTION 2 - CRANK TIME
            Adjust_Setting(&Crank_Sec, CRANK_SEC_MIN, CRANK_SEC_MAX, "CRANK TIME=");
            LCD_Set_Cursor(2,1);
            LCD_Word("=====SETTED=====");
            __delay_ms(2000);
            LCD_Data(0, 0x01);

            // OPTION 3 - CRANK INTERVAL
            Adjust_Setting(&Crank_Interval, CRANK_INTERVAL_MIN, CRANK_INTERVAL_MAX, "CRANK INTVL=");
            LCD_Set_Cursor(2,1);
            LCD_Word("=====SETTED=====");
            __delay_ms(2000);
            LCD_Data(0, 0x01);

            // OPTION 4 - Warm_Up_Time
            Adjust_Setting(&Warm_Up_Time, WARM_UP_TIME_MIN, WARM_UP_TIME_MAX, "WARMUP T=");
            LCD_Set_Cursor(2,1);
            LCD_Word("=====SETTED=====");
            __delay_ms(2000);
            LCD_Data(0, 0x01);

            // OPTION 5 - Cool_Down_Time
            Adjust_Setting(&Cool_Down_Time, COOL_DOWN_TIME_MIN, COOL_DOWN_TIME_MAX, "COOLDOWN T=");
            LCD_Set_Cursor(2,1);
            LCD_Word("=====SETTED=====");
            __delay_ms(2000);
            LCD_Data(0, 0x01);
            
            // OPTION 6 - DG ON TIME
            Adjust_Setting(&Mains_Healthy, MAINS_HEALTHY_MIN, MAINS_HEALTHY_MAX, "MAINS HLTHY=");
            LCD_Set_Cursor(2,1);
            LCD_Word("=====SETTED=====");
            __delay_ms(2000);
            LCD_Data(0, 0x01);
            
            
//             Save to EEPROM [SECTION]]
             LCD_Set_Cursor(1,1);
            LCD_Word("EEPROM Saving...");
            EEPROM_WriteByte(0, Crank_Count);
            EEPROM_WriteByte(1, Crank_Sec);
            EEPROM_WriteByte(2, Crank_Interval);
            EEPROM_WriteByte(3, Warm_Up_Time);
            EEPROM_WriteByte(4, Cool_Down_Time);
            EEPROM_WriteByte(5, Mains_Healthy);
        }
}





void Adjust_Setting(uint8_t *value, uint8_t min, uint8_t max, const char *label)
{
    LCD_Data(0, 0x01);
    while(1)
    {
        
        LCD_Set_Cursor(1,1);
        LCD_Word(label);
        LCD_Display_2Digit(*value);
        LCD_Word("S");

        // Increment
        if (SW1 == PULLUP_ON)
        {
            __delay_ms(100);     // Debounce
            while(SW1 == PULLUP_ON);    // Wait for release
            if (*value < max) 
            {
                (*value)++; 
            }
               
        }

        // Decrement
        if (SW2 == PULLUP_ON)
        {
            __delay_ms(100);
            while(SW2 == PULLUP_ON);
            if (*value > min) 
            {
                (*value)--;
            }
        }

        // Next Option
        if (SW3 == PULLUP_ON)
        {
            __delay_ms(100);
            while(SW3 == PULLUP_ON);
            break;
        }
    }
}