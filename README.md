# Automatic Air Purifier - ESP32 + AVC Dual-Rotor Fan

**Version:** 1.0  
**Date:** November 2026  
**Author:** Kurunotchi  

## Project Description

This is an automatic air purifier controller based on ESP32.  
The system keeps the powerful AVC 40×40×56 mm counter-rotating fan completely OFF under normal conditions.  
When air quality becomes **fatal** (PM2.5 > 150 µg/m³), the fan turns ON with a smooth soft-start and runs at full speed.  
When air quality improves (PM2.5 < 100 µg/m³), the fan smoothly decelerates and fully powers off via relay.

### Key Features
- Fan remains completely powered off during safe air conditions
- Activates only at hazardous/fatal PM2.5 levels
- Soft-start and soft-stop (no sudden full speed)
- Relay cuts 12V power completely when not needed
- Hysteresis to prevent rapid on/off cycling
- Optional manual force-on button
- Optional OLED status display
- Uses PMS5003 laser particle sensor

---

## Hardware Overview

- **Controller:** ESP32 DevKit
- **Fan:** AVC DFPD0456B2U / DF0456B12U / DFTA0456B2H (40×40×56 mm, 12V, 8-wire dual rotor)
- **Power Switching:** 5V Relay Module
- **Sensor:** PMS5003 / PMS7003
- **Power Supply:** 12V 5A (or higher)

---

## Thresholds

| Condition              | PM2.5 Value     | Action                  |
|------------------------|-----------------|-------------------------|
| Safe / Normal          | < 100 µg/m³     | Fan OFF                 |
| Fatal / Hazardous      | > 150 µg/m³     | Fan ON (soft start)     |
| Hysteresis zone        | 100 – 150 µg/m³ | Keeps current state     |

---

## File Structure

```
AirPurifier_ESP32/
├── README.md
├── BOM.md
├── BOQ.md
├── Pseudocode.md
├── Flowchart.md
└── AirPurifier_ESP32.ino
```

---

## Quick Start

1. Assemble hardware according to the wiring in `BOM.md` / `README.md`
2. Install required libraries in Arduino IDE
3. Upload `AirPurifier_ESP32.ino`
4. Open Serial Monitor (115200 baud)

---

## Libraries Required

- Adafruit SSD1306
- Adafruit GFX Library

(Install via Arduino Library Manager)

---

## License

This project is provided as-is for personal and educational use.  
