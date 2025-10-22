#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>
#include <stdbool.h>


// ===============================
// EEPROM ADDRESS MAP
// ===============================
#define ADDR_CRANK_COUNT      0x00
#define ADDR_CRANK_SEC        0x01
#define ADDR_CRANK_INTERVAL   0x02
#define ADDR_WARM_UP_TIME     0x03
#define ADDR_COOL_DOWN_TIME   0x04
#define ADDR_MAINS_HELATHY    0x05


// Default values for a fresh program [DEFAULT VLAUE SETTINGS PURPOSE]
#define DEF_CRANK_COUNT       3
#define DEF_CRANK_SEC         3
#define DEF_CRANK_INTERVAL    10
#define DEF_WARM_UP_TIME      6
#define DEF_COOL_DOWN_TIME    8
#define DEF_MAINS_HELATHY     9



void EEPROM_WriteByte(unsigned char addr, unsigned char value);
unsigned char EEPROM_ReadByte(unsigned char addr);

// Loader for default or saved temperature
uint8_t EEPROM_ReadOrDefault(uint8_t address, uint8_t defaultValue);
void LoadAllSettings(uint8_t *Crank_Count, uint8_t *Crank_Sec, uint8_t *Crank_Interval,
                     uint8_t *Warm_Up_Time, uint8_t *Cool_Down_Time, uint8_t *Mains_Healthy);


#endif
