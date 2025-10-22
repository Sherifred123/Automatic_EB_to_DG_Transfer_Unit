//EEPROM.C

#include <xc.h>


//===================== CREATED HEADER FILES  =====================================
#include "main.h"
#include "SystemConfig.h"
#include "Timer.h"
#include "Lcd.h"
#include "Ac_Calculation.h"
#include "EEPROM.h"


//===================== BYTE READ/WRITE =======================

void EEPROM_WriteByte(unsigned char addr, unsigned char value)
{
    EEADR = addr;
    EEDATA = value;
    WREN = 1;

    // Unlock sequence
    GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    WR = 1;
    GIE = 1;

    while(WR);
    WREN = 0;
}

unsigned char EEPROM_ReadByte(unsigned char addr)
{
    EEADR = addr;
    RD = 1;
    return EEDATA;
}


uint8_t EEPROM_ReadOrDefault(uint8_t address, uint8_t defaultValue)
{
    uint8_t value = EEPROM_ReadByte(address);
    if (value == 0xFF) {
        EEPROM_WriteByte(address, defaultValue);
        return defaultValue;
    }
    return value;
}

void LoadAllSettings(uint8_t *Crank_Count, uint8_t *Crank_Sec, uint8_t *Crank_Interval,
                     uint8_t *Warm_Up_Time, uint8_t *Cool_Down_Time, uint8_t *Mains_Healthy)
{
    *Crank_Count    = EEPROM_ReadOrDefault(ADDR_CRANK_COUNT, DEF_CRANK_COUNT);
    *Crank_Sec      = EEPROM_ReadOrDefault(ADDR_CRANK_SEC, DEF_CRANK_SEC);
    *Crank_Interval = EEPROM_ReadOrDefault(ADDR_CRANK_INTERVAL, DEF_CRANK_INTERVAL);
    *Warm_Up_Time   = EEPROM_ReadOrDefault(ADDR_WARM_UP_TIME, DEF_WARM_UP_TIME);
    *Cool_Down_Time = EEPROM_ReadOrDefault(ADDR_COOL_DOWN_TIME, DEF_COOL_DOWN_TIME);
    *Mains_Healthy  = EEPROM_ReadOrDefault(ADDR_MAINS_HELATHY, DEF_MAINS_HELATHY);
}

