/*
 * Name: övningsprojekt
 * Author: Elis Jonsson
 * Date: 2025-10-09
 * Description: This project uses a DS3231 to measure time and displays the time 
 * on a 1306 OLED display. The display has two modes that can be toggled using a button:
 *  Mode 1: An analog clock
 *  Mode 2: Time as text and temperature
 * In addition to this a NeoPixel LED ring does a cool pattern,
 * which can be toggled under Global variables: Misc: led_on
*/

// Include Libraries
#include <Servo.h>
#include <RTClib.h>
#include <Wire.h>
#include <U8glib.h>
#include <math.h>
#include <Adafruit_NeoPixel.h>

// Construct objects
RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 screen(U8G_I2C_OPT_NO_ACK);

// Construct LED ring
#define PIN 2
#define NUM_PIXELS 24
Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Global variables: Clock
const int circle_x_pos = 64;
const int circle_y_pos = 32;
const int radius = 30;

// Global variables: Pins
const int LEDPin = 8;
const int buttonPin = 7;
int lastButtonState = 1;

// Global variables: NeoPixel LED Ring
int startPixel = 0;
int endPixel = NUM_PIXELS - 1;
int direction = 1;

// Global variables: Misc
const char* daysOfTheWeek[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
const bool led_on = false;
bool drawClock = true;
int delayCounter = 0;

void setup() {
  // Init communication
  Serial.begin(9600);
  Wire.begin();

  // Init Hardware
  pinMode(LEDPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  rtc.begin();
  strip.begin();
  strip.show();

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // set RTC to compile time ONCE then make it a comment
  screen.setFont(u8g_font_5x7);
}

void loop() {
  String currentTime = getTime();
  String currentDay = getDay();
  float temp = getTemp();

  int buttonState = digitalRead(buttonPin);
  if (buttonState) {
    drawClock = !drawClock; // Toggles between analog and digital clock by inversing a bool (true -> false and false -> true)
  }

  if (drawClock) {
    oledDrawClock();
    delay(200);
  } else {
    oledWrite(currentTime, String(temp));
  }

  if (led_on) {
    LEDRingOrbit();
  }

  if (delayCounter == 10) {
    delayCounter = 0;
    Serial.println(currentDay + " " + currentTime);
  }

  delay(100);
  delayCounter++;
}

/*
 * Reads the current day, month and year from the DS3231 and returns it as "dd mm/yy"
 */
String getDay() {
  DateTime now = rtc.now();
  String dayStr = daysOfTheWeek[now.dayOfTheWeek()]) + " " + String(now.day());
  String monthStr = String(now.month());
  String yearStr = String(now.year());
  return String(dayStr + "/" + monthStr + "/" + yearStr);
}

/*
 * Reads the current time from the DS3231 and returns it as "hh:mm:ss"
 */
String getTime() {
  DateTime now = rtc.now();

  // Format hours, minutes, and seconds with leading zeros
  String hourStr = String(now.hour());
  String minuteStr = (now.minute() < 10 ? "0" : "") + String(now.minute());
  String secondStr = (now.second() < 10 ? "0" : "") + String(now.second());

  return hourStr + ":" + minuteStr + ":" + secondStr;
}

/*
 * Reads the temperature from DS3231 and returns it as a float
 */
float getTemp() {
  return rtc.getTemperature();
}

/*
Displays each pixel based on current temperature, once at a time to the LED ring
*/
void LEDRingOrbit() {
  int color = map(getTemp(), 20, 35, 0, 255);

  // Turn on one pixel at a time until all pixels are lit
  for (int i = startPixel; i != endPixel; i += direction) {
    strip.setPixelColor(i, strip.Color(color, 0, 255 - color));
    strip.show();
    delay(30);
  }

  // Turn off one pixel at a time until all pixels are off
  for (int i = endPixel; i != startPixel; i -= direction) {
    strip.setPixelColor(i, 0);
    strip.show();
    delay(30);
  }

  // Swap startpoint with endpoint and then change direction
  int temp = startPixel;
  startPixel = endPixel;
  endPixel = temp;
  direction *= -1;
}

/*
 * Displays text on the OLED display
 */
void oledWrite(String text1, String text2) {
  screen.firstPage();
  do {
    screen.drawStr(30, 20, text1.c_str());
    screen.drawStr(30, 40, (text2 + " C").c_str());
  } while (screen.nextPage());
}

/*
* Draws an analog clock on the oled
*/
void oledDrawClock() {
  // Check what time it is
  DateTime now = rtc.now();
  float second = now.second();
  float minute = now.minute() + second / 60.0;
  float hour = (now.hour() % 12) + minute / 60.0;

  // Calculate hand endpoints by using sin and cos
  const int hourEnd_x_pos = circle_x_pos + (radius * sin(hour * M_PI / 6)) / 2;
  const int hourEnd_y_pos = circle_y_pos - (radius * cos(hour * M_PI / 6)) / 2;
  const int minuteEnd_x_pos = circle_x_pos + radius * sin(minute * M_PI / 30);
  const int minuteEnd_y_pos = circle_y_pos - radius * cos(minute * M_PI / 30);
  const int secondEnd_x_pos = circle_x_pos + radius * sin(second * M_PI / 30);
  const int secondEnd_y_pos = circle_y_pos - radius * cos(second * M_PI / 30);

  screen.firstPage();
  do {
    // Draw outline
    screen.drawCircle(circle_x_pos, circle_y_pos, radius);

    // Draw hands
    screen.drawLine(circle_x_pos, circle_y_pos, hourEnd_x_pos, hourEnd_y_pos);
    screen.drawLine(circle_x_pos, circle_y_pos, minuteEnd_x_pos, minuteEnd_y_pos);
    screen.drawLine(circle_x_pos, circle_y_pos, secondEnd_x_pos, secondEnd_y_pos);

    // Draw hour labels
    for (int i = 1; i <= 12; i += 1) {
      const int clockLabel_x = (circle_x_pos - 2) + (radius - 5) * sin(i * M_PI / 6);
      const int clockLabel_y = (circle_y_pos + 2) - (radius - 5) * cos(i * M_PI / 6);
      screen.drawStr(clockLabel_x, clockLabel_y, String(i).c_str());
    }
  } while (screen.nextPage());
}