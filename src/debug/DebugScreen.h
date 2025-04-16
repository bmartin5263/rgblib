//
// Created by Brandon on 4/12/25.
//

#ifndef RGBLIB_DEBUGSCREEN_H
#define RGBLIB_DEBUGSCREEN_H

#include "U8g2lib.h"
#include "Types.h"

namespace rgb {

class DebugScreen {
public:
  using DrawFunction = std::function<void(U8G2&)>;

  static auto Start() -> void { Instance().start(); }
  static auto PrintLine(int row, const std::string& msg) -> void { Instance().printLine(row, msg); }
  static auto Display() -> void { Instance().display(); }
  static auto ReadyForUpdate() -> bool { return Instance().readyForUpdate(); }

private:
  U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2{U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8};
  std::string line0{};
  std::string line1{};
  std::string line2{};
  std::string line3{};
  std::string line4{};
  Timestamp lastUpdate{};
  bool started{false};

  static auto Instance() -> DebugScreen& {
    static DebugScreen instance;
    return instance;
  }

  auto start() -> void;
  auto display() -> void;
  auto readyForUpdate() -> bool;
  auto printLine(int row, const std::string& msg) -> void;

};

}


#endif //RGBLIB_DEBUGSCREEN_H
