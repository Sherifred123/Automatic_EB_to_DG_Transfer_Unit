//MAIN.C

#include <xc.h>

#include "main.h"
#include "SystemConfig.h"
#include "Timer.h"
#include "Lcd.h"
#include "Ac_Calculation.h"
#include "EEPROM.h"

//  LoadAllSettings(&Crank_Count, &Crank_Sec, &Crank_Interval, &Warm_Up_Time, &Cool_Down_Time, &Mains_Healthy);

uint8_t Set,Crank_Count,Crank_Sec,Crank_Interval,Warm_Up_Time,Cool_Down_Time,Mains_Healthy;

uint8_t EB_Phase_Low_Count=0,DG_Phase_Low_Count=0,
        Crank_Relay_Chance_Check=0,Crank_Sec_Check=0,
        Crank_Interval_Check=0,EB_Ontime_Check=0,DG_Ontime_Check=0;;
extern bool  Generator_State,Eb_State;
bool inital_check=false,EB_Fail_State=false,Normal_State=true,Remaining_Chance_DG=true,Generator_Stable=false;

void main(void)
{
    
    System_Initialize();
    LCD_Intial();
    Timer1_Init(ON);
    ADC_Intial();
//    
   
    LoadAllSettings(&Crank_Count, &Crank_Sec, &Crank_Interval, &Warm_Up_Time, &Cool_Down_Time, &Mains_Healthy);
    LCD_Data(0, 0x01);

 //    //temp purpose
////    EB_Fail_State= true,Normal_State=false,inital_check=true;
    

    while(1)
    {
      
        if(Normal_State == true)
        {
//#define EB              6
//#define DG              3
            if(Timer1_Has1SecElapsed() )
            {  
               Ac_Calculation_Value(EB , DISPLAY);
               Ac_Calculation_Value(DG , DISPLAY);
               Battery_Value();//BATTERY VOLTAGE DISPLAY PURPOSE
               inital_check=true;//To avoid the reaching to alarm first purpose

            } 
        }
        
        
//        if(1==0)//TEMP PURPOSE ALONE
//        {
//            
//        }
        
        
        else if(Generator_Stable == false)
        {
                if(Eb_State == false  && inital_check == true)//EB to Generator switching
                {
                    EB_Fail_State=true;
                    if(Eb_State == false)
                    {
                        LCD_Data(0, 0x01);
                        LCD_Set_Cursor(1,1);
                        LCD_Word("Mains Unhealthy");
                        __delay_ms(1000);
                        LATCH_RLY=ON;//TO ON THE FUEL PURPOSE
                    }

                    //chances remaining=3
                    while(Crank_Relay_Chance_Check < Crank_Count  && EB_Fail_State == true)
                    {
                                LCD_Set_Cursor(2,1);
                                LCD_Word("                 ");
                                Crank_Relay_Chance_Check++;
                                //CHECKING PURPOSE ALONE
//                                LCD_Set_Cursor(2,1);
//                                LCD_Word("CH=");
//                                LCD_Display_2Digit(Crank_Relay_Chance_Check);
//                                LCD_Set_Cursor(2,1);

                                //CRANK ON DURATION [NO SECOND CRANK RELAY NEED TO BE ON=3]
                                while(Crank_Sec_Check < Crank_Sec)
                                {
                                    Ac_Calculation_Value(DG , NO_DISPLAY);               
                                    Crank_Sec_Check++;
                                    CRANK_RLY=ON;
                                    LCD_Set_Cursor(1,1);
                                    LCD_Word("Cranking ON");
//                                    LCD_Set_Cursor(2,8);
//                                    LCD_Word("C=");
//                                    LCD_Display_2Digit(Crank_Sec_Check);
                                    LCD_Set_Cursor(2,1);
                                    
                                    __delay_ms(1000); 

                                }Crank_Sec_Check=RESET_VALUE;
                                CRANK_RLY=OFF;
                                LCD_Set_Cursor(2,1);
                                LCD_Word("                 ");
                                
                                //CRANK NEXT CYCLE ON INTERVAL =10 
                                
                                uint8_t stable_count=0;//FOR GENRATOR STABLE COUNT
                                while(Crank_Interval_Check < Crank_Interval && EB_Fail_State == true )
                                {
                                    
                                    Crank_Interval_Check++; 
//                                    Ac_Calculation_Value(DG , NO_DISPLAY);
        

                                           RC2=0;RC3=1;
                                         __delay_ms(1000);
                                            
                                            LCD_Set_Cursor(2,1);
                                            LCD_Word("int=");
                                            LCD_Display_2Digit(Crank_Interval_Check);

                                    
                                    if(stable_count == 5)
                                    {
                                        LCD_Set_Cursor(2,1);
                                        LCD_Word("                    ");
                                        LCD_Word("GEN VOLTAGE OK");
                                        Generator_Stable=true;
                                        break;
                                    }
                                    else if(Generator_State == true && Eb_State == false)
                                    {
                                        stable_count++;
                                        RC3=0;RC2=1;
                                        
                                        EB_Fail_State=false;
                                        LCD_Set_Cursor(2,1);
                                        LCD_Word(" ");   
                                    }

                                }Crank_Interval_Check=stable_count=RESET_VALUE;
                                LCD_Set_Cursor(2,1);
                                LCD_Word("                 ");
                                
 
                                
                                
                        }Crank_Relay_Chance_Check=RESET_VALUE;
                          
                }
        
        }
//        else if(Generator_Stable == true)
//        {
//            
//            while(EB_Ontime_Check < EB_Ontime)
//            {
//                        EB_Ontime_Check++;
//                        LCD_Data(0, 0x01);
//                        LCD_Set_Cursor(1,1);
//                        LCD_Word("EB FAILS");
//                        LCD_Set_Cursor(2,1);
//                        LCD_Word("DG ON TIME=");
//                        LCD_Display_2Digit(EB_Ontime_Check);
//                        __delay_ms(1000);
//                        
//            }
//        }
//        
        Setting_Parameter();
        
          
//            LCD_Display_3Digit();
        
//                }
//        }
    }
    return;
}


void Battery_Value()
{
    uint16_t adc = ADC_Read(0);
    float Result = ((adc * 5.0) / 1023.0) * 7.67;
    uint16_t Bat_Volt = (uint16_t)(Result * 100);

    LCD_Data(0, 0x01);
//    LCD_Set_Cursor(1,1);
//    LCD_Word("ADC=");
//    LCD_Display_4Digit(adc);

    LCD_Set_Cursor(2,1);
    LCD_Word("BAT Volt=");
    LCD_Data(1, ((Bat_Volt / 1000) % 10) + '0');
    LCD_Data(1, ((Bat_Volt / 100) % 10) + '0');
    LCD_Data(1, '.');
    LCD_Data(1, ((Bat_Volt / 10) % 10) + '0');
    LCD_Data(1, (Bat_Volt % 10) + '0');
    LCD_Data(1,'V');
    __delay_ms(3000);
}









/*
 without float
 * RAM=22%
 * PROGRAM [FLASH]=15%
 
 WITH FLOAT
 * RAM=39%
 * PROGRAM [FLASH]=46%
 * 
 * DIFF
 * RAM=17
 * PROGRAM [FLASH]=31%
 
 */

