//
// Created by Brandon on 3/17/25.
//

#include "BasicRpmDisplay.h"

namespace rgb {

auto BasicRpmDisplay::setup() -> void {
  Log.infoLn("RPM setup");

  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BUILTIN, LOW);

  circuit.setBrightness(255);
  for (int i = 0; i < 16; ++i) {
    circuit[i] = Color::BLUE(.01);
  }
  circuit.display();

  vehicle.connect();
}

auto BasicRpmDisplay::update() -> void {
  vehicle.connect();
  rpm = vehicle.rpm();
}

auto BasicRpmDisplay::draw() -> void {
  int pixel = (rpm / 500);
  auto high = 0.01960784314f;
  auto low = 0.003921568627f;

  for (int i = 0; i < 16; ++i) {
    circuit[i] = Color::OFF();
  }

  for (int i = 2; i < 9; ++i) {
    if (i - 2 < pixel) {
      circuit[i] = Color::GREEN(high);
    }
    else {
      circuit[i] = Color::GREEN(low);
    }
  }
  for (int i = 9; i < 11; ++i) {
    if (i - 2 < pixel) {
      circuit[i] = Color::YELLOW(high);
    }
    else {
      circuit[i] = Color::YELLOW(low);
    }
  }
  for (int i = 11; i < 12; ++i) {
    if (i - 2 < pixel) {
      circuit[i] = Color::RED(high);
    }
    else {
      circuit[i] = Color::RED(low);
    }
  }

  circuit.display();
}

}