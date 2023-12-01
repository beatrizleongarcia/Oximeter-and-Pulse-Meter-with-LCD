
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000
PulseOximeter pox;
uint32_t tsLastReport = 0;

void onBeatDetected()
{
    Serial.println("Beat!");
}

#include <LiquidCrystal.h>
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
const int sensor=A1;
int tempc;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  //LCD's columns and rows:
  lcd.begin(16, 2);
  pinMode(sensor,INPUT); 

  if (!pox.begin()) {
      //lcd.print("FAILED");
      for(;;);
  } else {
      //lcd.print("SUCCESS");
  }
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
  pox.update();
  
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    lcd.setCursor(0,0);
    lcd.print("HR =");
    lcd.print(" ");
    lcd.print(pox.getHeartRate());
    lcd.print("bpm    ");
    lcd.setCursor(0,1);
    lcd.print("02%=");
    lcd.print(" ");
    lcd.print(pox.getSpO2());
    lcd.print("%  ");
    tsLastReport = millis();
  }
}