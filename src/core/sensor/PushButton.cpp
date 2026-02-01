//
// Created by Brandon on 2/17/25.
//

#include <utility>
#include "PushButton.h"
#include "Log.h"

namespace rgb {

PushButton::PushButton(PinNumber pin)
  : pin(pin), button()
{
//  pinMode(pin, INPUT); TODO
}

PushButton::PushButton(PinNumber pin, Runnable callback)
  : pin(pin), button(std::move(callback))
{
//  pinMode(pin, INPUT); TODO
}

auto PushButton::onPress(const Runnable& callback) noexcept -> PushButton& {
  button.onPress(callback);
  return *this;
}

auto PushButton::update() -> ButtonState {
//  auto pressed = digitalRead(*pin); TODO
  auto pressed = false;
  return button.update(pressed);
}

auto PushButton::getState() const noexcept -> ButtonState {
  return button.getState();
}

}