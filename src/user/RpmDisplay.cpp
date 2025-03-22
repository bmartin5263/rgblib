//
// Created by Brandon on 2/21/25.
//

#include "RpmDisplay.h"

using namespace rgb;

RpmDisplay::RpmDisplay(LEDRing& ring): ring(ring) {

}

auto RpmDisplay::setup() -> void {
  Log.infoLn("RPM setup");
  vehicle.connect();
}

auto RpmDisplay::update() -> void {
  vehicle.connect();
  rpm = vehicle.rpm();
}

constexpr u16 mapToPixelPosition(int level, int rotation, int ledCount) {
  return (level + rotation) % ledCount;
}

auto RpmDisplay::draw() -> void {
  auto ledCount = ring.size();
  auto levels = ring.size() == 12 ? 9 : 13;
  auto rpmLevel = rpm / 500;
  for (int i = 0; i < levels; ++i) {

    float brightness;
    if (i < rpmLevel) {
      brightness = ByteToFloat(brightBrightness);
    }
    else {
      brightness = ByteToFloat(dimBrightness);
    }

    Color color;
    if (i < yellowStart) {
      color = Color::GREEN(brightness);
    }
    else if (i < redStart) {
      color = Color::YELLOW(brightness);
    }
    else {
      color = Color::RED(brightness);
    }


    ring[mapToPixelPosition(i, rotation, ledCount)] = color;
  }
}