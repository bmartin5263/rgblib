//
// Created by Brandon on 6/12/25.
//

#include "AdafruitI2CGamepad.h"
#include "Log.h"

constexpr auto BUTTON_X = 6;
constexpr auto BUTTON_Y = 2;
constexpr auto BUTTON_A = 5;
constexpr auto BUTTON_B = 1;
constexpr auto BUTTON_SELECT = 0;
constexpr auto BUTTON_START = 16;
constexpr auto BUTTOM_MASK = (1UL << BUTTON_X) | (1UL << BUTTON_Y) | (1UL << BUTTON_START) |
                       (1UL << BUTTON_A) | (1UL << BUTTON_B) | (1UL << BUTTON_SELECT);
constexpr auto MAX_ANALOG_VALUE = 1023;

namespace rgb {

auto AdafruitI2CGamepad::start() -> void {
  TRACE("Starting AdafruitI2CGamepad");
  if (!seesaw.begin(0x50)) {
    ERROR("Failed to begin() seesaw");
    return;
  }

  auto version = ((seesaw.getVersion() >> 16) & 0xFFFF);
  if (version != 5743) {
    ERROR("Invalid seesaw version");
    return;
  }

  seesaw.pinModeBulk(BUTTOM_MASK, INPUT_PULLUP);
  seesaw.setGPIOInterrupts(BUTTOM_MASK, 1);
}

auto AdafruitI2CGamepad::update() -> void {
  // Reverse x/y values to match joystick orientation
  auto x = MAX_ANALOG_VALUE - seesaw.analogRead(14);
  auto y = MAX_ANALOG_VALUE - seesaw.analogRead(15);
  analogX = static_cast<normal>(x) / static_cast<normal>(MAX_ANALOG_VALUE);
  analogY = static_cast<normal>(y) / static_cast<normal>(MAX_ANALOG_VALUE);

  auto buttons = seesaw.digitalReadBulk(BUTTOM_MASK);

  buttonA.update(!(buttons & (1UL << BUTTON_A)));
  buttonB.update(!(buttons & (1UL << BUTTON_B)));
  buttonX.update(!(buttons & (1UL << BUTTON_X)));
  buttonY.update(!(buttons & (1UL << BUTTON_Y)));
  buttonStart.update(!(buttons & (1UL << BUTTON_START)));
  buttonSelect.update(!(buttons & (1UL << BUTTON_SELECT)));
}

}