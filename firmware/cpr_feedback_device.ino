/*
----------------------------------------------------
CPR Feedback Device Firmware
  Board : Arduino Uno R4 Minima
  Sensor  : LM393 IR Sensor (detects each compression)
  Display : 16x2 LCD with I2C backpack
  Motor   : 12V DC Reciprocating Motor via BTS7960 driver

Features
- Adult Mode
- Compression Rate Monitoring
- LCD Feedback
- LED Feedback
- Emergency Stop
- BTS7960 Motor Control

Version : 1.0
----------------------------------------------------
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---- LCD ----
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---- Pins ----
#define IR_PIN        2
#define BTN_ADULT     3
#define BTN_STOP      5
#define LED_GREEN     6
#define LED_YELLOW    7
#define LED_RED       8
#define MOTOR_RPWM    9
#define MOTOR_LPWM    10
#define MOTOR_R_EN    11
#define MOTOR_L_EN    12

// ---- CPR Rate Targets ----
const int RATE_MIN = 120;
const int RATE_MAX = 140;

// ---- Motor Speed ----
const int MOTOR_SPEED_ADULT = 220;

// ---- Rate measurement window ----
const unsigned long RATE_WINDOW_MS = 3000;

// ---- Mode ----
int currentMode = 0;

// ---- Emergency Stop flag ----
bool emergencyStopped = false;

// ---- Compression counting ----
volatile int compressionCount = 0;
unsigned long lastCountTime = 0;
int currentRate = 0;

// ---- IR sensor interrupt ----
void countCompression() {
  compressionCount++;
}

// ---- Turn off all LEDs ----
void allLedsOff() {
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
}

// ---- Stop the motor ----
void stopMotor() {
  analogWrite(MOTOR_RPWM, 0);
  analogWrite(MOTOR_LPWM, 0);
}

// ---- Run the motor at given speed ----
void runMotor(int speed) {
  analogWrite(MOTOR_RPWM, speed);
  analogWrite(MOTOR_LPWM, 0);
}

// ---- Show welcome screen ----
void showWelcome() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  CPR  Device  ");
  lcd.setCursor(0, 1);
  lcd.print("Select Mode...  ");
}

// ---- Show current mode on LCD ----
void showMode() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mode: ADULT     ");
  lcd.setCursor(0, 1);
  lcd.print("Starting...     ");
  delay(1500);
  lcd.clear();
}

// ---- Show emergency stop ----
void showEmergency() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("!! EMERGENCY !! ");
  lcd.setCursor(0, 1);
  lcd.print("  Motor Stopped ");
}

// ---- Show rate and feedback on LCD ----
void showFeedback(int rate) {
  lcd.setCursor(0, 0);
  lcd.print("Rate:");
  if (rate < 10)       lcd.print("  ");
  else if (rate < 100) lcd.print(" ");
  lcd.print(rate);
  lcd.print(" /min   ");

  lcd.setCursor(0, 1);
  if (rate == 0) {
    lcd.print("  Compressing.. ");
  } else if (rate < RATE_MIN) {
    lcd.print("  Too Slow!     ");
  } else if (rate > RATE_MAX) {
    lcd.print("  Too Fast!     ");
  } else {
    lcd.print("  Good Pace!    ");
  }
}

// ---- Update LEDs based on rate ----
void updateLeds(int rate) {
  allLedsOff();
  if (rate == 0) {
    // no reading yet
  } else if (rate < RATE_MIN) {
    digitalWrite(LED_YELLOW, HIGH);
  } else if (rate > RATE_MAX) {
    digitalWrite(LED_RED, HIGH);
  } else {
    digitalWrite(LED_GREEN, HIGH);
  }
}

// =====================
//        SETUP
// =====================
void setup() {
  pinMode(IR_PIN, INPUT_PULLUP);
  pinMode(BTN_ADULT, INPUT);
  pinMode(BTN_STOP, INPUT);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  pinMode(MOTOR_RPWM, OUTPUT);
  pinMode(MOTOR_LPWM, OUTPUT);
  pinMode(MOTOR_R_EN, OUTPUT);
  pinMode(MOTOR_L_EN, OUTPUT);

  digitalWrite(MOTOR_R_EN, HIGH);
  digitalWrite(MOTOR_L_EN, HIGH);

  stopMotor();
  allLedsOff();

  attachInterrupt(digitalPinToInterrupt(IR_PIN), countCompression, FALLING);

  lcd.init();
  lcd.backlight();

  showWelcome();

  Serial.begin(9600);
  Serial.println("CPR Device Ready.");
}

// =====================
//        LOOP
// =====================
void loop() {

  if (digitalRead(BTN_STOP) == HIGH) {
    emergencyStopped = true;
    stopMotor();
    allLedsOff();
    digitalWrite(LED_RED, HIGH);
    showEmergency();
    delay(500);
    return;
  }

  if (emergencyStopped) {
    if (digitalRead(BTN_ADULT) == HIGH) {
      emergencyStopped = false;
    } else {
      return;
    }
  }

  if (digitalRead(BTN_ADULT) == HIGH && currentMode == 0) {
    currentMode = 1;
    compressionCount = 0;
    lastCountTime = millis();
    currentRate = 0;
    showMode();
    delay(300);
  }

  if (currentMode == 0) {
    showWelcome();
    delay(300);
    return;
  }

  runMotor(MOTOR_SPEED_ADULT);

  unsigned long now = millis();
  if (now - lastCountTime >= RATE_WINDOW_MS) {
    noInterrupts();
    int count = compressionCount;
    compressionCount = 0;
    interrupts();

    currentRate = count * (60000 / RATE_WINDOW_MS);
    lastCountTime = now;

    Serial.print("Rate: ");
    Serial.print(currentRate);
    Serial.println(" /min");
  }

  showFeedback(currentRate);
  updateLeds(currentRate);

  delay(200);
}
