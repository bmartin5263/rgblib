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
#include "RpmColorMode.h"

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
public:

  int rpm{0};
  RpmLayout layout{RpmLayout::TRADITIONAL};
  RpmColorMode colorMode{RpmColorMode::SEGMENTED};
  uint yellowLineStart{5500};
  uint redLineStart{6500};
  uint limit{7000};
  rgb::u8 dimBrightness{1};
  rgb::u8 brightBrightness{4};
};

#endif //RGBLIB_RPMDISPLAY_H
