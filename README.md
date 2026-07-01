# CPR Feedback Device

An Arduino Uno R4 Minima–based CPR feedback system designed to monitor chest compression rate and provide real-time feedback during automated cardiopulmonary resuscitation (CPR).

The system uses an LM393 infrared speed sensor to measure compression frequency, a BTS7960 43A motor driver to control a reciprocating linear actuator, and a 16×2 I2C LCD to display compression status. Visual feedback is provided using three LEDs, while an emergency stop feature allows immediate interruption of operation.

# CPR Feedback Device

An Arduino Uno R4 Minima–based CPR feedback system designed to monitor chest compression rate and provide real-time feedback during automated cardiopulmonary resuscitation (CPR).

The system uses an LM393 infrared speed sensor to measure compression frequency, a BTS7960 43A motor driver to control a reciprocating linear actuator, and a 16×2 I2C LCD to display compression status. Visual feedback is provided using three LEDs, while an emergency stop feature allows immediate interruption of operation.

---

## Features

- Adult CPR mode
- Real-time compression rate monitoring
- IR sensor–based stroke detection
- Compression rate calculation (CPM)
- LCD feedback display
- LED status indicators
- Emergency stop functionality
- BTS7960 motor control
- Closed-loop monitoring of compression frequency

---

## Hardware

- Arduino Uno R4 Minima
- LM393 IR Speed Sensor
- BTS7960 43A Motor Driver
- 12V Reciprocating Linear Actuator
- 16×2 LCD with I2C Backpack
- 12V 7Ah Sealed Lead Acid (SLA) Battery
- DC-DC Buck Converter
- Push Buttons
- LEDs
- Breadboard
- Jumper Wires

---

## Pin Configuration

| Component | Arduino Pin |
|-----------|-------------|
| IR Sensor OUT | D2 |
| Adult Mode Input | D3 |
| Emergency Stop | D5 |
| Green LED | D6 |
| Yellow LED | D7 |
| Red LED | D8 |
| BTS7960 RPWM | D9 |
| BTS7960 LPWM | D10 |
| BTS7960 R_EN | D11 |
| BTS7960 L_EN | D12 |
| LCD SDA | A4 |
| LCD SCL | A5 |

---

## Working Principle

1. Power on the system.
2. Select **Adult Mode**.
3. The BTS7960 motor driver powers the reciprocating linear actuator to perform automated chest compressions.
4. The LM393 IR sensor detects every actuator stroke.
5. The Arduino Uno R4 Minima calculates the compression rate in compressions per minute (CPM).
6. The current compression rate is displayed on the 16×2 LCD.
7. LED indicators provide visual feedback:
   - **Green:** Compression rate within the target range (120–140 CPM)
   - **Yellow:** Compression rate below the target range
   - **Red:** Compression rate above the target range
8. Activating the emergency stop immediately stops the actuator and displays an emergency message on the LCD.

---

## Compression Rate Feedback

| Compression Rate | LCD Message | LED Status |
|------------------|------------|------------|
| 0 CPM | Compressing... | Off |
| Below 120 CPM | Too Slow! | Yellow |
| 120–140 CPM | Good Pace! | Green |
| Above 140 CPM | Too Fast! | Red |

---

## Repository Structure

```text
cpr-feedback-device/
├── firmware/
│   └── cpr_feedback_device.ino
├── circuit/
│   ├── circuit_diagram.png
│   └── wiring_diagram.png
├── images/
│   ├── prototype.jpg
│   ├── lcd_feedback.jpg
│   └── system_overview.png
├── README.md
├── LICENSE
└── .gitignore
```

---

## Required Libraries

- Wire (included with the Arduino IDE)
- LiquidCrystal_I2C

Install the **LiquidCrystal_I2C** library using the Arduino Library Manager before uploading the firmware.

---

## Upload Instructions

1. Open `firmware/cpr_feedback_device.ino` in the Arduino IDE.
2. Select **Arduino Uno R4 Minima** as the target board.
3. Install the required libraries.
4. Connect the board via USB.
5. Compile and upload the firmware.
6. Connect the hardware according to the wiring diagram.
7. Power the system and begin operation.

---

## Future Improvements

- Compression depth sensing using force sensors
- PID-based motor speed control
- Wireless monitoring using Bluetooth or Wi-Fi
- Battery health monitoring
- Data logging for CPR sessions
- Load-cell-based compression force feedback

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Features

- Adult CPR mode
- Real-time compression rate monitoring
- IR sensor–based stroke detection
- Compression rate calculation (CPM)
- LCD feedback display
- LED status indicators
- Emergency stop functionality
- BTS7960 motor control
- Closed-loop monitoring of compression frequency

---

## Hardware

- Arduino Uno R4 Minima
- LM393 IR Speed Sensor
- BTS7960 43A Motor Driver
- 12V Reciprocating Linear Actuator
- 16×2 LCD with I2C Backpack
- 12V 7Ah Sealed Lead Acid (SLA) Battery
- DC-DC Buck Converter
- Push Buttons
- LEDs
- Breadboard
- Jumper Wires

---

## Pin Configuration

| Component | Arduino Pin |
|-----------|-------------|
| IR Sensor OUT | D2 |
| Adult Mode Input | D3 |
| Emergency Stop | D5 |
| Green LED | D6 |
| Yellow LED | D7 |
| Red LED | D8 |
| BTS7960 RPWM | D9 |
| BTS7960 LPWM | D10 |
| BTS7960 R_EN | D11 |
| BTS7960 L_EN | D12 |
| LCD SDA | A4 |
| LCD SCL | A5 |

---

## Working Principle

1. Power on the system.
2. Select **Adult Mode**.
3. The BTS7960 motor driver powers the reciprocating linear actuator to perform automated chest compressions.
4. The LM393 IR sensor detects every actuator stroke.
5. The Arduino Uno R4 Minima calculates the compression rate in compressions per minute (CPM).
6. The current compression rate is displayed on the 16×2 LCD.
7. LED indicators provide visual feedback:
   - **Green:** Compression rate within the target range (120–140 CPM)
   - **Yellow:** Compression rate below the target range
   - **Red:** Compression rate above the target range
8. Activating the emergency stop immediately stops the actuator and displays an emergency message on the LCD.

---

## Compression Rate Feedback

| Compression Rate | LCD Message | LED Status |
|------------------|------------|------------|
| 0 CPM | Compressing... | Off |
| Below 120 CPM | Too Slow! | Yellow |
| 120–140 CPM | Good Pace! | Green |
| Above 140 CPM | Too Fast! | Red |

---

## Required Libraries

- Wire (included with the Arduino IDE)
- LiquidCrystal_I2C

Install the **LiquidCrystal_I2C** library using the Arduino Library Manager before uploading the firmware.

---

## Upload Instructions

1. Open `firmware/cpr_feedback_device.ino` in the Arduino IDE.
2. Select **Arduino Uno R4 Minima** as the target board.
3. Install the required libraries.
4. Connect the board via USB.
5. Compile and upload the firmware.
6. Connect the hardware according to the wiring diagram.
7. Power the system and begin operation.

---

## Future Improvements

- Compression depth sensing using force sensors
- PID-based motor speed control
- Wireless monitoring using Bluetooth or Wi-Fi
- Battery health monitoring
- Data logging for CPR sessions
- Load-cell-based compression force feedback

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
