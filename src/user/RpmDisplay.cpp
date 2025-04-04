//
// Created by Brandon on 2/21/25.
//

#include "RpmDisplay.h"
#include "sensor/PushButton.h"
#include "Clock.h"

using namespace rgb;

RpmDisplay::RpmDisplay(LEDRing& ring, Vehicle& vehicle): ring(ring), vehicle(vehicle) {

}

auto RpmDisplay::setup() -> void {
  INFO("RPM setup");
}

auto RpmDisplay::update() -> void {
  rpm = vehicle.rpm();
  auto now = Clock::Now();
  auto a = Pulse(now.asSeconds());
  auto b = Pulse(now.asMilliseconds());
  auto c = Pulse(now.asSeconds() * 3);
  INFO("A: %f   B: %f   C: %f", a, b, c);
}

constexpr u16 mapToPixelPosition(int level, int ledCount, int offset = 0) {
  return (level + offset) % ledCount;
}

constexpr u16 calculateOffset(u16 ringSize, RpmLayout layout) {
  if (ringSize == 12) {
    return layout == RpmLayout::TRADITIONAL ? 0 : 10;
  }
  else {
    return layout == RpmLayout::TRADITIONAL ? 5 : 3;
  }
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
      return 13;
    }
    else {
      return 13;
    }
  }
}

auto RpmDisplay::draw() -> void {
  auto ledCount = ring.size();
  auto levels = calculateLevels(ledCount, layout);
  auto rpmLevelRate = limit / levels;
  auto rpmLevel = rpm / rpmLevelRate;
  auto offset = calculateOffset(ledCount, layout);

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
    if (colorMode == RpmColorMode::SEGMENTED) {
      if (levelValue < yellowLineStart) {
        color = Color::GREEN(brightness);
      }
      else if (levelValue < redLineStart) {
        color = Color::YELLOW(brightness);
      }
      else {
        color = Color::RED(brightness);
      }
    }
    else {
      if (rpm < yellowLineStart) {
        color = Color::GREEN(brightness);
      }
      else if (rpm < redLineStart) {
        color = Color::YELLOW(brightness);
      }
      else {
        color = Color::RED(brightness);
      }
    }


    ring[mapToPixelPosition(i, ledCount, offset)] = color;
  }
}