//
// Created by Brandon on 4/12/25.
//

#include "DebugScreen.h"
#include "Clock.h"
#include "Config.h"

namespace rgb {

auto DebugScreen::start(const DrawFunction& drawFunction) -> void {
  u8g2.begin();
  this->drawFunction = drawFunction;
}

auto DebugScreen::display() -> void {
  auto now = Clock::Now();
  if (now.TimeSince(lastUpdate) >= config::DEBUG_SCREEN_REFRESH_RATE) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_samim_10_t_all);
    u8g2.println();
    drawFunction(u8g2);
    u8g2.sendBuffer();
    lastUpdate = now;
  }
}

}