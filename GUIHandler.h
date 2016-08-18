#ifndef HUITOGUI_H_
#define HUITOGUI_H_

void GUIHandler();
void GUIHandlerSetup();
void GUIHandlerUpdate();
void GUIHandlerDisplayNewScreen(int commandType);

void GUIHandlerDisplayDownScreen();
void GUIHandlerDisplayUpScreen();
void GUIHandlerDisplaySpecifiedScreen(int screenNumber);

#endif
