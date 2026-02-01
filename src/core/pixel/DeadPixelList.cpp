//
// Created by Brandon on 1/17/26.
//

#include "DeadPixelList.h"


namespace rgb {

DeadPixelList::DeadPixelList(uint length) : mLength(length) {}

Pixel DeadPixelList::get(uint pixel) const {
  return Color::OFF();
}

void DeadPixelList::set(uint pixel, const Color& color) {
  // Do nothing
}

uint DeadPixelList::length() const {
  return mLength;
}

}