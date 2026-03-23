//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_NEOLEDSTRIP_H
#define RGBLIB_NEOLEDSTRIP_H

#include <Adafruit_NeoPixel.h>
#include "Types.h"
#include "Pin.h"
#include "Assertions.h"
#include "core/Color.h"
#include "ContiguousPixelList.h"
#include "LEDCircuit.h"
#include "Log.h"

namespace rgb {

/**
 * Represents a physical LED Strip, also functions as a PixelList with a 1:1 mapping
 * between pixel and LED
 *
 * @tparam N number of physical LEDs
 * @tparam FORMAT type of LEDs (i.e RGBW)
 * @tparam MODEL model of LEDs (i.e WS2812)
 * @tparam BACKEND hardware backend (RMT or SPI)
 */
template <u16 N, u16 PIN, neoPixelType TYPE>
class NeopixelLEDStrip : public ContiguousPixelList, public LEDCircuit {
public:
  constexpr explicit NeopixelLEDStrip(
    u16 offset = 0
  ):
    pixels{}, offset{offset}, brightness(1.0f), reversed{false}, started{false}
  {
  }

  auto start() -> void override {
    if (started) {
      return;
    }
    started = handle.begin();
    INFO("Neopixels Started on %i? %i", PIN, started);
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
//    if (reversed) {
//      for (u16 i = 0; i < N; ++i) {
//        auto pixel = pixels[mapPixelToLED(N - 1 - i)] * brightness;
//        handle.setPixelColor(i, FloatToByte(pixel.r), FloatToByte(pixel.g), FloatToByte(pixel.b), FloatToByte(pixel.w));
//      }
//    }
//    else {
      for (u16 i = 0; i < N; ++i) {
        auto pixel = pixels[mapPixelToLED(i)] * brightness;
        handle.setPixelColor(i, FloatToByte(pixel.r), FloatToByte(pixel.g), FloatToByte(pixel.b), FloatToByte(pixel.w));
      }
//    }
    handle.show();
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

  auto mapPixelToLED(u16 pixel) -> u16 {
    return (pixel + offset) % N;
  }

  NeopixelLEDStrip(const NeopixelLEDStrip&) = delete;
  NeopixelLEDStrip& operator=(const NeopixelLEDStrip&) = delete;
  NeopixelLEDStrip(NeopixelLEDStrip&&) = default;
  NeopixelLEDStrip& operator=(NeopixelLEDStrip&&) = default;

private:
  Adafruit_NeoPixel handle{N, PIN, TYPE};
  Pixel pixels[N];
  int offset;
  normal brightness;
  bool reversed;
  bool started;
};

}


#endif //RGBLIB_NEOLEDSTRIP_H
