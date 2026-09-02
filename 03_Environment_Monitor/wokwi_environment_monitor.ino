#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define DHT_PIN 2
#define DHT_TYPE DHT22

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

DHT dht(DHT_PIN, DHT_TYPE);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

void setup() {
  Serial.begin(9600);

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("Environment");
  display.println("Monitoring System");

  display.display();

  delay(2000);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT sensor error!");
    return;
  }

  // Serial output
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.println("--------------------");

  // OLED output
  display.clearDisplay();

  display.setCursor(0, 0);
  display.println("ENVIRONMENT");

  display.setCursor(0, 20);
  display.print("TEMP: ");
  display.print(temperature);
  display.println(" C");

  display.setCursor(0, 40);
  display.print("HUM : ");
  display.print(humidity);
  display.println(" %");

  display.display();

  delay(2000);
}
