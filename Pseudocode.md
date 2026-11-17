# Pseudocode
## Automatic Air Purifier – ESP32

```
INITIALIZE
    Set Relay Pin as OUTPUT → OFF
    Set PWM Pin (25 kHz, 8-bit)
    Set Button Pin as INPUT_PULLUP
    Initialize PMS5003 Serial (9600 baud)
    Initialize OLED (optional)
    currentDuty = 0
    fanIsOn = FALSE
    forceOn = FALSE
    FATAL_ON  = 150
    FATAL_OFF = 100
    RAMP_SPEED = 3

LOOP forever

    // Manual override
    IF Button is pressed THEN
        forceOn = TRUE

    // Read sensor every 2 seconds
    IF time since last reading > 2000 ms THEN
        Read PM2.5 from PMS5003
        Update display
        Call ControlFan()

    END IF

END LOOP


FUNCTION ControlFan()

    shouldBeOn = forceOn OR (PM2.5 > FATAL_ON) OR (fanIsOn AND PM2.5 > FATAL_OFF)

    IF shouldBeOn is TRUE THEN

        IF fanIsOn is FALSE THEN
            Turn Relay ON
            Wait 120 ms
            fanIsOn = TRUE
            Print "Fan Starting - Soft Ramp"

        END IF

        // Soft Start (Ramp Up)
        IF currentDuty < 255 THEN
            currentDuty = currentDuty + RAMP_SPEED
            IF currentDuty > 255 THEN currentDuty = 255
            Write PWM = currentDuty
        END IF

    ELSE
        // Soft Stop (Ramp Down)
        IF currentDuty > 0 THEN
            currentDuty = currentDuty - RAMP_SPEED
            IF currentDuty < 0 THEN currentDuty = 0
            Write PWM = currentDuty
        END IF

        // Fully stop
        IF currentDuty == 0 AND fanIsOn is TRUE THEN
            Wait 50 ms
            Turn Relay OFF
            fanIsOn = FALSE
            forceOn = FALSE
            Print "Fan OFF - Air is safe"
        END IF

    END IF

END FUNCTION
```  
