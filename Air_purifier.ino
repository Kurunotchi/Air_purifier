/*
 * Automatic Air Purifier - ESP32
 * Fan: AVC Dual-Rotor 40x40x56mm (8-wire)
 * Trigger: Only when air is FATAL (PM2.5 > 150)
 * Features: Relay power cut + Soft Start / Soft Stop
 * 
 * Author: Electronics Design
 * Date  : November 2026
 */

#include <HardwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ================== PIN DEFINITIONS ==================
#define RELAY_PIN         19      // Controls 12V power via Relay
#define FAN_PWM_PIN       25      // PWM signal to Brown+White
#define BUTTON_PIN        0       // Manual force ON button

#define PMS_RX            16      // ESP32 RX  <- PMS TX
#define PMS_TX            17      // ESP32 TX  -> PMS RX

// OLED
#define SCREEN_WIDTH      128
#define SCREEN_HEIGHT     64
#define OLED_RESET        -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ================== SETTINGS ==================
const int PWM_CHANNEL     = 0;
const int PWM_FREQ        = 25000;    // 25 kHz - good for server fans
const int PWM_RESOLUTION  = 8;        // 0-255

const int FATAL_ON        = 150;      // Turn ON above this (µg/m³)
const int FATAL_OFF       = 100;      // Turn OFF below this (hysteresis)
const int RAMP_SPEED      = 3;        // Soft start/stop speed (2=slower, 5=faster)

// ================== VARIABLES ==================
HardwareSerial pmsSerial(2);

bool fanIsOn        = false;
bool forceOn        = false;
int  currentDuty    = 0;              // Current PWM value (0-255)
int  pm25           = 0;
unsigned long lastRead = 0;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n=== Automatic Air Purifier Starting ===");

  // Pins
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(RELAY_PIN, LOW);               // Ensure fan is OFF at boot

  // PWM Setup
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(FAN_PWM_PIN, PWM_CHANNEL);
  ledcWrite(PWM_CHANNEL, 0);

  // PMS5003 Serial
  pmsSerial.begin(9600, SERIAL_8N1, PMS_RX, PMS_TX);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found - continuing without display");
  } else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Air Purifier");
    display.println("System Ready");
    display.println("Waiting for");
    display.println("fatal air...");
    display.display();
  }

  Serial.println("System ready. Fan will activate only when PM2.5 > 150");
}

void loop() {
  // Manual force button
  if (digitalRead(BUTTON_PIN) == LOW) {
    forceOn = true;
    Serial.println("Manual FORCE ON activated");
    delay(300);   // simple debounce
  }

  // Read sensor every 2 seconds
  if (millis() - lastRead >= 2000) {
    lastRead = millis();
    readPMS();
    controlFan();
    updateDisplay();
  }
}

// ================== READ PMS5003 ==================
void readPMS() {
  if (pmsSerial.available() >= 32) {
    uint8_t buf[32];
    pmsSerial.readBytes(buf, 32);

    // Check header
    if (buf[0] == 0x42 && buf[1] == 0x4D) {
      // Atmospheric PM2.5 (standard)
      pm25 = (buf[12] << 8) | buf[13];
      Serial.printf("PM2.5 = %d ug/m3 | Duty = %d | Fan = %s\n",
                    pm25, currentDuty, fanIsOn ? "ON" : "OFF");
    }
  }
}

// ================== FAN CONTROL WITH SOFT START ==================
void controlFan() {
  bool shouldBeOn = forceOn || (pm25 > FATAL_ON) || (fanIsOn && pm25 > FATAL_OFF);

  if (shouldBeOn) {
    // ----- Turn power ON if needed -----
    if (!fanIsOn) {
      digitalWrite(RELAY_PIN, HIGH);          // Relay ON → 12V to fan
      delay(120);
      fanIsOn = true;
      Serial.println(">>> RELAY ON - Starting soft ramp");
    }

    // ----- Soft Start (Ramp Up) -----
    if (currentDuty < 255) {
      currentDuty += RAMP_SPEED;
      if (currentDuty > 255) currentDuty = 255;
      ledcWrite(PWM_CHANNEL, currentDuty);
    }
  }
  else {
    // ----- Soft Stop (Ramp Down) -----
    if (currentDuty > 0) {
      currentDuty -= RAMP_SPEED;
      if (currentDuty < 0) currentDuty = 0;
      ledcWrite(PWM_CHANNEL, currentDuty);
    }

    // ----- Fully power off -----
    if (currentDuty == 0 && fanIsOn) {
      delay(50);
      digitalWrite(RELAY_PIN, LOW);           // Cut 12V completely
      fanIsOn = false;
      forceOn = false;
      Serial.println(">>> RELAY OFF - Air is safe again");
    }
  }
}

// ================== OLED UPDATE ==================
void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.printf("PM2.5: %d ug/m3\n", pm25);
  display.printf("Duty : %d/255\n\n", currentDuty);

  display.setTextSize(2);
  if (fanIsOn) {
    display.println("FATAL");
    display.println("FAN ON");
  } else {
    display.println("SAFE");
    display.println("FAN OFF");
  }
  display.display();
}
