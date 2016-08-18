#ifndef ADAFRUITTFT_H_
#define ADAFRUITTFT_H_

void AdafruitTFT();
void AdafruitTFTSetup();
void AdafruitTFTUpdate();
void AdafruitTFTDisplayNewScreen(int drawScreen, int eraseScreen);
void AdafruitTFTToggleScreen(int direction);

void drawScreen1();
void updateScreen1();
void eraseScreen1();

void drawScreen2();
void updateScreen2();
void eraseScreen2();

void drawScreen3();
void updateScreen3();
void eraseScreen3();

#endif
