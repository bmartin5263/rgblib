//
// Created by Brandon on 1/11/26.
//

#include "PixelStitch.h"
#include "Assertions.h"

namespace rgb {

PixelStitch::PixelStitch(
  PixelList& leftStart,
  uint leftLength,
  PixelList& rightStart,
  uint rightLength
) : leftStart(&leftStart), rightStart(&rightStart), leftLength(leftLength), rightLength(rightLength) {
  ASSERT(leftLength > 0, "Left Stitch cannot be 0-length");
  ASSERT(rightLength > 0, "Right Stitch cannot be 0-length");
  ASSERT(leftLength <= leftStart.length(), "Left stitch is too long");
  ASSERT(rightLength <= rightStart.length(), "Right stitch is too long");
}

PixelStitch::PixelStitch(PixelList& leftStart, PixelList& rightStart):
  PixelStitch(leftStart, leftStart.length(), rightStart, rightStart.length())
{

}


auto PixelStitch::length() const -> uint {
  return leftLength + rightLength;
}

auto PixelStitch::get(uint pixel) const -> Pixel {
  if (pixel < leftLength) {
    return leftStart->get(pixel);
  }
  else {
    return rightStart->get(pixel - leftLength);
  }
}

void PixelStitch::set(uint pixel, const Color& color) {
  if (pixel < leftLength) {
    return leftStart->set(pixel, color);
  }
  else {
    return rightStart->set(pixel - leftLength, color);
  }
}

}