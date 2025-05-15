#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int irSensorPin = 7;  // IR sensor output pin connected to digital pin 7
const int ledPin = 13;      // LED connected to digital pin 13 (optional)
unsigned long blinkStart;

void wakeUp(){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Wake up");
  display.display();
  digitalWrite(ledPin, HIGH);  // Turn on LED (optional)
  while(digitalRead(irSensorPin)==LOW){
    delay(100);
  }
  delay(2000);
}

void setup() {
  pinMode(irSensorPin, INPUT);  // Set IR sensor pin as input
  pinMode(ledPin, OUTPUT);      // Set LED pin as output (optional)
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void loop() {
  int alcoholValue = analogRead(0);       // read alcohol sensor input
  Serial.println(alcoholValue, DEC);  // prints the value read
  int sensorValue = digitalRead(irSensorPin);  // Read the IR sensor value
  if (sensorValue == LOW) {
    blinkStart = millis();
    while(millis()-blinkStart<2000){
      if(digitalRead(irSensorPin)==HIGH){
        break;
      }
      delay(100);
    }
    if(millis()-blinkStart>=2000){
      wakeUp();
    }
    // Obstacle detected
  } else {
    // No obstacle
    digitalWrite(ledPin, LOW);   // Turn off LED (optional)
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Good stuff");
  display.display();

  delay(300);  // Small delay for stability
}
