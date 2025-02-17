//#include <Arduino.h>
//#include <Adafruit_NeoPixel.h>
////
//////#include "App.hpp"
//////#include "user/DemoScene.h"
////
//////void setup(){
//////  delay(2000);
//////  Serial.begin(9600);
//////}
//////
//////void loop(){
//////  Serial.println("Hello World");
//////  delay(500);
//////}
////
//Adafruit_NeoPixel circuit(16, D5, NEO_GRBW + NEO_KHZ800);
//////DemoScene demoScene{};
////
//////void setup() {
//////  delay(2000);
//////  Serial.begin(9600);
//////  App::Init(demoScene);
//////}
//////
//////void loop() {
//////  App::Loop();
//////}
//
//void setup() {
//  // put your setup code here, to run once:
//  circuit.setBrightness(10);
//  circuit.begin();
//}
//
//int counter = 0;
//
//void loop() {
//  circuit.clear();
//  for (int i = 0; i < 16; ++i) {
//    circuit.setPixelColor(i, 0, 255, 0, 0);
//  }
//
//  auto c1 = counter;
//  auto c2 = (counter + 1) % 16;
//  auto c3 = (counter + 2) % 16;
//  auto c4 = (counter + 3) % 16;
//  circuit.setPixelColor(c1, 255, 0, 255, 0);
//  circuit.setPixelColor(c2, 255, 0, 255, 0);
//  circuit.setPixelColor(c3, 255, 0, 255, 0);
//  circuit.setPixelColor(c4, 255, 0, 255, 0);
//
//  counter = (counter + 1) % 16;
//
//  circuit.show();
//  delay(30);
//}