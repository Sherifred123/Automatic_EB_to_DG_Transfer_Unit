
//Ac_Calculation.C

#include <xc.h>
#include "main.h"
#include "SystemConfig.h"
#include "Timer.h"
#include "Lcd.h"
#include "Ac_Calculation.h"
#include "EEPROM.h"



/*
 * BATTERY = AN0
 * PHASE   = AN12,AN10,AN8,AN9,AN11,AN13
 */
const uint8_t ADC_Order_EB[3]={13,11,9},ADC_Order_DG[3]={8,10,12};

uint16_t voltage_EB[3]={0,0,0},voltage_DG[3]={0,0,0};

uint16_t adc_value_EB[3]={0,0,0},adc_value_DG[3]={0,0,0};

uint16_t vmax_EB=0,vmax_DG=0,sample_EB=0,sample_DG=0;

bool  Generator_State=false,Eb_State=false;


 int  Convert_To_Voltage(unsigned int adc_value)
{
//    int v_peak =(int) ((adc_value * 5.0 / 1023.0) * 177.25); 
//    return (int)((v_peak / 1.414)); // convert to RMS
     
    float v_adc = (adc_value * 5.0) / 1023.0;    
    float v_peak = v_adc * 223.76595744680851063829787234043;                
    float v_rms = v_peak / 1.414;                
    return (int)(v_rms);                         
}

void Ac_Calculation_Value(int mode ,uint8_t display)
{
    if(mode == EB )
    {
        
        
        for (uint8_t ch = 0; ch < 3 ;ch++)
        {
            vmax_EB = sample_EB=0;//reset purpose
            
           sample_EB = ADC_Read( ADC_Order_EB[ch]);
           __delay_ms(2);
     
            for (uint8_t s = 0; s < SAMPLES; s++)
            {
                sample_EB = ADC_Read(ADC_Order_EB[ch]);
                if (sample_EB > vmax_EB)
                    vmax_EB = sample_EB;
                    
                __delay_us(200); // Sampling for 50Hz waveform
            }
           
             if (vmax_EB < 10)
             {
               vmax_EB = 0;  
             }
                          
            adc_value_EB[ch] = vmax_EB;
            voltage_EB[ch] = Convert_To_Voltage(vmax_EB);
        }
            if(display ==  DISPLAY)
            {
                // Display results
                LCD_Data(0, 0x01);
                LCD_Set_Cursor(1,1);
                LCD_Word("EB CH  "); 
//                LCD_Word("CH:");
//                LCD_Data(1, (ch % 10) + '0');


//ADC_Order_EB[3]={13,11,9}
                    LCD_Set_Cursor(1,11);
                    LCD_Word("R=");
                    LCD_Display_3Digit( voltage_EB[0]);
                    LCD_Word("V");
                    
                    LCD_Set_Cursor(2,1);
                    LCD_Word("Y=");
                    LCD_Display_3Digit( voltage_EB[1]);
                    LCD_Word("V");

                    LCD_Set_Cursor(2,11);
                    LCD_Word("B=");
                    LCD_Display_3Digit( voltage_EB[2]);
                    LCD_Word("V");

     
              

                 
                 __delay_ms(3000);
            }
 
        

        
//============================================
//EB FAIL [EB TO DG CHANGE OVER PURPOSE]]
//============================================      
        if(EB_R >= EB_R_Limit && EB_Y >= EB_Y_Limit && EB_B >= EB_B_Limit)
        {
           Eb_State= true; 
        }
        else
        {
           Eb_State= false; 
           Normal_State=false;
        } 
    }
    
    else if(mode == DG)
    {
       
        
       for (uint8_t ch = 0; ch < 3 ;ch++)
        {
            vmax_DG = sample_DG=0;//reset purpose
            
           sample_DG = ADC_Read( ADC_Order_DG[ch]);
           __delay_ms(2);
     
            for (uint8_t s = 0; s < SAMPLES; s++)
            {
                sample_DG = ADC_Read(ADC_Order_DG[ch]);
                if (sample_DG > vmax_DG)
                    vmax_DG = sample_DG;
                    
                __delay_us(200); // Sampling for 50Hz waveform
            }
           
             if (vmax_DG < 10)
             {
               vmax_DG = 0;  
             }
                          
            adc_value_DG[ch] = vmax_DG;
            voltage_DG[ch] = Convert_To_Voltage(vmax_DG);
       }
            if(display ==  DISPLAY)
            {
              LCD_Data(0, 0x01);
                LCD_Set_Cursor(1,1);
                LCD_Word("DG CH  "); 
//                LCD_Word("CH:");
//                LCD_Data(1, (ch % 10) + '0');


//DISPLAYING SESSION
//ADC_Order_DG[3]={8,10,12}
                    LCD_Set_Cursor(1,11);
                    LCD_Word("R=");
                    LCD_Display_3Digit( voltage_DG[0]);
                    LCD_Word("V");
                    
                    LCD_Set_Cursor(2,1);
                    LCD_Word("Y=");
                    LCD_Display_3Digit( voltage_DG[1]);
                    LCD_Word("V");

                    LCD_Set_Cursor(2,11);
                    LCD_Word("B=");
                    LCD_Display_3Digit( voltage_DG[2]);
                    LCD_Word("V");
                    __delay_ms(3000);  
            }
               
            
//============================================
//GENRATOR STATE FINDING PURPOSE
//============================================
        if(DG_R >= DG_R_Limit && DG_Y >= DG_Y_Limit && DG_B >= DG_B_Limit)
        {
           Generator_State= true; 
        }
        else
        {
           Generator_State= false; 
//           Normal_State=false;
        }
           
        
        
   
    }
           
    
}

