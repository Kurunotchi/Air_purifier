# System Flowchart
## Automatic Air Purifier – ESP32 + Relay + Soft Start

```
                        +-------------------+
                        |      START        |
                        +---------+---------+
                                  |
                                  v
                        +-------------------+
                        | Initialize ESP32  |
                        | Relay OFF         |
                        | PWM = 0           |
                        | Sensor ready      |
                        +---------+---------+
                                  |
                                  v
                     +------------------------+
                     |      MAIN LOOP         |
                     +-----------+------------+
                                 |
               +-----------------+-----------------+
               |                                   |
               v                                   v
    +-------------------+               +-------------------+
    | Button pressed?   |               | Time to read      |
    |                   |               | sensor? (2 sec)   |
    +--------+----------+               +--------+----------+
             | Yes                               | Yes
             v                                   v
    +-------------------+               +-------------------+
    | forceOn = TRUE    |               | Read PM2.5        |
    +-------------------+               +--------+----------+
                                                 |
                                                 v
                                        +-------------------+
                                        | ControlFan()      |
                                        +--------+----------+
                                                 |
                         +-----------------------+-----------------------+
                         |                                               |
                         v                                               v
              +---------------------+                         +----------------------+
              | shouldBeOn = TRUE?  |                         | shouldBeOn = FALSE?  |
              | (PM2.5 > 150 or     |                         |                      |
              |  forceOn or         |                         |                      |
              |  hysteresis)        |                         |                      |
              +----------+----------+                         +----------+-----------+
                         | Yes                                          | Yes
                         v                                               v
              +---------------------+                         +----------------------+
              | Relay already ON?   |                         | currentDuty > 0 ?    |
              +----------+----------+                         +----------+-----------+
                   | No         | Yes                                  | Yes
                   v            |                                      v
         +------------------+   |                           +----------------------+
         | Turn Relay ON    |   |                           | Decrease currentDuty |
         | Wait 120ms       |   |                           | Write new PWM        |
         | fanIsOn = TRUE   |   |                           +----------+-----------+
         +--------+---------+   |                                      |
                  |             |                                      v
                  +------+------+                           +----------------------+
                         |                                  | currentDuty == 0 ?   |
                         v                                  +----------+-----------+
              +---------------------+                                | Yes
              | currentDuty < 255?  |                                v
              +----------+----------+                     +----------------------+
                   | Yes                                 | Turn Relay OFF       |
                   v                                     | fanIsOn = FALSE      |
         +----------------------+                        | forceOn = FALSE      |
         | Increase currentDuty |                        +----------------------+
         | Write PWM            |
         +----------------------+
                         |
                         v
              +---------------------+
              | Update OLED         |
              | (PM2.5 + Status)    |
              +----------+----------+
                         |
                         v
              +---------------------+
              |   Return to Loop    |
              +---------------------+
```

### Decision Summary

- **Turn Fan ON** when: PM2.5 > 150 **or** Manual button pressed
- **Keep Fan ON** while: PM2.5 > 100 (hysteresis)
- **Turn Fan OFF** when: PM2.5 < 100 **and** not forced
- Speed always changes gradually (soft start / soft stop)  
