#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


const int irSensorPin = 7;  // IR sensor output pin connected to digital pin 7
const int ledPin = 13;      // LED connected to digital pin 13 (optional)
unsigned long blinkStart;

void wakeUp(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wake up");
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
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
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
    lcd.setCursor(0, 0);
    lcd.print("Good Boy");
  }
  delay(300);  // Small delay for stability
}
