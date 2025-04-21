//
// Created by Brandon on 2/21/25.
//

#ifndef RGBLIB_RPMDISPLAY_H
#define RGBLIB_RPMDISPLAY_H

#include "Scene.h"
#include "led/LEDCircuit.h"
#include "network/WebServerFwd.h"
#include "sensor/Vehicle.h"
#include "user/effect/RpmLayout.h"
#include "user/effect/RpmColorMode.h"

namespace rgb {
  class PushButton;
}

class RpmDisplay : public rgb::Scene {
public:
  explicit RpmDisplay(rgb::LEDRing& ring, rgb::Vehicle& vehicle);

  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;

private:
  rgb::LEDRing& ring;
  rgb::Vehicle& vehicle;
  rgb::Timestamp lastPulseReset{0};
public:

  rgb::Color greenColor{rgb::Color::GREEN()};
  rgb::Color yellowColor{rgb::Color::YELLOW()};
  rgb::Color redColor{rgb::Color::RED()};
  rgb::fahrenheit minCoolantLevel{70.f};
  rgb::fahrenheit maxCoolantLevel{150.f};
  RpmLayout layout{RpmLayout::TRADITIONAL};
  RpmColorMode colorMode{RpmColorMode::SEGMENTED};
  uint yellowLineStart{5500};
  uint redLineStart{6500};
  uint limit{7000};
  rgb::u8 dimBrightness{1};
  rgb::u8 brightBrightness{4};
  bool glow{true};
  bool bright{false};

private:
  bool lastFrameWasYellow{false};
};

#endif //RGBLIB_RPMDISPLAY_H
