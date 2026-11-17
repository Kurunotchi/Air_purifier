# Bill of Materials (BOM)
## Automatic Air Purifier – ESP32 Version

| No. | Component                        | Specification / Model                      | Qty | Unit   | Notes / Remarks                                      |
|-----|----------------------------------|--------------------------------------------|-----|--------|------------------------------------------------------|
| 1   | Microcontroller                  | ESP32 DevKit (ESP32-WROOM-32)              | 1   | pcs    | Any ESP32 Dev Module                                 |
| 2   | Cooling Fan                      | AVC DFPD0456B2U / DF0456B12U / DFTA0456B2H | 1   | pcs    | 40×40×56 mm, 12V, 8-wire dual rotor                  |
| 3   | Relay Module                     | 5V Single Channel Relay Module             | 1   | pcs    | With optocoupler preferred, 10A contact rating       |
| 4   | Air Quality Sensor               | PMS5003 or PMS7003                         | 1   | pcs    | Laser PM2.5 sensor                                   |
| 5   | Power Supply                     | 12V 5A Switching Adapter                   | 1   | pcs    | Minimum 5A, preferably 6A                            |
| 6   | Fuse                             | 5A Fast Blow (or Blade fuse)               | 1   | pcs    | Inline with 12V                                      |
| 7   | Capacitor                        | 1000µF – 2200µF / 25V Electrolytic         | 1   | pcs    | Near fan power terminals                             |
| 8   | Capacitor                        | 100nF Ceramic                              | 1   | pcs    | Parallel with electrolytic                           |
| 9   | Pull-up Resistor                 | 10kΩ 1/4W                                  | 2   | pcs    | For tach signals (optional)                          |
| 10  | Push Button                      | Momentary Tactile Switch                   | 1   | pcs    | Manual force ON (optional)                           |
| 11  | OLED Display                     | 0.96" or 1.3" SSD1306 I2C                  | 1   | pcs    | Optional but recommended                             |
| 12  | Jumper Wires / Dupont            | Male-Female & Male-Male                    | 20  | pcs    | Assorted                                             |
| 13  | Breadboard or PCB                | Half-size breadboard or custom PCB         | 1   | pcs    | For prototyping                                      |
| 14  | Screw Terminals                  | 2-pin / 3-pin                              | 2   | pcs    | For 12V and fan connections (optional)               |
| 15  | Heat Shrink / Electrical Tape    | -                                          | -   | -      | For insulation                                       |
| 16  | Enclosure                        | Project box                                | 1   | pcs    | Optional                                             |

### Optional / Nice to Have

| No. | Component                | Specification              | Qty | Notes                     |
|-----|--------------------------|----------------------------|-----|---------------------------|
| 17  | Status LED               | 5mm LED + 220Ω resistor    | 1–2 | Fan status indicator      |
| 18  | Buzzer                   | Active 5V buzzer           | 1   | Alarm on fatal air        |
| 19  | DC Jack                  | 5.5×2.1 mm                 | 1   | For power input           |

---

**Total estimated cost (approximate, without fan):** $25 – $40 USD  
**Fan cost:** Varies ($8 – $25 depending on condition)  
