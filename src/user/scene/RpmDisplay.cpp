//
// Created by Brandon on 2/21/25.
//

#include "RpmDisplay.h"
#include "sensor/PushButton.h"
#include "time/Clock.h"
#include "debug/DebugScreen.h"

using namespace rgb;

RpmDisplay::RpmDisplay(LEDRing& ring, Vehicle& vehicle): ring(ring), vehicle(vehicle) {

}

auto RpmDisplay::setup() -> void {
  INFO("RPM setup");
  lastPulseReset = Clock::Now();
}

auto RpmDisplay::update() -> void {

}

constexpr u16 mapToPixelPosition(int level, int ledCount, int offset = 0) {
  return (level + offset) % ledCount;
}

constexpr u16 calculateOffset(u16 ledSize, RpmLayout layout, RpmShape shape) {
  if (shape == RpmShape::LINE) {
    return 0;
  }
  else if (ledSize == 12) {
    return layout == RpmLayout::TRADITIONAL ? 0 : 10;
  }
  else if (ledSize == 16) {
    return layout == RpmLayout::TRADITIONAL ? 5 : 3;
  }
  else {
    return 0;
  }
}


constexpr u16 calculateLevels(u16 ledSize, RpmLayout layout, RpmShape shape) {
  if (shape == RpmShape::LINE) {
    return ledSize;
  }
  else if (ledSize == 12) {
    if (layout == RpmLayout::SPORT) {
      return 10;
    }
    else {
      return 9;
    }
  }
  else if (ledSize == 16) {
    if (layout == RpmLayout::SPORT) {
      return 13;
    }
    else {
      return 13;
    }
  }
  else {
    return ledSize;
  }
}

auto RpmDisplay::draw() -> void {
  auto coolantTemp = vehicle.coolantTemp();
  auto coolantPercent = RemapPercent(minCoolantLevel, maxCoolantLevel, coolantTemp);
  auto effectiveYellowLineStart = static_cast<u16>(yellowLineStart * LerpClamp(.6f, 1.0f, coolantPercent));
  auto effectiveRedLineStart = static_cast<u16>(redLineStart * LerpClamp(.8f, 1.0f, coolantPercent));
  auto effectiveBrightBrightness = bright ? brightBrightness * 3 : brightBrightness;
  auto effectiveDimBrightness = bright ? dimBrightness * 3 : dimBrightness;

  auto ledCount = ring.getSize();
  auto levelCount = calculateLevels(ledCount, layout, shape);
  auto rpmPerLevel = limit / levelCount;
  auto yellowLevel = effectiveYellowLineStart / rpmPerLevel;
  auto redLevel = effectiveRedLineStart / rpmPerLevel;
  auto rpmLevelAchieved = static_cast<uint>(vehicle.rpm() / rpmPerLevel);
  if (rpmLevelAchieved == 0 && vehicle.rpm() > 100) {
    ++rpmLevelAchieved;
  }
  auto offset = calculateOffset(ledCount, layout, shape);
  auto now = Clock::Now();

  for (int level = 0; level < levelCount; ++level) {
    auto minRpmToAchieveLevel = (rpmPerLevel * level) + rpmPerLevel;
    float brightness;
    if (level < rpmLevelAchieved) {
      if (rpmLevelAchieved > yellowLevel && glow) {
        if (!lastFrameWasYellow) {
          lastPulseReset = now - Duration::Milliseconds(500);
        }
        auto d = ByteToFloat(effectiveBrightBrightness);
        auto b = ByteToFloat(effectiveBrightBrightness + 6);
        brightness = Lerp(d, b, Pulse((now - lastPulseReset).asSeconds(), 1.5f));
        lastFrameWasYellow = true;
      }
      else {
        if (lastFrameWasYellow) {
          auto d = ByteToFloat(effectiveBrightBrightness);
          auto b = ByteToFloat(effectiveBrightBrightness + 6);
          brightness = Lerp(d, b, Pulse((now - lastPulseReset).asSeconds(), 1.5f));
          if (brightness <= ByteToFloat(effectiveBrightBrightness + 1)) {
            lastFrameWasYellow = false;
          }
        }
        else {
          brightness = ByteToFloat(effectiveBrightBrightness);
        }
      }
    }
    else {
      brightness = ByteToFloat(effectiveDimBrightness);
    }

    Color color;
    if (colorMode == RpmColorMode::SEGMENTED) {
      if (level < yellowLevel) {
        color = greenColor * brightness;
      }
      else if (level < redLevel) {
        color = yellowColor * brightness;
      }
      else {
        color = redColor * brightness;
      }
    }
    else if (colorMode == RpmColorMode::SMOOTH) {
      if (minRpmToAchieveLevel <= effectiveYellowLineStart) {
        color = greenColor.lerpClamp(yellowColor, static_cast<float>(minRpmToAchieveLevel) / static_cast<float>(effectiveYellowLineStart)) * brightness;
      }
      else {
        color = yellowColor.lerpClamp(redColor, static_cast<float>(minRpmToAchieveLevel) / static_cast<float>(effectiveRedLineStart)) * brightness;
      }
    }
    else {
      if (rpmLevelAchieved < yellowLevel) {
        color = greenColor * brightness;
      }
      else if (rpmLevelAchieved < redLevel) {
        color = yellowColor * brightness;
      }
      else {
        color = redColor * brightness;
      }
    }


    ring[mapToPixelPosition(level, ledCount, offset)] = color;
  }
}