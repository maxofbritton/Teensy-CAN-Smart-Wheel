#include "ILI9341_t3.h"
#include "AdafruitTFT.h"
#include "GlobalVariables.h"

//#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
//#include <Adafruit_ILI9341.h>
//#include <Adafruit_STMPE610.h>

#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

//#define STMPE_CS 8
//Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

char carSpeedChar[4], carRPMChar[5];
String speedStr = "", RPMStr = "";
int speedX = 140, speedY = 50;
int RPMX = 100, RPMY = 160;
int prevCarSpeed = 0, prevCarRPM = 0;

extern int displayedScreen;
extern int carSpeed;
extern int carRPM;
extern int carOilPressure;
extern int carEngineTemp;
// Lap Time Data
extern int predictedLapTime;
extern int previousLapTime;
extern int bestLapTime;
extern int currentLapTime;
extern int deltaLapTime; // compared to ???????

void AdafruitTFT() {}

void AdafruitTFTSetup() {
  tft.begin();
  tft.setRotation(1); // no clue about rotation values 
  tft.fillScreen(ILI9341_BLACK);

  AdafruitTFTDisplayNewScreen(defaultScreen, defaultScreen);

}

void AdafruitTFTToggleScreen(int direction) {//1 == up, 0 == down
  if (direction == 1) {
    int nextScreen = displayedScreen + 1;
    if (nextScreen > finalScreen) {
      nextScreen = 0;
    }
    AdafruitTFTDisplayNewScreen(nextScreen, displayedScreen);
  } else {
    int nextScreen = displayedScreen - 1;
    if (nextScreen > finalScreen) {
      nextScreen = 0;
    }
    AdafruitTFTDisplayNewScreen(nextScreen, displayedScreen);
  }
  
}

void AdafruitTFTDisplayNewScreen(int drawScreen, int eraseScreen) {
  // Erase old screen
  switch (eraseScreen) {
    case speedScreen:
      eraseScreen1();
      break;
    case lapTimeScreen:
      eraseScreen2();
      break;
    case carStatsScreen:
      eraseScreen3();
      break;
  }

  // Draw new screen
  switch (drawScreen) {
    case speedScreen:
      drawScreen1();
      break;
    case lapTimeScreen:
      drawScreen2();
      break;
    case carStatsScreen:
      drawScreen3();
      break;
  }

  // Update global displayed screen value
  displayedScreen = drawScreen;

  // Update the Screen
  AdafruitTFTUpdate();
}

void AdafruitTFTUpdate() {
  // Check if the screen is being touched
  // IMPLEMENT LOGIC LATER
//  if (ts.touched()) {
//    TS_Point p = ts.getPoint();
//    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
//    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
//  }

  // Choose which screen to updated based on currently displayed screen
  switch (displayedScreen) {
    case speedScreen:
      updateScreen1();
      break;
    case lapTimeScreen:
      updateScreen2();
      break;
    case carStatsScreen:
      updateScreen3();
      break;
  }
}

/*
 * FONT SIZE IS 6 * size WIDE, 7 * size TALL
 */

/*
 * Screen 1: Speedomoter
 */

void drawScreen1() {
  // draw selected screen colour indicator
  tft.drawRect(0, 0, 320, 240, ILI9341_GREEN);  
  
  // Speed
  if (carSpeed < 0) {
    speedStr = "  0";
  } else if (carSpeed == 0) {
    speedStr = "  0";
  } else if (carSpeed < 10) {
    speedStr = "  " + String(carSpeed);
  } else if (carSpeed < 100) {
    speedStr = " " + String(carSpeed);
  } else {
    speedStr = String(carSpeed);
  } 
  speedStr.toCharArray(carSpeedChar, 4);
  // Draw Speed
  tft.setCursor(speedX, speedY);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setTextSize(5);
  tft.println(speedStr);
  // Draw MPH
  tft.setCursor(speedX, (speedY + 45));
  tft.setTextSize(3);
  tft.println("mph");

  // RPM
  if (carRPM < 0) {
    RPMStr = "   0";
  } else if (carRPM == 0) {
    RPMStr = "   0";
  } else if (carRPM < 10) {
    RPMStr = "   " + String(carRPM);
  } else if (carRPM < 100) {
    RPMStr = "  " + String(carRPM);
  } else if (carRPM < 1000) {
    RPMStr = " " + String(carRPM);
  } else {
    RPMStr = String(carRPM);
  } 
  RPMStr.toCharArray(carRPMChar, 5);
  // Draw RPM Value
  tft.setCursor(RPMX, RPMY);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setTextSize(4);
  tft.println(RPMStr);
  // Draw RPM
  tft.setCursor(RPMX, (RPMY + 40));
  tft.setTextSize(2);
  tft.println("RPM");
}

