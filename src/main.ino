#include <thread>
#include "App.h"
#include "user/BasicRpmDisplay.h"

using namespace rgb;

BasicRpmDisplay scene;

void setup() {
  App::Init(scene);
  std::thread t{[](){
    while (true) {
      Serial.println("Hello!");
      delay(1000);
    }
  }};

  t.detach();
}

void loop() {
  App::Loop();
}
//
//#include <Arduino.h>
//#include <Wire.h>
//#include <OBD.h>
//#include <Adafruit_NeoPixel.h>
//
//COBD obd; /* for Model A (UART version) */
//Adafruit_NeoPixel circuit{12, D2, NEO_GRBW + NEO_KHZ800};
//
//void senderSetup() {
//  Serial1.begin(9600, SERIAL_8N1, RX, TX);
//  pinMode(LED_BUILTIN, OUTPUT);
//}
//
//void senderLoop() {
//  digitalWrite(LED_BLUE, HIGH);
//
//  Serial1.println('1');
//  digitalWrite(LED_BUILTIN, HIGH);
//  Serial.println("LEDS ON");
//
//  while (!Serial1.available()) {
//    delay(100);
//  }
//  char receivedData = Serial1.read();
//  if (receivedData == '1') {
//    digitalWrite(LED_BLUE, LOW);
//  }
//
//  Serial1.println('2');
//  digitalWrite(LED_BUILTIN, LOW);
//  Serial.println("LEDS OFF");
//  delay(1000);
//}
//
//void obdSetup() {
//  // start communication with OBD-II adapter
//
//  int x = LOW;
//  digitalWrite(LED_BLUE, x);
//  Serial.println("obd.begin()");
//  while(!obd.begin()) {
//    x = x == LOW ? HIGH : LOW;
//    digitalWrite(LED_BLUE, x);
//    Serial.println("obd.begin()");
//  }
//  digitalWrite(LED_BLUE, HIGH);
//
//  // initiate OBD-II connection until success
//  x = LOW;
//  digitalWrite(LED_GREEN, x);
//  while (!obd.init()) {
//    x = x == LOW ? HIGH : LOW;
//    digitalWrite(LED_GREEN, x);
//  }
//  digitalWrite(LED_GREEN, HIGH);
//
//  circuit.begin();
//  circuit.setBrightness(255);
//
//  digitalWrite(LED_BUILTIN, HIGH);
//}
//
//void obdLoop() {
//  int value = 0;
//  // save engine RPM in variable 'value', return true on success
//  if (obd.readPID(PID_RPM, value)) {
//    // light on LED on Arduino board when the RPM exceeds 3000
//    digitalWrite(LED_RED, value > 1000 ? LOW : HIGH);
//  }
//
//  int rpm = value;
//  if (rpm < 500) {
//    rpm = 500;
//  }
//
//  int pixel = (rpm / 500);
//
//  int high = 5;
//  int low = 1;
//
//  for (int i = 2; i < 9; ++i) {
//    if (i - 2 < pixel) {
//      circuit.setPixelColor(i, 0, high, 0);
//    }
//    else {
//      circuit.setPixelColor(i, 0, low, 0);
//    }
//  }
//  for (int i = 9; i < 11; ++i) {
//    if (i - 2 < pixel) {
//      circuit.setPixelColor(i, high, high, 0);
//    }
//    else {
//      circuit.setPixelColor(i, low, low, 0);
//    }
//  }
//  for (int i = 11; i < 12; ++i) {
//    if (i - 2 < pixel) {
//      circuit.setPixelColor(i, high, 0, 0);
//    }
//    else {
//      circuit.setPixelColor(i, low, 0, 0);
//    }
//  }
//
//  circuit.show();
//}
//
//void setup()
//{
//  Serial.begin(9600);
//  delay(1000);
//  Serial.println("Beginning OBD2 Connection");
//
//  pinMode(LED_BLUE, OUTPUT);
//  pinMode(LED_GREEN, OUTPUT);
//  pinMode(LED_RED, OUTPUT);
//  pinMode(LED_BUILTIN, OUTPUT);
//  digitalWrite(LED_BLUE, HIGH);
//  digitalWrite(LED_GREEN, HIGH);
//  digitalWrite(LED_RED, HIGH);
//  digitalWrite(LED_BUILTIN, LOW);
//
////  senderSetup();
//  obdSetup();
//}
//
//void loop()
//{
////  senderLoop();
//  obdLoop();
//}