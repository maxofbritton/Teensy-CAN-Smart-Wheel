#include "AdafruitLEDBar.h"
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#include "GlobalVariables.h"

#include <Arduino.h>

// Gear Shift Point Preferences
// Shift point revs 0=1st 1=2nd etc
//int shiftPoint[] = {6000, 6000, 6000, 6000, 6000, 6000};
int minDisplayShiftPoint[] = {0, 0, 0, 0, 0, 0};
int revsToShiftPoint = 0;
extern int carRPM;
extern int gear;
extern int activeAlert;
int revsToShiftPointPrev = 0;

Adafruit_24bargraph bar = Adafruit_24bargraph();

void AdafruitLEDBar() {

}

void AdafruitLEDBarSetup() {
  Serial.begin(9600);
  Wire.begin ();
  Wire.beginTransmission(70);
  if (Wire.endTransmission() == 0) {
    bar.begin(0x70);
    Serial.println("LED Bar connected sucessfully!");
  } else {
    Serial.println("LED Bar not connected!");
  }
}

void AdafruitLEDBarUpdate() {
  if (activeAlert == 0) {
    displayShiftPoint();
  } else {
    displayAlert(activeAlert);
  }
}

void displayShiftPoint() {
  // Compares carRPM to min number of revs to display
  // one LED = 100
  int revsToShiftPoint = (int) (carRPM - 3600) / 100;
  if (revsToShiftPoint < 0) {
    revsToShiftPoint = -1;
  }
  if (revsToShiftPoint != revsToShiftPointPrev) {
    for (int b = 0; b < revsToShiftPoint; b++) {
      if (b < 8) {
        bar.setBar(b, LED_GREEN);
      } else if ( b > 7 && b < 16) {
        bar.setBar(b, LED_YELLOW);
      } else if (b > 15) {
        bar.setBar(b, LED_RED);
      }
      bar.writeDisplay();
    }

    for (int b = 0; b < (23 - revsToShiftPoint); b++) {
      bar.setBar(23 - b, LED_OFF);
    }
    bar.writeDisplay();
    revsToShiftPointPrev = revsToShiftPoint;
  }
}

void displayAlert(int alert) {
  switch (alert) {
    case fastestLapMsg:
      for (int b = 0; b < 24; b++) {
        bar.setBar(b, LED_GREEN);
      }
      bar.writeDisplay();
      bar.blinkRate(1);
      break;
    case OtherMsg:
      for (int b = 0; b < 24; b++) {
        bar.setBar(b, LED_YELLOW);
      }
      bar.writeDisplay();
      bar.blinkRate(1);
      break;
    case OtherOtherMsg:
      for (int b = 0; b < 24; b++) {
        bar.setBar(b, LED_RED);
      }
      bar.writeDisplay();
      bar.blinkRate(1);
      break;
  }
}

/*
  setBrightness(brightness) 0-15
  blinkRate(rate) 0 off, 1-3 different rates
*/
