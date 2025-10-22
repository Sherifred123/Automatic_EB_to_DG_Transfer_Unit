//Timer.C
#include <xc.h>

//===================== CREATED HEADER FILES  =====================================
#include "main.h"
#include "SystemConfig.h"
#include "Timer.h"
#include "Lcd.h"
#include "Ac_Calculation.h"
#include "EEPROM.h"










volatile int tmr1_counter = 0;
volatile bool one_sec_flag = false;
volatile int countdown_timer = 0;// 180s countdown

void Timer1_Init(int state)
{
    if(state==ON)
    {
        
        TMR1 = 3036;
        T1CON = 0x31;
        TMR1IF = 0;
        TMR1IE = 1;
        PEIE=1;
    }
    else if(state==OFF)
    {
        countdown_timer=0;
        TMR1 = 0;
        T1CON = 0x00;
        TMR1IF = 0;
        TMR1IE = 0;
        PEIE=0;
    }
        GIE=1;
}

// ISR
void __interrupt() ISR(void)
{
    if (TMR1IF)   // Timer1 overflow flag?
    {
        TMR1IF = 0;   // Clear flag
        TMR1 = 3036;  // Reload for 100ms

        tmr1_counter++;
        if (tmr1_counter >= 10)   // 10 × 100ms = 1s
        {

            tmr1_counter = 0;
            one_sec_flag = true;
            
        
        }
    }
}

bool Timer1_Has1SecElapsed(void)
{  
        if (one_sec_flag)
    {
           
        one_sec_flag = false;   // clear flag
        return true;            // tell main that 1 second has passed
    }
    return false;
}





