# CPR Feedback Device

An Arduino Uno R4 Minima–based CPR feedback system designed to monitor chest compression rate and provide real-time feedback during automated cardiopulmonary resuscitation (CPR).

The system uses an LM393 infrared sensor to measure compression frequency, a BTS7960 motor driver to control a reciprocating linear actuator, and a 16×2 I2C LCD to display compression status. Visual feedback is provided using three LEDs, while an emergency stop feature allows immediate interruption of operation.

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
- BTS7960 Motor Driver
- 12V Reciprocating Linear Actuator
- 16×2 LCD with I2C Backpack
- 12V 7Ah Battery
- LEDs
- Push Buttons
- DC-DC Buck Converter
- Connecting Wires

---

## Pin Configuration

| Component | Arduino Pin |
|-----------|-------------|
| IR Sensor | D2 |
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
2. Select Adult Mode.
3. The linear actuator begins chest compressions.
4. The LM393 IR sensor detects each compression stroke.
5. The Arduino calculates compressions per minute (CPM).
6. The LCD displays the measured compression rate.
7. LEDs indicate compression quality:
   - Green – Correct compression rate
   - Yellow – Compression rate below target
   - Red – Compression rate above target
8. Press the emergency stop input to immediately halt the actuator.

---

## Compression Rate Feedback

| Compression Rate | LCD Message | LED |
|-----------------|------------|-----|
| 0 | Compressing... | Off |
| Below target | Too Slow! | Yellow |
| Target range | Good Pace! | Green |
| Above target | Too Fast! | Red |

---

## Project Structure

```
firmware/
    cpr_feedback_device.ino

circuit/
    circuit_diagram.png

images/
    prototype.jpg
```

---

## Libraries

- Wire
- LiquidCrystal_I2C

Install the `LiquidCrystal_I2C` library using the Arduino Library Manager before uploading the sketch.

---

## Upload Instructions

1. Open `cpr_feedback_device.ino` using Arduino IDE.
2. Select **Arduino Uno R4 Minima**.
3. Install the required libraries.
4. Connect the board via USB.
5. Upload the sketch.

---

## Future Improvements

- Compression depth sensing
- PID-based motor control
- Battery health monitoring
- Wireless monitoring
- Data logging
- Load-cell-based force feedback

---

## License

This project is released under the MIT License.
