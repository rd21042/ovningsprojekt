# Övningsprojekt – DS3231 Clock with OLED & NeoPixel Ring  

### Author  
**Elis Jonsson**  
*Date: 2025-10-09*  

---

## Project Overview  

This project combines a **DS3231 Real-Time Clock (RTC)**, a **1306 OLED display**, and a **NeoPixel LED ring** to create a visually appealing and functional clock system.  

The OLED display features **two display modes**, toggled via a button:  

- **Mode 1 – Analog Clock:** Displays an analog clock face.  
- **Mode 2 – Digital Clock & Temperature:** Shows the current time as text and the measured temperature from the DS3231 sensor.  

Meanwhile, the **NeoPixel LED ring** performs a **colorful orbiting animation** that reflects the current temperature, which can be toggled on or off using the `led_on` flag in the code.

---

## Features  

Real-time clock using **DS3231**  
**OLED display (SSD1306 128x64)** with analog & digital modes  
**Temperature display** (from DS3231 sensor)  
**NeoPixel LED ring** animation with temperature-based color effects  
**Button control** to toggle between modes  
**Serial output** for time and date every 10 loops. 10 loops is roughly 1 second long.

## Hardware Requirements  

| Component | Description |
|------------|-------------|
| **Arduino** | Any compatible board (e.g., Uno, Nano) |
| **USB-Cable** | For connecting computer to Arduino, usually comes with the Arduino |
| **DS3231** | Real-Time Clock module |
| **OLED Display** | SSD1306 128x64 I2C |
| **NeoPixel Ring** | 24 RGB LEDs (Adafruit NeoPixel) |
| **Button** | Momentary pushbutton |
| **Resistors and Jump Wires** | For connections between components |
| **Breadboard** | To put components (except Arduino board), wires and resistors on |

---

## Required Libraries  

Make sure these libraries are installed in the Arduino IDE:  

- `Servo.h`  
- `RTClib.h`  
- `Wire.h`  
- `U8glib.h`  
- `Adafruit_NeoPixel.h`  
- `math.h` (built-in)  

You can install missing libraries via the Arduino Library Manager.