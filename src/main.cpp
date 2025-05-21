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

const int irSensorLeftPin = 7;   // Left eye
const int irSensorRightPin = 8;  // Right eye
const int buzzerPin = 13;
const int buttonPin = 6;

unsigned long blinkStart;
bool inStaringContest = false;
unsigned long highScore = 0;  // milliseconds

void showCountdown() {
  for (int i = 3; i >= 1; i--) {
    display.clearDisplay();
    display.setCursor(50, 20);
    display.setTextSize(3);
    display.println(i);
    display.display();

    tone(buzzerPin, 800);   // Play tone at 800Hz
    delay(400);             // Tone duration
    noTone(buzzerPin);
    delay(600);             // Remaining part of 1s
  }

  display.clearDisplay();
  display.setCursor(30, 20);
  display.setTextSize(2);
  display.println("GO!");
  display.display();

  tone(buzzerPin, 1200);    // High pitch for "GO!"
  delay(500);
  noTone(buzzerPin);

  display.setTextSize(2); // Reset text size
}

void wakeUp() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Wake up");
  display.display();
  tone(buzzerPin, 1000);

  while (digitalRead(irSensorLeftPin) == LOW && digitalRead(irSensorRightPin) == LOW) {
    delay(100);
  }
  noTone(buzzerPin);
  delay(2000);
}

void startStaringContest() {
  inStaringContest = true;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Staring");
  display.setCursor(0, 20);
  display.println("Contest!");
  display.display();
  delay(1000);

  // Wait for both eyes to open
  while (digitalRead(irSensorLeftPin) == LOW && digitalRead(irSensorRightPin) == LOW) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Open eyes!");
    display.display();
    delay(100);
  }

  showCountdown();

  unsigned long startTime = millis();

  while (digitalRead(irSensorLeftPin) == HIGH || digitalRead(irSensorRightPin) == HIGH) {
    unsigned long elapsed = (millis() - startTime) / 1000;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Don't blink!");
    display.setCursor(0, 20);
    display.print("Time: ");
    display.print(elapsed);
    display.println("s");
    display.setCursor(0, 40);
    display.print("Best: ");
    display.print(highScore / 1000);
    display.println("s");
    display.display();
    delay(100);
  }

  unsigned long totalTime = millis() - startTime;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("You blinked!");
  display.setCursor(0, 20);
  display.print("Time: ");
  display.print(totalTime / 1000);
  display.println("s");

  if (totalTime > highScore) {
    highScore = totalTime;
    display.setCursor(0, 40);
    display.println("New Record!");
  } else {
    display.setCursor(0, 40);
    display.print("Best: ");
    display.print(highScore / 1000);
    display.println("s");
  }

  display.display();
  delay(4000);

  inStaringContest = false;
}

void setup() {
  pinMode(irSensorLeftPin, INPUT);
  pinMode(irSensorRightPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // button is active-low

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
  if (digitalRead(buttonPin) == LOW && !inStaringContest) {
    startStaringContest();
    return;
  }

  int leftEye = digitalRead(irSensorLeftPin);
  int rightEye = digitalRead(irSensorRightPin);

  if (leftEye == LOW && rightEye == LOW) {
    blinkStart = millis();
    while (millis() - blinkStart < 2000) {
      leftEye = digitalRead(irSensorLeftPin);
      rightEye = digitalRead(irSensorRightPin);
      if (leftEye == HIGH || rightEye == HIGH) break;
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
