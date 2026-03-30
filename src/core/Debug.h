//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_DEBUG_H
#define RGBLIB_DEBUG_H

#include "Types.h"
#include "Clock.h"
#include <functional>
#include <array>

namespace rgb {

enum class BlinkerColor : u8 {
  RED, GREEN, BLUE, PURPLE, YELLOW, CYAN, WHITE, COUNT
};

class Debug {
public:
  static constexpr auto CYCLE_INTERVAL = Duration::Seconds(3);
  static constexpr auto BLINK_DURATION = Duration::Milliseconds(300);
  static constexpr auto GAP_DURATION = Duration::Milliseconds(0);
  static constexpr auto BLINKER_COUNT = static_cast<u8>(BlinkerColor::COUNT);

  using BlinkerCallback = std::function<bool()>;

  static auto Trigger() -> void { Instance().trigger(); }
  static auto Recover() -> void { Instance().recover(); }
  static auto HasFault() -> bool { return Instance().hasFault(); }
  static auto Update() -> void { Instance().update(); }
  static auto Draw() -> void { Instance().draw(); }
  static auto SetBlinker(BlinkerColor color, BlinkerCallback callback) -> void {
    Instance().setBlinker(color, std::move(callback));
  }
  static auto ClearBlinker(BlinkerColor color) -> void {
    Instance().clearBlinker(color);
  }

  Debug(const Debug& rhs) = delete;
  Debug(Debug&& rhs) noexcept = delete;
  Debug& operator=(const Debug& rhs) = delete;
  Debug& operator=(Debug&& rhs) noexcept = delete;

private:
  enum class BlinkState : u8 {
    IDLE, SHOWING, GAP
  };

  Debug() = default;
  ~Debug() = default;

  static auto Instance() -> Debug&;
  auto trigger() -> void;
  auto recover() -> void;
  auto hasFault() const -> bool;
  auto update() -> void;
  auto draw() -> void;
  auto setBlinker(BlinkerColor color, BlinkerCallback callback) -> void;
  auto clearBlinker(BlinkerColor color) -> void;

  auto nextActiveBlinker() -> bool;
  auto setLed(BlinkerColor color) -> void;
  auto clearLed() -> void;

  std::array<BlinkerCallback, BLINKER_COUNT> mBlinkers{};
  BlinkState mState{BlinkState::IDLE};
  Timestamp mStateStart{};
  u8 mCurrentIndex{0};
  bool mFault{false};
};

}

#endif //RGBLIB_DEBUG_H
