//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_NATIVELEDSTRIP_H
#define RGBLIB_NATIVELEDSTRIP_H

#include "Types.h"
#include "Util.h"
#include "ContiguousPixelList.h"
#include "LEDDevice.h"
#include "NativeDisplay.h"
#include "NativeRenderable.h"

namespace rgb {

/**
 * Backs a PixelList with an SDL-rendered window instead of physical LEDs,
 * for running an application with no hardware present.
 */
template <u16 N>
class NativeLEDStrip : public ContiguousPixelList, public LEDDevice, public NativeRenderable {
public:
  constexpr explicit NativeLEDStrip(
    u16 offset = 0
  ):
    pixels{}, offset{offset}, brightness(1.0f), reversed{false}, started{false}
  {
  }

  auto start() -> void override {
    if (started) {
      return;
    }

    NativeDisplay::Register(*this);
    started = true;
  }

  auto data() -> Pixel* override {
    return pixels;
  }

  auto data() const -> const Pixel* override {
    return pixels;
  }

  auto length() const -> uint override {
    return N;
  }

  auto getOffset() const -> int {
    return offset;
  }

  auto setOffset(int amount) -> void {
    offset = amount;
  }

  auto getBrightness() const -> normal {
    return brightness;
  }

  auto setBrightness(normal amount) -> void {
    brightness = Clamp(amount, 0.0f, 1.0f);
  }

  auto reset() -> void override {
    clear();
  }

  auto display() -> void override {
  }

  auto setReversed(bool value) -> void {
    reversed = value;
  }

  auto isReversed() const -> bool {
    return reversed;
  }

  auto toggleReversed() -> bool {
    auto previous = reversed;
    setReversed(!reversed);
    return previous;
  }

  auto mapPixelToLED(u16 pixel) const -> u16 {
    return WrapIndex(pixel, offset, N);
  }

  auto pixelCount() const -> u16 override {
    return N;
  }

  auto renderedPixel(u16 index) const -> Pixel override {
    auto mapped = reversed ? mapPixelToLED(N - 1 - index) : mapPixelToLED(index);
    return pixels[mapped] * brightness;
  }

  NativeLEDStrip(const NativeLEDStrip&) = delete;
  NativeLEDStrip& operator=(const NativeLEDStrip&) = delete;
  NativeLEDStrip(NativeLEDStrip&&) = default;
  NativeLEDStrip& operator=(NativeLEDStrip&&) = default;

private:
  Pixel pixels[N];
  int offset;
  normal brightness;
  bool reversed;
  bool started;
};

}

#endif //RGBLIB_NATIVELEDSTRIP_H