void eraseScreen1() {
//  // Erase MPH value
//  tft.fillRect(speedX, speedY, 85, 35, ILI9341_BLACK); 
//  // Erase 'MPH'
//  tft.setCursor(speedX, (speedY + 45));
//  tft.setTextColor(ILI9341_BLACK, ILI9341_BLACK);
//  tft.setTextSize(3);
//  tft.println("mph");
//
//   // Erase RPM Value
//  tft.setCursor(RPMX, RPMY);
//  tft.fillRect(RPMX, RPMY, 96, 28, ILI9341_BLACK);
//  // Erase 'RPM'
//  tft.setCursor(RPMX, (RPMY + 40));
//  tft.setTextColor(ILI9341_BLACK, ILI9341_BLACK);
//  tft.setTextSize(2);
//  tft.println("RPM");

    tft.fillScreen(ILI9341_BLACK);
}

void updateScreen1() {
  // update speed char array with new values if current and previous speeds are different
  if (carSpeed != prevCarSpeed) {    
    if (carSpeed < 0) {
      speedStr = "  0";
    } else if (carSpeed == 0) {
      speedStr = "  0";
    } else if (carSpeed < 10) {
      speedStr = "  " + String(carSpeed);
    } else if ( carSpeed < 100) {
      speedStr = " " + String(carSpeed);
    } else {
      speedStr = String(carSpeed);
    } 
    speedStr.toCharArray(carSpeedChar, 4);

    tft.setCursor(speedX, speedY);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.setTextSize(5);

     //100s
    int i = (int) (carSpeed / 100);
    int j = (int) (prevCarSpeed / 100);
    if (i != j) {
      tft.setCursor(speedX, speedY);
      tft.println(carSpeedChar[0]);
    }

    //10s
    int f = (carSpeed % 100) / 10;
    int g = (prevCarSpeed % 100) / 10;
    if (f != g) {
      tft.setCursor(speedX + 30, speedY);
      tft.println(carSpeedChar[1]);
    }

    //1s
    int l = carSpeed % 10;
    int m = prevCarSpeed % 10;
    if (l != m) {
      tft.setCursor(speedX + 60, speedY);
      tft.println(carSpeedChar[2]);
    }
    prevCarSpeed = carSpeed;
  }




  if (carRPM != prevCarRPM) {    
    if (carRPM < 0) {
      RPMStr = "   0";
    } else if (carRPM == 0) {
      RPMStr = "   0";
    } else if (carRPM < 10) {
      RPMStr = "   " + String(carRPM);
    } else if (carRPM < 100) {
      RPMStr = "  " + String(carRPM);
    } else if (carRPM < 1000) {
    RPMStr = " " + String(carRPM);
    } else {
      RPMStr = String(carRPM);
    } 
    RPMStr.toCharArray(carRPMChar, 5);

    tft.setCursor(RPMX, RPMY);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.setTextSize(4);

    //1000s
    int a = (int) (carRPM / 1000);
    int b = (int) (prevCarRPM / 1000);
    if (a != b) {
      tft.setCursor(RPMX, RPMY);
      tft.println(carRPMChar[0]);
    }

     //100s
    int i = (int) (carRPM / 100) % 10;
    int j = (int) (prevCarRPM / 100)  % 10;
    if (i != j) {
      tft.setCursor(RPMX + 24, RPMY);
      tft.println(carRPMChar[1]);
    }

    //10s
    int f = (carRPM % 100) / 10;
    int g = (prevCarRPM % 100) / 10;
    if (f != g) {
      tft.setCursor(RPMX + 48, RPMY);
      tft.println(carRPMChar[2]);
    }

    //1s
    int l = carRPM % 10;
    int m = prevCarRPM % 10;
    if (l != m) {
      tft.setCursor(RPMX + 72, RPMY);
      tft.println(carRPMChar[3]);
    }
    prevCarRPM = carRPM;
  }
}

/*
 * Screen 2: other screen?
 */

void drawScreen2() {
  // draw selected screen colour inicator
  tft.drawRect(0,0,320,240,ILI9341_BLUE);
//
//  Tft.drawString("SCREEN 2",60,60,3,WHITE);
  
}

void eraseScreen2() {
//  Tft.drawString("SCREEN 2",60,60,3,BLACK);
  tft.fillScreen(ILI9341_BLACK);
}

void updateScreen2() {
// update screen 2
}

/*
 * Screen 3: Critical Car Info 
*/

void drawScreen3() {
  // draw selected screen colour inicator
  tft.drawRect(0,0,320,240,ILI9341_RED);
//
//  Tft.drawString("SCREEN 3",60,60,3,WHITE);
  
}

void eraseScreen3() {
//  Tft.drawString("SCREEN 3",60,60,3,BLACK);
  tft.fillScreen(ILI9341_BLACK);
}

void updateScreen3() {

}
