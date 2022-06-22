#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

#define SENSOR_PIN 4

const int AIR_VALUE = 4095;
const int WATER_VALUE = 1700;
const int SENSOR_OFFSET = 60;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void drawHumScreen(int hum) {
  Serial.println(hum);

  display.clearDisplay();
  display.setTextSize(2); 
  display.setCursor(0,0);
  if (hum > 20) {
    display.println(F("HIGH"));
  } else if (hum > 18) {
    display.println(F("MIDDLE"));
  } else {
    display.println(F("LOW"));
  }

  display.setTextSize(3);
  display.println("");
  display.print(hum);
  display.println("%");

  display.display();
}



void setup() {
  Wire.begin(32, 33);

  Serial.begin(9600);

  while (!Serial) {
   Serial.println("Starting serial...");
  }

  pinMode(SENSOR_PIN, INPUT);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }

  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.println("HoneyHum v1");
  display.display();

  delay(2000);
  display.clearDisplay();
}

void loop() {
  int hum = analogRead(SENSOR_PIN);
  int hum_percentage = map(hum, AIR_VALUE, WATER_VALUE, 0, 100);
  drawHumScreen(hum_percentage - SENSOR_OFFSET);
  delay(400);
}