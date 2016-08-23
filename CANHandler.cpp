#include "GlobalVariables.h"
#include "CANMessageIDs.h"
#include "CANHandler.h"
#include <FlexCAN.h>

FlexCAN CANbus(500000);
static CAN_message_t rxmsg;

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

#include <Arduino.h>


void CANHandler() {}

void CANHandlerSetup() {
  
  Serial.begin(9600);
  CANbus.begin();
}

void CANHandlerUpdate() {
  
  while ( CANbus.read(rxmsg) ) {
//      Serial.print("CAN ID: ");
//      Serial.println(rxmsg.id);
//      Serial.print("Message: ");
//      for (int i = 0; i<rxmsg.len; i++) {
//        Serial.print(rxmsg.buf[i]);
//        Serial.print(", ");
//      }
//      Serial.println();

//     MessageHandler(rxmsg);

    

    switch(rxmsg.id) {
      case CAN_ID_speed:
        carSpeed = rxmsg.buf[0];
        Serial.println(carSpeed);
        break;
      case CAN_ID_rpm:
        carRPM = ((256 * rxmsg.buf[0]) + rxmsg.buf[1]) / 4;
        break;
      case CAN_ID_temp:
        carEngineTemp = rxmsg.buf[0];
        break;
    }
   }
}

//void MessageHandler(CAN_message_t message) {
//  switch(message.id) {
//    case CAN_ID_speed:
//      carSpeed = message.buf[0];
//      break;
//    case CAN_ID_rpm:
//      carRPM = ((256 * message.buf[0]) + message.buf[1]) / 4;
//      break;
//    case CAN_ID_temp:
//      carEngineTemp = message.buf[0];
//      break;
//  }
//}

