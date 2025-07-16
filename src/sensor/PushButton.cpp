//
// Created by Brandon on 2/17/25.
//

#include <Arduino.h>

#include <utility>
#include "PushButton.h"
#include "Log.h"

namespace rgb {

PushButton::PushButton(pin_num pin)
  : pin(pin), button()
{
  pinMode(pin, INPUT);
}

PushButton::PushButton(pin_num pin, Runnable callback)
  : pin(pin), button(std::move(callback))
{
  pinMode(pin, INPUT);
}

auto PushButton::onPress(const Runnable& callback) noexcept -> PushButton& {
  button.onPress(callback);
  return *this;
}

auto PushButton::update() -> ButtonState {
  auto pressed = digitalRead(*pin);
  return button.update(pressed);
}

auto PushButton::getState() const noexcept -> ButtonState {
  return button.getState();
}

}