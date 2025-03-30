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

  for (int i = 0; i < 100; ++i) {
    if (vehicle.connect()) break;
  }

  if (warmupEffect) {
    auto levels = ring.size() == 12 ? 9 : 13;
    if (ring.size() == 12) {
      yellowStart = 2;
      redStart = 5;
    }
    else {
      yellowStart = 3;
      redStart = 6;
    }
  }
}

auto RpmDisplay::update() -> void {
  rpm = vehicle.rpm();

  if (warmupEffect && ++warmupTimer >= 1200) {
    warmupPhase += 1;
    warmupTimer = 0;
    if (warmupPhase == 2) {
      ++yellowStart;
    }
    else {
      bool changed = false;
      if (redStart < 8) {
        ++redStart;
        changed = true;
      }
      if (yellowStart < 6) {
        ++yellowStart;
        changed = true;
      }
      if (!changed) {
        warmupEffect = false;
      }
    }
  }
}

constexpr u16 mapToPixelPosition(int level, int ledCount) {
  return (level) % ledCount;
}

auto RpmDisplay::draw() -> void {
  auto ledCount = ring.size();
  auto levels = ring.size() == 12 ? 9 : 13;
  auto rpmLevel = rpm / rpmLevelRate;
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


    ring[mapToPixelPosition(i, ledCount)] = color;
  }
}

auto RpmDisplay::cleanup() -> void {
  ring.setShift(0);
}