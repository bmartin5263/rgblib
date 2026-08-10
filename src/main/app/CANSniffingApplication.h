//
// Created by Brandon on 7/26/26.
//

#ifndef RGBLIB_CANSNIFFINGAPPLICATION_H
#define RGBLIB_CANSNIFFINGAPPLICATION_H

#include "UserApplication.h"
#include "MCP2515.h"
#include "CANModule.h"
#include "IRReceiver.h"

using namespace rgb;

inline CANModule mcp2515{A0, CANModule::ClockRate::MHZ_8};

using namespace rgb;

class CANSniffingApplication : public UserApplication<> {
protected:
  auto configure(Configurer& app) -> void override {
  }

  auto initialize() -> void override{
    Debug::SetBlinker(BlinkerColor::RED, [] { return mcp2515.isConnected(); });
    Timer::SetTimeout(Duration::Seconds(1), [](auto& ctx) {
      mcp2515.request();
      ctx.repeatIn = Duration::Seconds(1);
    }).detach();
  }

  auto update() -> void override {
    if (!mcp2515.isConnected()) {
      mcp2515.connect(CANModule::BaudRate::BAUD_500, false);
    }
    else {
      mcp2515.update();
    }
  }
};

#endif //RGBLIB_CANSNIFFINGAPPLICATION_H
