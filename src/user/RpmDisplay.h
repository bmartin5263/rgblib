//
// Created by Brandon on 2/21/25.
//

#ifndef RGBLIB_RPMDISPLAY_H
#define RGBLIB_RPMDISPLAY_H

#include "Scene.h"
#include "led/LEDCircuit.h"
#include "network/WebServerFwd.h"
#include "sensor/Vehicle.h"
#include "RpmLayout.h"

namespace rgb {
  class PushButton;
}

class RpmDisplay : public rgb::Scene {
public:
  explicit RpmDisplay(rgb::LEDRing& ring, rgb::Vehicle& vehicle);

  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;
  auto cleanup() -> void override;

private:
  rgb::LEDRing& ring;
  rgb::Vehicle& vehicle;
  RpmLayout layout{RpmLayout::SPORT};
  bool warmupEffect{true};
  int warmupTimer{0};
  int warmupPhase{0};
  uint rpmLevelRate{500};

public:
  int rpm{0};
  rgb::u16 yellowStart{3};
  rgb::u16 redStart{6};
  rgb::u8 dimBrightness{1};
  rgb::u8 brightBrightness{4};
};

#endif //RGBLIB_RPMDISPLAY_H
