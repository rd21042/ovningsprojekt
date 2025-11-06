# ⏰ Övningsprojekt – DS3231 Clock with OLED & NeoPixel Ring  

### Author  
**Elis Jonsson**  
📅 *Date: 2025-10-09*  

---

## 🧩 Project Overview  

This project combines a **DS3231 Real-Time Clock (RTC)**, a **1306 OLED display**, and a **NeoPixel LED ring** to create a visually appealing and functional clock system.  

The OLED display features **two display modes**, toggled via a button:  

- 🕒 **Mode 1 – Analog Clock:** Displays an analog clock face.  
- 💬 **Mode 2 – Digital Clock & Temperature:** Shows the current time as text and the measured temperature from the DS3231 sensor.  

Meanwhile, the **NeoPixel LED ring** performs a **colorful orbiting animation** that reflects the current temperature, which can be toggled on or off using the `led_on` flag in the code.

---

## ⚙️ Features  

✅ Real-time clock using **DS3231**  
✅ **OLED display (SSD1306 128x64)** with analog & digital modes  
✅ **Temperature display** (from DS3231 sensor)  
✅ **NeoPixel LED ring** animation with temperature-based color effects  
✅ **Button control** to toggle between modes  
✅ **Serial output** for time and date every 10 loops  

---

## 🧠 How It Works  

1. **Startup:**  
   The DS3231 RTC initializes and the OLED display is set up. The compile-time clock is written to the RTC once (then should be commented out).  

2. **Display Modes:**  
   - The button toggles a boolean (`drawClock`) that switches between analog and digital display modes.  
   - Analog mode draws a clock face with hour, minute, and second hands.  
   - Digital mode displays formatted time and temperature text.  

3. **LED Ring Animation:**  
   - The NeoPixel ring cycles through an orbiting pattern.  
   - LED color changes depending on temperature (cooler → blue, warmer → red).  
   - Controlled by `led_on` in the global variables.  

4. **Serial Monitor Output:**  
   Every few loops, the current day and time are printed to the serial monitor.  

---

## 🔧 Hardware Requirements  

| Component | Description |
|------------|-------------|
| **Arduino** | Any compatible board (e.g., Uno, Nano) |
| **DS3231** | Real-Time Clock module |
| **OLED Display** | SSD1306 128x64 I2C |
| **NeoPixel Ring** | 24 RGB LEDs (Adafruit NeoPixel) |
| **Button** | Momentary pushbutton |
| **Resistors/Wires** | For connections and button pull-down |

---

## 📚 Required Libraries  

Make sure these libraries are installed in the Arduino IDE:  

- `Servo.h`  
- `RTClib.h`  
- `Wire.h`  
- `U8glib.h`  
- `Adafruit_NeoPixel.h`  
- `math.h` (built-in)  

You can install missing libraries via the Arduino Library Manager.