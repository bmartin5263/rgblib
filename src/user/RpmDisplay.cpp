//
// Created by Brandon on 2/21/25.
//

#include "RpmDisplay.h"
#include "sensor/PushButton.h"

using namespace rgb;

RpmDisplay::RpmDisplay(LEDRing& ring, Vehicle& vehicle): ring(ring), vehicle(vehicle) {

}

auto RpmDisplay::setup() -> void {
  INFO("RPM setup");
  ring.setShift(2);

  for (int i = 0; i < 3; ++i) {
    if (vehicle.connect()) break;
  }
}

auto RpmDisplay::update() -> void {
  rpm = vehicle.rpm();
}

constexpr u16 mapToPixelPosition(int level, int ledCount, int offset = 0) {
  return (level + offset) % ledCount;
}

constexpr u16 calculateOffset(RpmLayout layout) {
  return layout == RpmLayout::TRADITIONAL ? 0 : 10;
}


constexpr u16 calculateLevels(u16 ringSize, RpmLayout layout) {
  if (ringSize == 12) {
    if (layout == RpmLayout::SPORT) {
      return 10;
    }
    else {
      return 9;
    }
  }
  else {
    if (layout == RpmLayout::SPORT) {
      return 14;
    }
    else {
      return 13;
    }
  }
}

auto RpmDisplay::draw() -> void {
  auto ledCount = ring.size();
  auto levels = calculateLevels(ring.size(), layout);
  auto rpmLevelRate = limit / levels;
  auto rpmLevel = rpm / rpmLevelRate;
  auto offset = calculateOffset(layout);

  for (int i = 0; i < levels; ++i) {
    auto levelValue = rpmLevelRate * i + rpmLevelRate;
    float brightness;
    if (i < rpmLevel) {
      brightness = ByteToFloat(brightBrightness);
    }
    else {
      brightness = ByteToFloat(dimBrightness);
    }

    Color color;
    if (levelValue < yellowLineStart) {
      color = Color::GREEN(brightness);
    }
    else if (levelValue < redLineStart) {
      color = Color::YELLOW(brightness);
    }
    else {
      color = Color::RED(brightness);
    }


    ring[mapToPixelPosition(i, ledCount, offset)] = color;
  }
}

auto RpmDisplay::cleanup() -> void {
  ring.setShift(0);
}