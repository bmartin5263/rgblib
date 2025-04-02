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
  uint limit{3600};

public:
  int rpm{0};
  RpmLayout layout{RpmLayout::SPORT};
  rgb::u16 yellowLineStart{2800};
  rgb::u16 redLineStart{3600};
  rgb::u8 dimBrightness{1};
  rgb::u8 brightBrightness{4};
};

#endif //RGBLIB_RPMDISPLAY_H
