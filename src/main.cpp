#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// IR sensors
const int irSensorLeftPin = 7;   // Left eye
const int irSensorRightPin = 8;  // Right eye
const int buzzerPin = 13;

unsigned long blinkStart;

void wakeUp() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Wake up");
  display.display();
  tone(buzzerPin, 1000);

  // Wait until at least one eye is open
  while (digitalRead(irSensorLeftPin) == LOW && digitalRead(irSensorRightPin) == LOW) {
    delay(100);
  }
  delay(2000);
}

void setup() {
  pinMode(irSensorLeftPin, INPUT);
  pinMode(irSensorRightPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void loop() {
  int leftEye = digitalRead(irSensorLeftPin);
  int rightEye = digitalRead(irSensorRightPin);

  if (leftEye == LOW && rightEye == LOW) {
    blinkStart = millis();
    while (millis() - blinkStart < 2000) {
      leftEye = digitalRead(irSensorLeftPin);
      rightEye = digitalRead(irSensorRightPin);

      // Exit early if either eye opens
      if (leftEye == HIGH || rightEye == HIGH) {
        break;
      }
      delay(100);
    }

    if (millis() - blinkStart >= 2000) {
      wakeUp();
    }
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Good stuff");
  display.display();

  delay(300);
}
