//
// Created by Brandon on 1/19/25.
//

#include "SolidColorGenerator.h"

SolidColorGenerator::SolidColorGenerator(): _color(Color::BLUE()) {

}

SolidColorGenerator::SolidColorGenerator(const Color& color): _color(color) {

}

auto SolidColorGenerator::color() -> Color& {
  return _color;
}

auto SolidColorGenerator::generate(const Parameters& params) -> Color const {
  return color();
}