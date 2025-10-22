# ⚙️ EB–DG Automatic Power Controller  
### Smart Embedded Solution for Reliable Power Switching  

---

## 🧩 Project Overview  

This project is an **embedded power management system** designed to automatically switch between **Electric Board (EB)** and **Diesel Generator (DG)** power sources based on real-time voltage conditions.  

It provides **continuous monitoring of all three AC phases** and **battery voltage sensing**, ensuring uninterrupted power delivery for critical loads.

---

## 🔋 Key Functionalities  

- ⚡ **Automatic EB ↔ DG Changeover** based on voltage status  
- 📊 **Three-Phase AC Voltage Measurement** (R, Y, B)  
- 🔋 **Battery Voltage Monitoring** using ADC with precision divider  
- 🧮 **RMS Voltage Calculation** and display on 16×2 LCD  
- 🔄 **Real-Time Status Indication** for both EB and DG  
- 🔌 **Relay-Controlled Power Switching** for safe and stable changeover  

---

## 🧰 Hardware and Software Details  

| Component | Description |
|------------|-------------|
| **Microcontroller** | Embedded Controller (8-bit MCU) |
| **Programming Tool** | MPLAB SNAP (ICSP Interface) |
| **Compiler** | XC8 |
| **IDE** | MPLAB X IDE |
| **Display** | 16×2 LCD |
| **Voltage Divider** | R1 = 220 kΩ, R2 = 33 kΩ (Battery ADC Input) |
| **Power Supply** | 5 V regulated DC |
| **Language** | Embedded C |

---

## 📁 Project File Structure  



📁 EB_DG_Controller
├── main.c → Main control logic
├── Ac_Calculation.c → AC phase sampling & RMS conversion
├── Battery_Value.c → Battery voltage measurement
├── Lcd.h / Lcd.c → LCD interface driver
├── Timer.h / Timer.c → Timers and delays
├── SystemConfig.h → System configuration bits
└── EEPROM.h / EEPROM.c → Parameter storage and retrieval


---

## 🧠 Technical Insight  

- AC voltages are **sampled via ADC channels** and converted to RMS values using peak detection.  
- Voltage thresholds determine whether **EB** or **DG** power is active.  
- A **voltage divider** safely scales the battery voltage within the ADC’s 5 V reference limit.  
- The **LCD module** continuously displays real-time voltage readings and power-source status.  

---

## 🚀 Future Enhancements  

- ⚙️ Add overload protection and current monitoring  
- 🌐 Integrate Wi-Fi (ESP8266) for remote monitoring  
- 💾 Include data logging via EEPROM or SD Card  
- 📱 Develop a mobile dashboard for live system updates  

---

### 🏁 Summary  

An intelligent, reliable, and scalable **embedded power controller** solution that automates EB–DG changeover and continuously supervises voltage conditions to ensure seamless power continuity.

---

**Developed with:** 🛠️ *MPLAB X IDE | XC8 Compiler | Embedded C*
