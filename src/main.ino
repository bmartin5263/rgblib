#include "lincoln/LincolnLightsApp.h"

LincolnLightsApp app{};

//auto setup() -> void {
//  IrReceiver.begin(D3, ENABLE_LED_FEEDBACK, LED_RED);
//  app.setup();
//}
//
//auto loop() -> void {
//  app.loop();
//
//  if (IrReceiver.decode()) {
//    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
//    IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
//    IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
//    IrReceiver.resume(); // Enable receiving of the next value
//  }
//}

void setup() {
  app.setup();
}

void loop() {
  app.loop();
}