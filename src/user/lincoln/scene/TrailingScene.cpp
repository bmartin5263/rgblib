//
// Created by Brandon on 3/17/25.
//

#include "Assertions.h"
#include "TrailingScene.h"
#include "Clock.h"

TrailingScene::TrailingScene(TrailingSceneParameters params): params(std::move(params)) {
  ASSERT(params.leds != nullptr, "TrailingScene: LEDs is null");
}

auto TrailingScene::setup() -> void {
  nextMoveTime.value = 0;
  pixel = 0;
}

auto TrailingScene::update() -> void {
  auto now = rgb::Clock::Now();
  if (now >= nextMoveTime) {
    move();
    nextMoveTime = now + params.speed;
  }
}

auto TrailingScene::draw() -> void {
  auto& leds = params.LEDs();
  auto ledSize = leds.getSize();
  auto length = params.length;
  auto now = rgb::Clock::Now();

  auto colorGeneratorParameters = TrailingSceneColorGeneratorParameters {
    .now = now,
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
      if (led >= 0 && led < ledSize + 1) {
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
  auto ledSize = leds.getSize();
  pixel += 1;
  if (pixel >= ledSize + (params.continuous ? 0 : params.length + params.endBuffer)) {
    pixel = 0;
  }
}