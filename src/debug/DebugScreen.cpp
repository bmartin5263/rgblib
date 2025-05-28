//
// Created by Brandon on 4/12/25.
//

#include "DebugScreen.h"
#include "Clock.h"
#include "Config.h"
#include "Assertions.h"

namespace rgb {

auto DebugScreen::start() -> void {
  ASSERT_C(u8g2.begin(), "Failed to start debug screen", Color::GREEN(.01f));
}

auto DebugScreen::display() -> void {
  if (readyForUpdate()) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_samim_10_t_all);
    u8g2.println();

    auto y = 20;
    for (auto& str : list) {
      u8g2.drawStr(0, y, str.c_str());
      y += 10;
    }

    u8g2.sendBuffer();
    lastUpdate = Clock::Now();
  }
}

auto DebugScreen::readyForUpdate() -> bool {
  auto now = Clock::Now();
  return now.timeSince(lastUpdate) >= config::DEBUG_SCREEN_REFRESH_RATE;
}

auto DebugScreen::printLine(int row, const std::string& msg) -> void {
  list[row] = msg;
}

auto DebugScreen::printLine(const std::string& msg) -> void {
  list.push(msg);
}

}