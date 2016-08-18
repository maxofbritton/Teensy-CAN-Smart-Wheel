#include <Arduino.h>

#include "GUIHandler.h"
#include "GlobalVariables.h"
#include "AdafruitTFT.h"
//#include "AdafruitLEDBar.h"

int numberOfScreens = 3;
int screenOrder[] = {speedScreen, lapTimeScreen, carStatsScreen};



extern int displayedScreen;

void GUIHandler() {
  
}

void GUIHandlerSetup() {
  AdafruitTFTSetup();
  Serial.begin(9600);
//  AdafruitLEDBarSetup();
}

void GUIHandlerUpdate() {
  AdafruitTFTUpdate();
//  AdafruitLEDBarUpdate();
}

void GUIHandlerDisplayNewScreen(int commandType) {
  // Called Somewhere else in hardware
  switch(commandType) {
    case displayDownScreenCommand:
      GUIHandlerDisplayDownScreen();
      break;
    case displayUpScreenCommand:
      GUIHandlerDisplayUpScreen();
      break;

  }
}


/*
  Following are only called internally
 */

void GUIHandlerDisplayDownScreen() {
  // For screenOrder array
  int displayedScreenPos = 0;
  int nextScreenPos = 0;
  
  // Find index of what screen is currently displayed
  for (int i = 0; i < numberOfScreens; i++) {
    if (displayedScreen == screenOrder[i]) {
      displayedScreenPos = i;
      break;
    }
  }

  // Calculate screen index up from currenly displayed
  nextScreenPos = displayedScreenPos - 1;
  // If already at top, go to bottom
  if (nextScreenPos == 0) {
    nextScreenPos = (numberOfScreens - 1);
  }

  // Call the screen to display the new screen and erase the old
  AdafruitTFTDisplayNewScreen(screenOrder[nextScreenPos], screenOrder[displayedScreenPos]);
}

void GUIHandlerDisplayUpScreen() {
  // For screenOrder array
  int displayedScreenPos = 0;
  int nextScreenPos = 0;
  
  // Find index of what screen is currently displayed
  for (int i = 0; i < numberOfScreens; i++) {
    if (displayedScreen == screenOrder[i]) {
      displayedScreenPos = i;
      break;
    }
  }

  // Calculate screen index up from currenly displayed
  nextScreenPos = displayedScreenPos + 1;
  // If already at top, go to bottom
  if (nextScreenPos == numberOfScreens) {
    nextScreenPos = 0;
  }

  // Call the screen to display the new screen and erase the old
  AdafruitTFTDisplayNewScreen(screenOrder[nextScreenPos], screenOrder[displayedScreenPos]);
}

void GUIHandlerDisplaySpecifiedScreen(int specifiedScreen) {
    // For screenOrder array
  int displayedScreenPos = 0;
  
  // Find index of what screen is currently displayed
  for (int i = 0; i < numberOfScreens; i++) {
    if (displayedScreen == screenOrder[i]) {
      displayedScreenPos = i;
      break;
    }
  }
  
  AdafruitTFTDisplayNewScreen(specifiedScreen, screenOrder[displayedScreenPos]);
}

