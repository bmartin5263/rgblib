//
// Created by Brandon on 1/19/25.
//

#include "BreatheEffect.h"
#include "Util.h"
#include "led/LEDChain.h"

namespace rgb {

auto BreatheEffect::update() -> void {

}

auto BreatheEffect::draw(LEDChain& chain) -> void {
  auto r = LerpClamp(lowColor.r, highColor.r, phase);
  auto g = LerpClamp(lowColor.g, highColor.g, phase);
  auto b = LerpClamp(lowColor.b, highColor.b, phase);
  auto w = LerpClamp(lowColor.w, highColor.w, phase);
  auto color = Color {r, g, b, w};
  chain.fill(color);
}

auto BreatheEffect::getSpeed() -> u16 {
  return speed;
}

auto BreatheEffect::getHighColor() -> Color {
  return highColor;
}

auto BreatheEffect::getLowColor() -> Color {
  return lowColor;
}

auto BreatheEffect::getHighTime() -> u16 {
  return highTime;
}

auto BreatheEffect::getLowTime() -> u16 {
  return lowTime;
}

auto BreatheEffect::setHighColor(const Color& value) -> BreatheEffect& {
  highColor = value;
  return *this;
}

auto BreatheEffect::setLowColor(const Color& value) -> BreatheEffect& {
  lowColor = value;
  return *this;
}

auto BreatheEffect::setHighTime(u16 value) -> BreatheEffect& {
  highTime = value;
  return *this;
}

auto BreatheEffect::setLowTime(u16 value) -> BreatheEffect& {
  lowTime = value;
  return *this;
}

auto BreatheEffect::setSpeed(u16 value) -> BreatheEffect& {
  speed = value;
  return *this;
}

}