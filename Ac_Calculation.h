#ifndef Ac_Calculation
#define Ac_Calculation

#define SAMPLES 150

//FROM MAIN.C
extern bool Normal_State;





extern const uint8_t ADC_Order_EB[3],ADC_Order_DG[3];

extern uint16_t voltage_EB[3],voltage_DG[3];

extern uint16_t adc_value_EB[3],adc_value_DG[3];

extern uint16_t vmax_EB,vmax_DG,sample_EB,sample_DG;

//=========================================================================
//FOR USER FRIEDNLY PURPOSE ASSIGNING THE VOLTAGE ARRAY INTO RESPECTIVE NAME
//=========================================================================
#define EB_R    voltage_EB[0]
#define EB_Y    voltage_EB[1]
#define EB_B    voltage_EB[2]
#define DG_R    voltage_DG[0]
#define DG_Y    voltage_DG[1]
#define DG_B    voltage_DG[2]


//=========================================================================
//PHASE VOLTAGE MINIMUM LIMIT
//=========================================================================
#define EB_R_Limit    207
#define EB_Y_Limit    207
#define EB_B_Limit    207
#define DG_R_Limit    207
#define DG_Y_Limit    207
#define DG_B_Limit    207






int Convert_To_Voltage_Int(unsigned int adc_value);
void Ac_Calculation_Value(int mode ,uint8_t display);



#endif
