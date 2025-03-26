//
// Created by Brandon on 3/17/25.
//

#include "Assertions.h"
#include "TrailingScene.h"
#include "Clock.h"

TrailingScene::TrailingScene(TrailingSceneParameters& params): params(params) {
  ASSERT(params.leds != nullptr, "TrailingScene: LEDs is null");
}

auto TrailingScene::setup() -> void {
  moveTime = 0;
  pixel = 0;
}

auto TrailingScene::update() -> void {
  if (moveTime++ >= params.speed) {
    move();
    moveTime = 0;
  }
}

auto TrailingScene::draw() -> void {
  auto& leds = params.LEDs();
  auto ledSize = leds.size();
  auto length = params.length;
  auto time = rgb::Clock::Micro();

  auto colorGeneratorParameters = TrailingSceneColorGeneratorParameters {
    .micros = time,
    .speed = params.speed,
    .length = length
  };
  if (params.continuous) {
    for (int i = 0; i < length; ++i) {
      auto led = (pixel + i + params.shift) % ledSize;
      colorGeneratorParameters.relativePosition = i;
      colorGeneratorParameters.absolutePosition = led;
      leds[led] = params.colorGenerator(colorGeneratorParameters);
    }
  }
  else {
    for (int i = 0; i < length; ++i) {
      auto led = (pixel + i + 1) - ((rgb::i32) length);
      if (led >= 0 && led < ledSize) {
        led = (led + params.shift) % ledSize;
        colorGeneratorParameters.relativePosition = i;
        colorGeneratorParameters.absolutePosition = led;
        leds[led] = params.colorGenerator(colorGeneratorParameters);
      }
    }
  }
}

auto TrailingScene::move() -> void {
  auto& leds = params.LEDs();
  auto ledSize = leds.size();
  pixel += 1;
  if (pixel >= ledSize + (params.continuous ? 0 : params.length + params.endBuffer)) {
    pixel = 0;
  }
}