#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define MQ3_A A0     // MQ-3 sensor connected to A0
#define RELAY 7      // Relay connected to D7
#define BUZZER 8     // Buzzer connected to D8

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adjust I2C address if needed

void setup() {
    pinMode(MQ3_A, INPUT);
    pinMode(RELAY, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    
    digitalWrite(RELAY, HIGH); // Initially, allow motor to run
    digitalWrite(BUZZER, LOW); // Buzzer off initially
    
    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(" Alcohol Test ");
    delay(2000);
}

void loop() {
    int alcoholLevel = analogRead(MQ3_A);  // Read sensor value
    Serial.println(alcoholLevel);  // Debugging

    lcd.clear();
    lcd.setCursor(0, 0);

    if (alcoholLevel > 700) {  // Threshold value, adjust as needed
        lcd.print("Alcohol Detected!");
        lcd.setCursor(0, 1);
        lcd.print("Vehicle Stopped!");
        
        digitalWrite(RELAY, LOW); // Motor OFF
        digitalWrite(BUZZER, HIGH); // Alarm ON
    } else {
        lcd.print("No Alcohol!");
        lcd.setCursor(0, 1);
        lcd.print("Safe Driving!");
        
        digitalWrite(RELAY, HIGH); // Motor ON
        digitalWrite(BUZZER, LOW); // Alarm OFF
    }
    delay(1000);
}
