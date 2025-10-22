⚙️ EB–DG Automatic Power Controller
Smart Embedded Solution for Reliable Power Switching
🧩 Project Overview

This project is an embedded power management system designed to automatically switch between Electric Board (EB) and Diesel Generator (DG) power sources based on real-time voltage conditions.
It provides continuous monitoring of all three AC phases and battery voltage measurement, ensuring uninterrupted power delivery for critical loads.

🔋 Key Functionalities

⚡ Automatic EB ↔ DG Changeover based on voltage status

📊 Three-Phase AC Voltage Measurement (R, Y, B)

🔋 Battery Voltage Monitoring using ADC with precision divider

🧮 RMS Voltage Calculation and display on 16x2 LCD

🔄 Real-Time Status Indication for both EB and DG

🔌 Microcontroller-Controlled Relay Switching for stable changeover

🧰 Hardware and Software Details
Component	Description
Microcontroller	PIC16F887
Programming Tool	MPLAB SNAP (ICSP Interface)
Compiler	XC8
IDE	MPLAB X IDE
Display	16x2 LCD
Voltage Divider	R1 = 220kΩ, R2 = 33kΩ (Battery ADC Input)
Power Supply	5V regulated DC
Language	Embedded C
🧩 Project File Structure
📁 EB_DG_Controller
 ├── main.c                → Main control logic
 ├── Ac_Calculation.c      → AC phase sampling & RMS conversion
 ├── Battery_Value.c       → Battery voltage measurement
 ├── Lcd.h / Lcd.c         → LCD interface driver
 ├── Timer.h / Timer.c     → Timers and delays
 ├── SystemConfig.h        → MCU configuration bits
 └── EEPROM.h / EEPROM.c   → Parameter storage and retrieval

🧠 Technical Insight

AC voltages are sampled using ADC channels and converted to RMS values through peak detection.

The voltage thresholds determine whether EB or DG power is active.

A voltage divider scales the battery voltage for ADC range safety (5V reference).

The LCD module continuously displays real-time voltage readings and system states.

🚀 Future Enhancements

Add overload protection and current monitoring.

Integrate Wi-Fi module (ESP8266) for remote voltage viewing.

Include data logging via EEPROM or SD card.

Develop mobile dashboard for real-time status updates.
