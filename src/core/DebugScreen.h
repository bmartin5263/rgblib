//
// Created by Brandon on 4/12/25.
//

#ifndef RGBLIB_DEBUGSCREEN_H
#define RGBLIB_DEBUGSCREEN_H

#include "U8g2lib.h"
#include "Types.h"
#include "CircularLog.h"

namespace rgb {

struct FlipDisplay {
  explicit FlipDisplay(bool v): value(v) {}
  operator bool() const {
    return value;
  }
  bool value;
};

class DebugScreen {
public:
  using DrawFunction = std::function<void(U8G2&)>;

  static auto Start(FlipDisplay flip = FlipDisplay(false)) -> void { Instance().start(flip); }
  static auto PrintLine(const std::string& msg) -> void { Instance().printLine(msg); }
  static auto PrintLine(int row, const std::string& msg) -> void { Instance().printLine(row, msg); }
  static auto Display() -> void { Instance().display(); }
  static auto ReadyForUpdate() -> bool { return Instance().readyForUpdate(); }

private:
  constexpr static auto CS = D10;
  constexpr static auto DC = D9;
  constexpr static auto RESET = D8;

  U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2{U8G2_R0, CS, DC, RESET};
  CircularLog<std::array<std::string, 5>> list{};
  Timestamp lastUpdate{};
  bool started{false};

  static auto Instance() -> DebugScreen& {
    static DebugScreen instance;
    return instance;
  }

  auto start(FlipDisplay flip) -> void;
  auto display() -> void;
  auto readyForUpdate() -> bool;
  auto printLine(const std::string& msg) -> void;
  auto printLine(int row, const std::string& msg) -> void;

};

}


#endif //RGBLIB_DEBUGSCREEN_H
