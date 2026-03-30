//
// Created by Brandon on 1/5/25.
//

#include "Debug.h"
#include <Arduino.h>

namespace rgb {

auto Debug::trigger() -> void {
  mFault = true;
}

auto Debug::recover() -> void {
  mFault = false;
}

auto Debug::hasFault() const -> bool {
  return mFault;
}

auto Debug::update() -> void {
}

auto Debug::draw() -> void {
  auto now = Clock::Now();
  auto elapsed = now.timeSince(mStateStart);

  switch (mState) {
    case BlinkState::IDLE: {
      if (elapsed >= CYCLE_INTERVAL) {
        mCurrentIndex = 0;
        if (nextActiveBlinker()) {
          setLed(static_cast<BlinkerColor>(mCurrentIndex));
          mState = BlinkState::SHOWING;
          mStateStart = now;
        }
      }
      break;
    }
    case BlinkState::SHOWING: {
      if (elapsed >= BLINK_DURATION) {
        clearLed();
        ++mCurrentIndex;
        if (nextActiveBlinker()) {
          mState = BlinkState::GAP;
        }
        else {
          mState = BlinkState::IDLE;
        }
        mStateStart = now;
      }
      break;
    }
    case BlinkState::GAP: {
      if (elapsed >= GAP_DURATION) {
        setLed(static_cast<BlinkerColor>(mCurrentIndex));
        mState = BlinkState::SHOWING;
        mStateStart = now;
      }
      break;
    }
  }
}

auto Debug::setBlinker(BlinkerColor color, BlinkerCallback callback) -> void {
  mBlinkers[static_cast<u8>(color)] = std::move(callback);
}

auto Debug::clearBlinker(BlinkerColor color) -> void {
  mBlinkers[static_cast<u8>(color)] = nullptr;
}

auto Debug::nextActiveBlinker() -> bool {
  while (mCurrentIndex < BLINKER_COUNT) {
    auto& callback = mBlinkers[mCurrentIndex];
    if (callback && callback()) {
      return true;
    }
    ++mCurrentIndex;
  }
  return false;
}

auto Debug::setLed(BlinkerColor color) -> void {
#ifdef RGB_ARDUINO_NANO
  // Active-low: LOW = on, HIGH = off
  auto r = HIGH;
  auto g = HIGH;
  auto b = HIGH;

  switch (color) {
    case BlinkerColor::RED:    r = LOW; break;
    case BlinkerColor::GREEN:  g = LOW; break;
    case BlinkerColor::BLUE:   b = LOW; break;
    case BlinkerColor::PURPLE: r = LOW; b = LOW; break;
    case BlinkerColor::YELLOW: r = LOW; g = LOW; break;
    case BlinkerColor::CYAN:   g = LOW; b = LOW; break;
    case BlinkerColor::WHITE:  r = LOW; g = LOW; b = LOW; break;
    default: break;
  }

  digitalWrite(LED_RED, r);
  digitalWrite(LED_GREEN, g);
  digitalWrite(LED_BLUE, b);
#endif
}

auto Debug::clearLed() -> void {
#ifdef RGB_ARDUINO_NANO
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
#endif
}

auto Debug::Instance() -> Debug& {
  static Debug instance;
  return instance;
}

}
