//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_DEMOSCENE_H
#define RGBLIB_DEMOSCENE_H

#include "Adafruit_NeoPixel.h"
#include "Scene.h"
#include "led/LEDCircuit.h"
#include "led/LEDSlice.h"
#include "effect/FillEffect.h"
#include "effect/TrailingEffect.h"
#include "effect/BreatheEffect.h"

class DemoScene : public Scene {
public:
  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;
  auto cleanup() -> void override;

private:
  static constexpr int LEDS = 16;

  // Hardware Driver
  Adafruit_NeoPixel neoPixel{LEDS, 6, NEO_RGBW + NEO_KHZ800};

  // Memory for Pixel Colors
  LEDCircuit<LEDS> circuit{neoPixel};

  // Divide memory according to physical setup
  LEDRing* ring{&circuit};

  // Effects
  FillEffect fillEffect{};
  TrailingEffect trailingEffect{};
  BreatheEffect breatheEffect{};

};


#endif //RGBLIB_DEMOSCENE_H
