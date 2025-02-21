//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_BASICSCENE_H
#define RGBLIB_BASICSCENE_H

#include "Scene.h"
#include "network/WebServerFwd.h"
#include "sensor/PushButton.h"
#include "led/LEDCircuit.h"

namespace rgb {

class BasicScene : public Scene {
public:
  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;
  auto cleanup() -> void override;

private:
  LEDCircuit<16> circuit{D2};
  PushButton button1{D4};
  PushButton button2{D6};
  PushButton button3{D9};
  PushButton button4{D12};
  WebServerHandle handle{};
  WebServerHandle handle2{};

public:
  int speed{8};
  u8 r1{255};
  u8 g1{0};
  u8 b1{0};
  u8 r2{16};
  u8 g2{0};
  u8 b2{0};
  u8 brightness{15};

};

}


#endif //RGBLIB_BASICSCENE_H
