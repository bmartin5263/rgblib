//
// Created by Brandon on 7/26/25.
//

#ifndef ARDUINONANOSANDBOX_SEVENSEGMENTDISPLAY_H
#define ARDUINONANOSANDBOX_SEVENSEGMENTDISPLAY_H

#include "Arduino.h"
#include "SPI.h"
#include "Types.h"
#include "array"

namespace rgb {

enum class SevenSegmentDigit {
  _0 = 0,
  _1,
  _2,
  _3,
  _4,
  _5,
  _6,
  _7,
  _8,
  _9,
  BLANK
};

class MAX7219EightDigitSevenSegmentDisplay {
public:
  constexpr static auto DIGIT_PATTERNS = std::array {
    0b01111110, // 0
    0b00110000, // 1
    0b01101101, // 2
    0b01111001, // 3
    0b00110011, // 4
    0b01011011, // 5
    0b01011111, // 6
    0b01110000, // 7
    0b01111111, // 8
    0b01111011  // 9
  };
  constexpr static auto DIGITS = 8u;
  constexpr static auto DASH = 0b00000001;
  constexpr static auto EMPTY = 0b00000000;

  // MAX7219 register addresses
  constexpr static auto REG_DIGIT0 = 0x01;
  constexpr static auto REG_DECODE_MODE = 0x09;
  constexpr static auto REG_INTENSITY = 0x0A;
  constexpr static auto REG_SCAN_LIMIT = 0x0B;
  constexpr static auto REG_SHUTDOWN = 0x0C;
  constexpr static auto REG_DISPLAY_TEST = 0x0F;
  constexpr static auto MAX_BRIGHTNESS = 0x0F;

  MAX7219EightDigitSevenSegmentDisplay(pin_num csPin):
    csPin(csPin) {

  }

  auto start() -> void {
    pinMode(csPin, OUTPUT);
    digitalWrite(csPin, HIGH);

    // Exit shutdown mode
    writeRegister(REG_SHUTDOWN, 0x01);

    // Set decode mode to no decode (we'll handle segment patterns manually)
    writeRegister(REG_DECODE_MODE, 0x00);

    // Set scan limit to display all 8 digits
    writeRegister(REG_SCAN_LIMIT, 0x07);

    // Set intensity (brightness) - 0x00 to 0x0F
    writeRegister(REG_INTENSITY, 0x08);

    // Turn off display test
    writeRegister(REG_DISPLAY_TEST, 0x00);

    clear();
  }

  auto setBrightness(float amount) -> void {
    writeRegister(REG_INTENSITY, MAX_BRIGHTNESS * amount);
  }

  auto clear() -> void {
    for (int i = 0; i < 8; ++i) {
      writeRegister(REG_DIGIT0 + i, EMPTY);
    }
  }

  auto writeRegister(byte reg, byte data) -> void {
    digitalWrite(csPin, LOW);
    SPI.transfer(reg);
    SPI.transfer(data);
    digitalWrite(csPin, HIGH);
  }

  auto writeDigit(SevenSegmentDigit digit, unsigned int offset) -> void {
    writeNumber(static_cast<int>(digit), offset);
  }

  auto writeDigitOrBlank(SevenSegmentDigit digit, unsigned int offset) -> void {
    if (digit == SevenSegmentDigit::BLANK) {
      writePattern(EMPTY, offset);
    }
    else {
      writeNumber(static_cast<int>(digit), offset);
    }
  }

  auto writePattern(byte pattern, unsigned int position, unsigned int count = 1) -> void {
    count = min(count, DIGITS);
    if (count == DIGITS) {
      fillPattern(pattern);
      return;
    }
    position = position % DIGITS;
    for (int i = 0; i < count; ++i) {
      writeRegister(REG_DIGIT0 + position, pattern);
      position = (position + 1) % DIGITS;
    }
  }

  auto fillPattern(byte pattern) -> void {
    for (int i = 0; i < DIGITS; ++i) {
      writeRegister(REG_DIGIT0 + i, pattern);
    }
  }

  auto writeNumber(int number, unsigned int offset = 0, SevenSegmentDigit padding = SevenSegmentDigit::BLANK) -> void {
    // Handle negative numbers
    bool isNegative = false;
    if (number < 0) {
      isNegative = true;
      number = -number;
    }

    // Handle zero case
    if (number == 0) {
      writePattern(DIGIT_PATTERNS[0], offset);
      return;
    }

    // Display digits from right to left
    int count = 0;
    unsigned int position = (offset % DIGITS);
    while (number > 0 && count < DIGITS) {
      int digit = number % 10;
      writePattern(DIGIT_PATTERNS[digit], position);
      number /= 10;
      position = (position + 1) % DIGITS;
      ++count;
    }
    if (padding != SevenSegmentDigit::BLANK) {
      while (count < DIGITS) {
        writePattern(DIGIT_PATTERNS[static_cast<int>(padding)], position);
        position = (position + 1) % DIGITS;
        ++count;
      }
    }

    // Display negative sign if needed
    if (isNegative && count < DIGITS) {
      writePattern(DASH, position);
    }
  }

private:
  pin_num csPin;
};

}


#endif //ARDUINONANOSANDBOX_SEVENSEGMENTDISPLAY_H
