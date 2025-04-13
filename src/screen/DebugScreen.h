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

  static auto Start(const DrawFunction& drawFunction) -> void { Instance().start(drawFunction); }
  static auto Display() -> void { Instance().display(); }

private:
  DrawFunction drawFunction{};
  Timestamp lastUpdate{};
  bool started{false};

  static auto Instance() -> DebugScreen& {
    static DebugScreen instance;
    return instance;
  }

  auto start(const DrawFunction& drawFunction) -> void;
  auto display() -> void;

  U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2{U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8};


};

}


#endif //RGBLIB_DEBUGSCREEN_H
