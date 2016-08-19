#include <Arduino.h>

#include "GUIHandler.h"
//#include "CANHandler.h"
//#include "ButtonHandler.h"
#include "GlobalVariables.h"

//#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include "ILI9341_t3.h"
//#include <Adafruit_ILI9341.h>
//#include <Adafruit_STMPE610.h>
//#include "Adafruit_LEDBackpack.h"

// Create Global Variables
// Car Info Data
int carSpeed = 0;
int carRPM = 4500;
int gear = 1;
int carOilPressure = 0;
int carEngineTemp = 0;
// Lap Time Data
int predictedLapTime;
int previousLapTime;
int bestLapTime;
int currentLapTime;
int deltaLapTime; // compared to ???????
// Used by GUIHandle and ADAFRUIT TFT
int displayedScreen = 0;  // used in HUItoGUI, updated in Screen
int activeAlert = 0;

int prevMillis;

void setup() {  
  Serial.begin(9600);
  GUIHandlerSetup();
//  CANHandlerSetup();
//  ButtonHandlerSetup();
}

void loop() {
  // Call functions to update hardware
  GUIHandlerUpdate();
//  CANHandlerUpdate();
//  ButtonHandlerUpdate();
  carRPM +=10;
  if (carRPM >6000) {
    carRPM = 0;
  }
  carSpeed++;
  if (carSpeed > 300) {
    carSpeed = 0;
//  GUIHandlerDisplaySpecifiedScreen(carStatsScreen);
  }

  
  int currentMillis = millis();
  if ((currentMillis - prevMillis) > 1000) {
    
    prevMillis = currentMillis;
    GUIHandlerDisplayNewScreen(displayUpScreenCommand);
  }
}
