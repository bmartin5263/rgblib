//
// Created by Brandon on 4/12/25.
//

#include "DebugScreen.h"
#include "time/Clock.h"
#include "Config.h"

namespace rgb {

auto DebugScreen::start() -> void {
  u8g2.begin();
}

auto DebugScreen::display() -> void {
  if (readyForUpdate()) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_samim_10_t_all);
    u8g2.println();
    u8g2.drawStr(0, 20, line0.c_str());
    u8g2.drawStr(0, 30, line1.c_str());
    u8g2.drawStr(0, 40, line2.c_str());
    u8g2.drawStr(0, 50, line3.c_str());
    u8g2.drawStr(0, 60, line4.c_str());
    u8g2.sendBuffer();
    lastUpdate = Clock::Now();
  }
}

auto DebugScreen::readyForUpdate() -> bool {
  auto now = Clock::Now();
  return now.TimeSince(lastUpdate) >= config::DEBUG_SCREEN_REFRESH_RATE;
}

auto DebugScreen::printLine(int row, const std::string& msg) -> void {
  if (row == 0) {
    line0 = msg;
  }
  else if (row == 1) {
    line1 = msg;
  }
  else if (row == 2) {
    line2 = msg;
  }
  else if (row == 3) {
    line3 = msg;
  }
  else {
    line4 = msg;
  }
}

}