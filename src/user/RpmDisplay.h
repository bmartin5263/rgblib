//
// Created by Brandon on 2/21/25.
//

#ifndef RGBLIB_RPMDISPLAY_H
#define RGBLIB_RPMDISPLAY_H

#include "Scene.h"
#include "led/LEDCircuit.h"
#include "network/WebServerFwd.h"

namespace rgb {

class RpmDisplay : public Scene {
public:
  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;

private:
  LEDCircuit<16> circuit{D2};
  WebServerHandle handle{};

public:
  std::string colorMap{"gggyyyyyrr"};
  int number{3};
  int change{1};
  int frame{0};
  int speed{25};
  u8 masterBrightness{255};
  u8 dimBrightness{1};
  u8 brightBrightness{4};
//  u8 masterBrightness{15};
//  u8 dimBrightness{100};
//  u8 brightBrightness{255};
};

}

#endif //RGBLIB_RPMDISPLAY_H
