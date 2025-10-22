#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H

#include <stdint.h>

#define _XTAL_FREQ 20000000

// CONFIGURATION BITS
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config CP = ON
#pragma config CPD = ON
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF

// MACROS
#define ON              1
#define OFF             0
#define PULLUP_ON       0
#define PULLUP_OFF      1
#define RESET_VALUE     0
#define SW1             RA1
#define SW2             RA2
#define SW3             RA3
#define SW4             RA4
#define LATCH_RLY       RC0
#define CRANK_RLY       RC1
#define OPTION_1        0
#define OPTION_2        1
#define OPTION_3        2
#define OPTION_4        3
#define OPTION_5        4
#define EB              6
#define DG              3
#define DISPLAY         1
#define NO_DISPLAY      0


// ===============================
// SETTINGS LIMITS (DEFINE AS MACROS)
// ===============================
#define CRANK_COUNT_MIN      1
#define CRANK_COUNT_MAX      20

#define CRANK_SEC_MIN        1
#define CRANK_SEC_MAX        20

#define CRANK_INTERVAL_MIN   1
#define CRANK_INTERVAL_MAX   20

#define WARM_UP_TIME_MIN     1
#define WARM_UP_TIME_MAX     20

#define COOL_DOWN_TIME_MIN   1
#define COOL_DOWN_TIME_MAX   20

#define MAINS_HEALTHY_MIN    1
#define MAINS_HEALTHY_MAX   20


//#define Phase_Offset_Limit   3






// FUNCTION DECLARATIONS
void System_Initialize(void);
void ADC_Intial(void);
unsigned int ADC_Read(unsigned char channel);

void Setting_Parameter();
void Adjust_Setting(uint8_t *value, uint8_t min, uint8_t max, const char *label);

#endif
