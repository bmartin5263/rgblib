//
// Created by Brandon on 7/5/25.
//

#include "RpmLayout.h"

auto RpmLayout::TRADITIONAL() -> const RpmLayout* {
  return &TraditionalRpmLayout::Instance();
}

auto RpmLayout::SPORT() -> const RpmLayout* {
  return &SportRpmLayout::Instance();
}

auto TraditionalRpmLayout::calculateLevels(rgb::u16 ledSize) const -> rgb::u16 {
  switch (ledSize) {
    case 12:
      return 9;
    case 16:
      return 13;
    default:
      return ledSize;
  }
}

auto TraditionalRpmLayout::calculateOffset(rgb::u16 ledSize) const -> rgb::u16 {
  switch (ledSize) {
    case 12:
      return 0;
    case 16:
      return 5;
    default:
      return 0;
  }
}

auto SportRpmLayout::calculateOffset(rgb::u16 ledSize) const -> rgb::u16 {
  switch (ledSize) {
    case 12:
      return 10;
    case 16:
      return 3;
    default:
      return 0;
  }
}

auto SportRpmLayout::calculateLevels(rgb::u16 ledSize) const -> rgb::u16 {
  switch (ledSize) {
    case 12:
      return 10;
    case 16:
      return 13;
    default:
      return ledSize;
  }
}